/*
 * Linux x86_64 syscall layer + preemptive scheduler.
 *
 * schedule() is naked asm called from the PIT tick: it saves the
 * interrupted kernel context on the current process's kernel stack,
 * picks the next RUNNABLE process and resumes it.  Blocking syscalls
 * (wait4, console read) park the process WAITING; wakeups come from
 * the keyboard IRQ and child exits.
 *
 * Trapframe offsets are those of intr.c (also used by sys.S).
 */

#include "proc.h"

/* trapframe offsets */
#define FR_R15	0x00
#define FR_R14	0x08
#define FR_R13	0x10
#define FR_R12	0x18
#define FR_R11	0x20
#define FR_R10	0x28
#define FR_R9	0x30
#define FR_R8	0x38
#define FR_RBP	0x40
#define FR_RSI	0x48
#define FR_RDI	0x50
#define FR_RDX	0x58
#define FR_RCX	0x60
#define FR_RBX	0x68
#define FR_RAX	0x70
#define FR_VEC	0x78
#define FR_ERR	0x80
#define FR_RIP	0x88

#define ENOENT	2
#define EFAULT	14
#define EBADF	9
#define ENOMEM	12
#define EINVAL	22
#define ENOTTY	25
#define EPIPE	32
#define ENFILE	23
#define EMFILE	24
#define ENOSYS	38
#define ECHILD	10
#define ENOTDIR	20

#define PAGE_SIZE	4096ul
#define PTE_P		0x001
#define PTE_W		0x002
#define PTE_U		0x004
#define PTE_NX		0x8000000000000000ull
#define PTE_USER_RW	(PTE_P | PTE_W | PTE_U | PTE_NX)

#define phys2virt(p)	((void *)((uint64_t)(p) + hhdm_offset))

/* --------------------------------------------------------- extern APIs */

/* exec.c */
extern struct proc proc[NPROC];
extern struct proc *curproc;
int execve_proc(struct proc *p, const char *path, char **argv,
    char **envp);
void proc_free(struct proc *p);
extern int have_btrfs;
extern int have_fat;
/* vmm.c */
unsigned long long vmm_new(void);
int vmm_map(unsigned long long cr3, unsigned long long va,
    unsigned long long pa, unsigned long long flags);
unsigned long long vmm_phys(unsigned long long cr3, unsigned long long va);
void vmm_destroy_user(unsigned long long cr3);
void vmm_copy_range(unsigned long long src, unsigned long long dst,
    unsigned long long lo, unsigned long long hi);
/* pmm.c */
unsigned long long alloc_phys(void);
void free_phys(unsigned long long p);
unsigned long long alloc_run(unsigned long long npages,
    unsigned long long *got);
unsigned long long pmm_stack_alloc(void);
void pmm_stack_free(unsigned long long base);
/* intr.c */
void pic_eoi(int irq);
void sti(void);
/* keyboard.c */
int kbd_getchar(void);
int kbd_haschar(void);
void kbd_echo_enable(int on);
/* console.c */
void console_write(const char *s, unsigned long n);
/* cpu.c */
void cpu_kstack_set(unsigned long long top, unsigned long long rsp0);
void cpu_fsbase_set(unsigned long long base);
/* btrfs.c */
int btrfs_lookup(const char *path, unsigned long long *ino,
    unsigned long long *size, unsigned short *mode);
int btrfs_readdir(unsigned long long dirid, unsigned int index,
    unsigned int *next, char *name, unsigned long long *child,
    unsigned char *dtype);
unsigned int btrfs_read_file(unsigned long long ino, unsigned long long off,
    unsigned int len, unsigned char *buf);
/* fat32.c */
int fat_lookup(const char *path, struct fatent *out);
unsigned int fat_read_at(const struct fatent *e, unsigned int off,
    unsigned int len, unsigned char *buf);
/* limine.c / pmm.c */
extern unsigned long long hhdm_offset;
extern volatile unsigned long long jiffies;

/* ---------------------------------------------------------- scheduler */

/* non-static: referenced by name from schedule()'s inline asm */
struct proc *
pick_next(void)
{
	int i, start;
	struct proc *best = 0;
	static unsigned long long last;
	extern void console_puts(const char *);
	extern void putdec(unsigned long long);

	if (curproc)
		start = (int)(curproc - proc) + 1;
	else
		start = 0;
	for (i = 0; i < NPROC; i++) {
		struct proc *p = &proc[(start + i) % NPROC];

		if (p->state == RUNNABLE && p->ksp != 0) {
			best = p;
			break;
		}
	}
	return best;
}

/*
 * Naked: call only from the tick (after EOI) or from a blocking
 * syscall.  Saves the six callee-saved regs plus RFLAGS, stores rsp
 * into curproc->ksp (unless ZOMBIE -- those are never resumed), picks
 * the next process, switches CR3 + kernel stack, restores.  Offsets:
 * state 0x00, cr3 0x10, kstack 0x18, ksp 0x20 (proc.h).
 *
 * Saved-stack layout from ksp (ascending): rflags, r15, r14, r13,
 * r12, rbx, rbp, return address.  fork() hand-builds the same shape.
 */
__attribute__((naked))
void
schedule(void)
{
	__asm__ volatile(
	    "pushq %rbp\n"
	    "pushq %rbx\n"
	    "pushq %r12\n"
	    "pushq %r13\n"
	    "pushq %r14\n"
	    "pushq %r15\n"
	    /*
	     * Defer interrupts across save/switch: a tick landing
	     * between "movq %rsp, 0x20(%rdi)" and the stack switch
	     * would re-enter schedule() and overwrite the saved ksp of
	     * the context we are parking.  The saved RFLAGS travels on
	     * the context's own stack and is restored by popfq below,
	     * so the resumed context sees exactly the IF state it had.
	     */
	    "pushfq\n"
	    "cli\n"
	    "movq curproc(%rip), %rdi\n"
	    "testq %rdi, %rdi\n"
	    "jz 1f\n"
	    "cmpl $4, 0(%rdi)\n"		/* ZOMBIE: never resumed */
	    "je 1f\n"
	    "movq %rsp, 0x20(%rdi)\n"
	    /*
	     * A RUNNING process being preempted must become RUNNABLE,
	     * otherwise it is parked with a saved ksp that no one will
	     * ever pick: blockable states (WAITING/ZOMBIE) keep their
	     * value, but a bare tick used to leave the interrupted
	     * process marked RUNNING forever.  That is what hung
	     * external commands: bash was preempted inside wait4
	     * (state RUNNING) just before the child exited, so the
	     * exiting child found nobody to switch to and halted.
	     */
	    "cmpl $2, 0(%rdi)\n"
	    "jne 1f\n"
	    "movl $1, 0(%rdi)\n"
	    "1:\n"
	    "call pick_next\n"
	    "testq %rax, %rax\n"
	    "jz 2f\n"
	    "movq %rax, %rdi\n"
	    "movq %rdi, curproc(%rip)\n"
	    "movl $2, 0(%rdi)\n"
	    "movq 0x10(%rdi), %rax\n"
	    "movq %rax, %cr3\n"
	    "movq 0x18(%rdi), %rsi\n"
	    "movq %rsi, %rdi\n"
	    "call cpu_kstack_set\n"		/* (top, rsp0=top) */
	    /*
	     * FS_BASE is per-process (glibc TLS lives there).  Without
	     * restoring it on every switch a process resumes with the
	     * previous owner's TLS, so fs:0x28 (the stack canary) reads
	     * someone else's value and every stack-protected binary
	     * aborts with "stack smashing detected".
	     */
	    "movq curproc(%rip), %rdi\n"
	    "movq 0x48(%rdi), %rdi\n"
	    "call cpu_fsbase_set\n"
	    "movq curproc(%rip), %rdi\n"
	    "movq 0x20(%rdi), %rsp\n"
	    "2:\n"
	    "popfq\n"
	    "popq %r15\n"
	    "popq %r14\n"
	    "popq %r13\n"
	    "popq %r12\n"
	    "popq %rbx\n"
	    "popq %rbp\n"
	    "ret\n");
}

/*
 * Wake every WAITING process.  Called from the keyboard IRQ: the only
 * things that block are console reads (and wait4, which tolerates
 * spurious wakeups by re-checking), so a blanket wakeup is correct.
 */
void
proc_wake_all(void)
{
	int i;

	for (i = 0; i < NPROC; i++)
		if (proc[i].state == WAITING)
			proc[i].state = RUNNABLE;
}

/* ------------------------------------------------------------- copyout */

static int
copyout(struct proc *p, unsigned long long uaddr, const void *kbuf,
    unsigned long long len)
{
	unsigned long long done = 0;

	while (done < len) {
		unsigned long long page = (uaddr + done) & ~(PAGE_SIZE - 1);
		unsigned long long pa = vmm_phys(p->cr3, page);
		unsigned long long in = (uaddr + done) & (PAGE_SIZE - 1);
		unsigned long long chunk = PAGE_SIZE - in;
		uint8_t *dst;
		unsigned long long k;

		if (pa == 0)
			return -1;
		if (chunk > len - done)
			chunk = len - done;
		dst = (uint8_t *)phys2virt(pa) + in;
		for (k = 0; k < chunk; k++)
			dst[k] = ((const uint8_t *)kbuf)[done + k];
		done += chunk;
	}
	return 0;
}

static int
copyin(struct proc *p, void *kbuf, unsigned long long uaddr,
    unsigned long long len)
{
	unsigned long long done = 0;

	while (done < len) {
		unsigned long long page = (uaddr + done) & ~(PAGE_SIZE - 1);
		unsigned long long pa = vmm_phys(p->cr3, page);
		unsigned long long in = (uaddr + done) & (PAGE_SIZE - 1);
		unsigned long long chunk = PAGE_SIZE - in;
		const uint8_t *src;
		unsigned long long k;

		if (pa == 0)
			return -1;
		if (chunk > len - done)
			chunk = len - done;
		src = (const uint8_t *)phys2virt(pa) + in;
		for (k = 0; k < chunk; k++)
			((uint8_t *)kbuf)[done + k] = src[k];
		done += chunk;
	}
	return 0;
}

static int
copyinstr(struct proc *p, char *kbuf, unsigned long long uaddr, int max)
{
	int n = 0;

	while (n < max - 1) {
		if (copyin(p, kbuf + n, uaddr + n, 1) != 0)
			return -1;
		if (kbuf[n] == 0)
			return n;
		n++;
	}
	kbuf[n] = 0;
	return n;
}

/* ------------------------------------------------------- file helpers */

static int
fs_stat(const char *path, unsigned long long *ino, unsigned long long *size,
    unsigned short *mode, unsigned int *fatclus)
{
	struct fatent fe;

	*mode = 0100755;
	*fatclus = 0;
	if (have_btrfs &&
	    btrfs_lookup(path, ino, size, mode) == 0)
		return 0;
	*ino = 0;
	if (have_fat && fat_lookup(path, &fe) == 0) {
		*size = fe.size;
		*fatclus = fe.cluster;
		return 0;
	}
	return -1;
}

/* ------------------------------------------------------------ syscalls */

/* -------------------------------------------------------------- pipes */

/*
 * Anonymous pipes: a ring buffer plus reader/writer counts.  Both ends
 * are ordinary file descriptors (is_pipe set) so dup/fork/exec inherit
 * them for free.  Delivery is schedule()-based; a blanket
 * proc_wake_all() on every write/close is plenty at this scale.
 */
#define NPIPE		8
#define PIPE_BUF	4096

struct pipe {
	uint8_t buf[PIPE_BUF];
	unsigned int head, tail;		/* byte positions */
	int readers, writers;
	int used;
};

static struct pipe pipes[NPIPE];

static struct pipe *
pipe_alloc(void)
{
	int i;

	for (i = 0; i < NPIPE; i++)
		if (!pipes[i].used) {
			pipes[i].used = 1;
			pipes[i].head = pipes[i].tail = 0;
			pipes[i].readers = pipes[i].writers = 0;
			return &pipes[i];
		}
	return 0;
}

static void pipe_close(struct proc *p, int fd);

static void
pipe_free(struct pipe *pp)
{
	if (pp)
		pp->used = 0;
}

/* an fd now refers to this pipe: bump the matching end's refcount */
static void
pipe_ref(struct file *f)
{
	struct pipe *pp = f->pipe;

	if (pp == 0)
		return;
	if (f->pipe_rd)
		pp->readers++;
	else
		pp->writers++;
}

static unsigned int
pipe_count(struct pipe *pp)
{
	return pp->head - pp->tail;
}

static long long
sys_pipe(struct proc *p, unsigned long long ufds)
{
	struct pipe *pp = pipe_alloc();
	int rfd = -1, wfd = -1, i;
	int fds[2];

	if (pp == 0)
		return -ENFILE;
	for (i = 3; i < NOFILE; i++)
		if (!p->files[i].used) {
			rfd = i;
			break;
		}
	for (; i < NOFILE; i++)
		if (!p->files[i].used && i != rfd) {
			wfd = i;
			break;
		}
	if (rfd < 0 || wfd < 0) {
		pipe_free(pp);
		return -EMFILE;
	}
	p->files[rfd].used = 1;
	p->files[rfd].is_pipe = 1;
	p->files[rfd].pipe_rd = 1;
	p->files[rfd].ino = 0;
	p->files[rfd].size = 0;
	p->files[rfd].off = 0;
	p->files[rfd].pipe = pp;
	p->files[wfd] = p->files[rfd];
	p->files[wfd].pipe_rd = 0;
	pipe_ref(&p->files[rfd]);
	pipe_ref(&p->files[wfd]);
	fds[0] = rfd;
	fds[1] = wfd;
	if (copyout(p, ufds, fds, 8) != 0) {
		pipe_close(p, rfd);
		pipe_close(p, wfd);
		return -EFAULT;
	}
	return 0;
}

static void
pipe_close(struct proc *p, int fd)
{
	struct pipe *pp = p->files[fd].pipe;

	if (pp == 0)
		return;
	if (p->files[fd].pipe_rd)
		pp->readers--;
	else
		pp->writers--;
	if (pp->readers <= 0 && pp->writers <= 0)
		pipe_free(pp);
	p->files[fd].used = 0;
	p->files[fd].pipe = 0;
	proc_wake_all();
}

/* close-on-exec: execve drops every descriptor above stderr */
void
proc_exec_fds(struct proc *p)
{
	int j;

	for (j = 3; j < NOFILE; j++)
		if (p->files[j].used) {
			if (p->files[j].is_pipe)
				pipe_close(p, j);
			else
				p->files[j].used = 0;
		}
}

static long long
pipe_read(struct proc *p, struct pipe *pp, unsigned long long ubuf,
    unsigned long long len)
{
	uint8_t tmp[256];
	unsigned long long got = 0;

	while (got == 0) {
		unsigned int n = pipe_count(pp);

		if (n == 0) {
			if (pp->writers <= 0)
				return 0;	/* EOF */
			p->state = WAITING;
			schedule();
			p->state = RUNNING;
			continue;
		}
		if (n > len)
			n = (unsigned int)len;
		if (n > sizeof(tmp))
			n = sizeof(tmp);
		{
			unsigned int i, pos;

			for (i = 0; i < n; i++) {
				pos = (pp->tail + i) % PIPE_BUF;
				tmp[i] = pp->buf[pos];
			}
			pp->tail += n;
		}
		if (copyout(p, ubuf, tmp, n) != 0)
			return -EFAULT;
		got = n;
	}
	proc_wake_all();
	return (long long)got;
}

static long long
pipe_write(struct proc *p, struct pipe *pp, unsigned long long ubuf,
    unsigned long long len)
{
	uint8_t tmp[256];
	unsigned long long done = 0;

	while (done < len) {
		unsigned int space = PIPE_BUF - pipe_count(pp);
		unsigned int n;

		if (pp->readers <= 0)
			return done ? (long long)done : -EPIPE;
		if (space == 0) {
			proc_wake_all();
			p->state = WAITING;
			schedule();
			p->state = RUNNING;
			continue;
		}
		n = (unsigned int)(len - done);
		if (n > space)
			n = space;
		if (n > sizeof(tmp))
			n = sizeof(tmp);
		if (copyin(p, tmp, ubuf + done, n) != 0)
			return -EFAULT;
		{
			unsigned int i, pos;

			for (i = 0; i < n; i++) {
				pos = (pp->head + i) % PIPE_BUF;
				pp->buf[pos] = tmp[i];
			}
			pp->head += n;
		}
		done += n;
		proc_wake_all();
	}
	return (long long)done;
}

/* ------------------------------------------------------------- ioctl */

/* a plausible termios for the kernel console */
static long long
sys_ioctl(struct proc *p, int fd, unsigned long long req,
    unsigned long long arg)
{
	if (fd < 0 || fd >= NOFILE || !p->files[fd].used)
		return -EBADF;
	/* the console is the only character device; a dup or an
	 * F_DUPFD'ed descriptor keeps ino == 0 */
	/*
	 * Only the console is a terminal.  Job control stays off: the
	 * kernel does not deliver signals yet (no SIGTTIN/SIGTTOU/
	 * SIGCHLD), and bash's job-control machinery would deadlock
	 * waiting for them.  ENOTTY on a dup'ed tty fd makes bash fall
	 * back to "no job control in this shell".
	 */
	if (!p->files[fd].is_console)
		return -ENOTTY;

	switch (req) {
	case 0x5401: {				/* TCGETS */
		uint8_t t[36];
		int i;

		for (i = 0; i < 36; i++)
			t[i] = 0;
#define PUT32(o, v) do { \
		t[o] = (uint8_t)((v) & 0xff); \
		t[(o) + 1] = (uint8_t)(((v) >> 8) & 0xff); \
		t[(o) + 2] = (uint8_t)(((v) >> 16) & 0xff); \
		t[(o) + 3] = (uint8_t)(((v) >> 24) & 0xff); \
	} while (0)
		PUT32(0, 0x0500);		/* ICRNL | IXON */
		PUT32(4, 0x0005);		/* OPOST | ONLCR */
		PUT32(8, 0x00bf);		/* B38400 | CS8 | CREAD */
		/* ISIG|ICANON|ECHO|ECHOE|ECHOK|ECHONL|IEXTEN.
		 * FLUSHO (0x200) must stay clear: readline treats it as
		 * "output being flushed" and turns flushing off. */
		PUT32(12, 0x807b);
		t[22] = 0;			/* VTIME = c_cc[5] */
		t[23] = 1;			/* VMIN  = c_cc[6] */
#undef PUT32
		if (copyout(p, arg, t, 36) != 0)
			return -EFAULT;
		return 0;
	}
	case 0x5402:				/* TCSETS */
	case 0x5403:				/* TCSETSW */
	case 0x5404:				/* TCSETSF */
		return 0;
	case 0x540f: {				/* TIOCGPGRP */
		uint32_t pid = (uint32_t)p->pid;

		if (copyout(p, arg, &pid, 4) != 0)
			return -EFAULT;
		return 0;
	}
	case 0x5410:				/* TIOCSPGRP */
		return 0;
	case 0x5413: {				/* TIOCGWINSZ */
		uint16_t ws[4];			/* row, col, xpix, ypix */

		ws[0] = 24;
		ws[1] = 80;
		ws[2] = 0;
		ws[3] = 0;
		if (copyout(p, arg, ws, 8) != 0)
			return -EFAULT;
		return 0;
	}
	case 0x541b: {				/* FIONREAD */
		uint32_t n = kbd_haschar() ? 1 : 0;

		if (copyout(p, arg, &n, 4) != 0)
			return -EFAULT;
		return 0;
	}
	default:
		return 0;
	}
}

/* ------------------------------------------------------ select/poll */

/*
 * Wait until the console (fd 0) has a byte.  Only the low 64 fds are
 * inspected: the guest never has more than a handful, and bash's
 * readline selects on stdin alone.
 */
static void
wait_console(struct proc *p)
{
	while (!kbd_haschar()) {
		p->state = WAITING;
		schedule();
		p->state = RUNNING;
	}
}

/* read a 64-bit chunk of an fd_set; returns 0 on EFAULT */
static int
fdset_get(struct proc *p, unsigned long long uaddr, unsigned long long *v)
{
	*v = 0;
	if (uaddr == 0)
		return 0;
	return copyin(p, v, uaddr, 8);
}

static long long
sys_select(struct proc *p, unsigned long long nfds,
    unsigned long long urfds, unsigned long long uwfds,
    unsigned long long uefds, unsigned long long utimeout, int is_pselect)
{
	unsigned long long r = 0, w = 0, e = 0, rr;
	long long nready = 0;
	int need = 0, nonblock = 0;

	(void)utimeout;
	if (nfds == 0)
		return 0;

	if (fdset_get(p, urfds, &r) != 0 ||
	    fdset_get(p, uwfds, &w) != 0 ||
	    fdset_get(p, uefds, &e) != 0)
		return -EFAULT;
	(void)e;

	if ((r & 1) && !kbd_haschar())
		need = 1;

	/*
	 * Timeouts matter: readline calls _rl_input_queued() with a
	 * 500 ms timeout while it decides whether the next key extends a
	 * multi-key sequence, and it expects select() to come back empty
	 * when nothing arrives.  Blocking there instead makes the shell
	 * swallow the following keystrokes as sequence continuations
	 * (dropped key + bell), which is what made readline eat the
	 * first characters of a line.
	 */
	{
		unsigned long long ts[2];
		unsigned long long ms = 0;

		if (utimeout && copyin(p, ts, utimeout, 16) == 0) {
			ms = ts[0] * 1000ull + ts[1] / 1000000ull;
			if (ts[0] == 0 && ts[1] == 0)
				nonblock = 1;
		}
		if ((r & 1) && !kbd_haschar()) {
			if (nonblock) {
				r &= ~1ull;
				need = 0;
			} else if (ms) {
				unsigned long long deadline =
				    jiffies + (ms + 9) / 10;

				while (!kbd_haschar() && jiffies < deadline) {
					p->state = WAITING;
					schedule();
					p->state = RUNNING;
					if (!kbd_haschar() && jiffies < deadline)
						__asm__ volatile("sti; hlt");
				}
				if (!kbd_haschar())
					r &= ~1ull;
			} else
				wait_console(p);
			need = 0;
		}
	}

	/* everything else is reported ready: the only files are the
	 * console (write always succeeds) and regular files (always
	 * readable); pipes are not select()ed by bash */

	rr = 0;
	if (r & 1) {
		rr |= 1;
		nready++;
	}
	if (r & ~1ull) {			/* other read fds: ready */
		rr |= r & ~1ull;
		nready += __builtin_popcountll(r & ~1ull);
	}
	if (w) {
		nready += __builtin_popcountll(w);
	}
	if (urfds && copyout(p, urfds, &rr, 8) != 0)
		return -EFAULT;
	if (uwfds && copyout(p, uwfds, &w, 8) != 0)	/* writable */
		return -EFAULT;
	if (uefds) {
		unsigned long long z = 0;

		if (copyout(p, uefds, &z, 8) != 0)
			return -EFAULT;
	}
	(void)is_pselect;
	return nready;
}

struct pollfd_k {
	int fd;
	short events;
	short revents;
};

static long long
sys_poll(struct proc *p, unsigned long long ufds, unsigned long long nfds)
{
	unsigned long long i;
	int need = 0;

	if (nfds > 64)
		nfds = 64;
	for (i = 0; i < nfds; i++) {
		struct pollfd_k pf;

		if (copyin(p, &pf, ufds + 8 * i, 8) != 0)
			return -EFAULT;
		if (pf.fd == 0 && (pf.events & 1) && !kbd_haschar())
			need = 1;
	}
	if (need)
		wait_console(p);

	{
		long long nready = 0;

		for (i = 0; i < nfds; i++) {
			struct pollfd_k pf;

			if (copyin(p, &pf, ufds + 8 * i, 8) != 0)
				return -EFAULT;
			pf.revents = 0;
			if (pf.fd == 0)
				pf.revents = pf.events & 1;	/* POLLIN */
			else if (pf.fd < NOFILE)
				pf.revents = pf.events;		/* always */
			if (pf.revents)
				nready++;
			if (copyout(p, ufds + 8 * i, &pf, 8) != 0)
				return -EFAULT;
		}
		return nready;
	}
}

/*
 * getdents64: walk the btrfs DIR_INDEX items of an open directory.  Each
 * linux_dirent64 is { u64 ino; s64 off; u16 reclen; u8 type; char name[]; }
 * padded to 8 bytes; d_name starts at offset 19.
 */
/*
 * statx(2).  Modern glibc routes fstat/stat through it (coreutils' ls
 * calls statx first and, when it returns ENOSYS, gives up instead of
 * falling back), so an unimplemented statx makes `ls <dir>` fail with
 * a bogus ENOTDIR.
 */
static long long
sys_statx(struct proc *p, int dirfd, unsigned long long upath,
    unsigned long long uflags, unsigned long long ubuf)
{
	uint8_t sx[256];
	char path[256];
	unsigned long long ino = 0, size = 0;
	unsigned short mode = 0;
	unsigned int fc = 0, i;
	int r;

	if (copyinstr(p, path, upath, sizeof(path)) < 0)
		return -EFAULT;
	if (path[0] == 0 && dirfd >= 0 && dirfd < NOFILE &&
	    p->files[dirfd].used) {
		struct file *f = &p->files[dirfd];

		ino = f->ino;
		size = f->size;
		mode = f->is_console ? 0020620 :
		    f->is_dir ? 0040755 : 0100644;
		(void)uflags;
	} else {
		if (path[0] == 0)
			return -ENOENT;
		r = fs_stat(path, &ino, &size, &mode, &fc);
		if (r != 0)
			return -ENOENT;
	}
	for (i = 0; i < sizeof(sx); i++)
		sx[i] = 0;
#define SX32(o, v) do { \
		sx[o] = (uint8_t)((v) & 0xff); \
		sx[(o)+1] = (uint8_t)(((v) >> 8) & 0xff); \
		sx[(o)+2] = (uint8_t)(((v) >> 16) & 0xff); \
		sx[(o)+3] = (uint8_t)(((v) >> 24) & 0xff); \
	} while (0)
#define SX64(o, v) do { \
		for (i = 0; i < 8; i++) \
			sx[(o)+i] = (uint8_t)(((v) >> (8 * i)) & 0xff); \
	} while (0)
	SX32(0, 0x7ffu);		/* stx_mask: type/mode/nlink/ino/size */
	SX32(4, 4096);			/* stx_blksize */
	SX32(16, 1);			/* stx_nlink */
	SX32(20, 0);			/* stx_uid */
	SX32(24, 0);			/* stx_gid */
	sx[28] = (uint8_t)(mode & 0xff);
	sx[29] = (uint8_t)(mode >> 8);
	SX64(32, ino);
	SX64(40, size);
	SX64(48, (size + 511) / 512);
#undef SX32
#undef SX64
	if (copyout(p, ubuf, sx, sizeof(sx)) != 0)
		return -EFAULT;
	return 0;
}

static long long
sys_getdents64(struct proc *p, int fd, unsigned long long ubuf,
    unsigned long long count)
{
	uint8_t buf[1024];
	struct file *f;
	unsigned long long used = 0;

	if (fd < 0 || fd >= NOFILE || !p->files[fd].used)
		return -EBADF;
	f = &p->files[fd];
	if (!f->is_dir)
		return -ENOTDIR;

	while (used + 32 <= count && used + 32 <= sizeof(buf)) {
		char name[208];
		unsigned long long child;
		unsigned char dtype;
		unsigned int next, nlen, rl, i;
		uint8_t *e;

		if (btrfs_readdir(f->ino, f->off, &next, name, &child,
		    &dtype) != 0)
			break;
		for (nlen = 0; name[nlen]; nlen++)
			continue;
		rl = (24 + nlen + 1 + 7) & ~7u;
		if (used + rl > count || used + rl > sizeof(buf))
			break;
		e = buf + used;
		for (i = 0; i < 8; i++) {
			e[i] = (uint8_t)(child >> (8 * i));
			e[8 + i] = (uint8_t)((unsigned long long)next >>
			    (8 * i));
		}
		e[16] = (uint8_t)(rl & 0xff);
		e[17] = (uint8_t)(rl >> 8);
		switch (dtype) {
		case 1: e[18] = 8; break;	/* REG */
		case 2: e[18] = 4; break;	/* DIR */
		case 7: e[18] = 10; break;	/* LNK */
		default: e[18] = 0; break;	/* UNKNOWN */
		}
		for (i = 0; i <= nlen; i++)
			e[19 + i] = (uint8_t)name[i];
		for (i = 19 + nlen + 1; i < rl; i++)
			e[i] = 0;
		used += rl;
		f->off = next;
	}
	if (used == 0)
		return 0;
	if (copyout(p, ubuf, buf, used) != 0)
		return -EFAULT;
	return (long long)used;
}

static long long
sys_read(struct proc *p, int fd, unsigned long long ubuf,
    unsigned long long len)
{
	static uint8_t kbuf[4096];
	unsigned long long got = 0;
	unsigned int r;

	if (fd < 0 || fd >= NOFILE || !p->files[fd].used)
		return -EBADF;
	if (p->files[fd].is_pipe)
		return pipe_read(p, p->files[fd].pipe, ubuf, len);
	if (p->files[fd].is_console) {
		/* console: block for >= 1 char */
		for (;;) {
			int c = kbd_getchar();

			if (c >= 0) {
				kbuf[got++] = (uint8_t)c;
				break;
			}
			p->state = WAITING;
			schedule();
			p->state = RUNNING;
		}
		while (got < sizeof(kbuf) && got < len) {
			int c = kbd_getchar();

			if (c < 0)
				break;
			kbuf[got++] = (uint8_t)c;
		}
		if (copyout(p, ubuf, kbuf, got) != 0)
			return -EFAULT;
		return (long long)got;
	}
	if (p->files[fd].off >= p->files[fd].size)
		return 0;
	{
		unsigned long long n = p->files[fd].size -
		    p->files[fd].off;

		if (n > len)
			n = len;
		if (n > sizeof(kbuf))
			n = sizeof(kbuf);
		if (have_btrfs && p->files[fd].ino)
			r = btrfs_read_file(p->files[fd].ino,
			    p->files[fd].off, (unsigned int)n, kbuf);
		else {
			struct fatent fe;

			fe.cluster = p->files[fd].fat_cluster;
			fe.size = (unsigned int)p->files[fd].size;
			r = fat_read_at(&fe, p->files[fd].off,
			    (unsigned int)n, kbuf);
		}
		if (copyout(p, ubuf, kbuf, r) != 0)
			return -EFAULT;
		p->files[fd].off += r;
		return (long long)r;
	}
}

static long long
sys_write(struct proc *p, int fd, unsigned long long ubuf,
    unsigned long long len)
{
	static uint8_t kbuf[4096];
	unsigned long long n = len, chunk;

	if (fd < 0 || fd >= NOFILE || !p->files[fd].used)
		return -EBADF;
	if (p->files[fd].is_pipe)
		return pipe_write(p, p->files[fd].pipe, ubuf, len);
	if (!p->files[fd].is_console)
		return -EBADF;			/* rootfs is read-only */
	while (n > 0) {
		chunk = n > sizeof(kbuf) ? sizeof(kbuf) : n;
		if (copyin(p, kbuf, ubuf + (len - n), chunk) != 0)
			return -EFAULT;
		console_write((const char *)kbuf, chunk);
		n -= chunk;
	}
	return (long long)len;
}

static long long
sys_open(struct proc *p, unsigned long long upath)
{
	char path[256];
	unsigned long long ino, size = 0;
	unsigned short mode;
	unsigned int fatclus;
	int fd, j;

	if (copyinstr(p, path, upath, sizeof(path)) < 0)
		return -EFAULT;
	if (fs_stat(path, &ino, &size, &mode, &fatclus) != 0)
		return -ENOENT;
	for (j = 0; j < NOFILE; j++)
		if (!p->files[j].used) {
			fd = j;
			p->files[fd].used = 1;
			p->files[fd].ino = ino;
			p->files[fd].size = size;
			p->files[fd].off = 0;
			p->files[fd].fat_cluster = fatclus;
			p->files[fd].is_dir =
			    (mode & 0170000) == 0040000;
			return fd;
		}
	return -EBADF;
}

static long long
sys_stat(struct proc *p, int dirfd, unsigned long long upath,
    unsigned long long ust)
{
	char path[256];
	unsigned long long ino, size = 0;
	unsigned short mode;
	unsigned int fatclus;
	uint8_t sb[144];
	int i;

	if (copyinstr(p, path, upath, sizeof(path)) < 0)
		return -EFAULT;
	/*
	 * fstat() on a descriptor has been implemented as
	 * newfstatat(fd, "", ...) since glibc 2.32, and AT_EMPTY_PATH
	 * semantics mean "stat the descriptor itself".  Treating "" as a
	 * path made fstat report the root directory's regular-file mode,
	 * so opendir() bailed out with ENOTDIR and `ls <dir>` never even
	 * reached getdents64.
	 */
	if (path[0] == 0) {
		if (dirfd < 0 || dirfd >= NOFILE || !p->files[dirfd].used)
			return -ENOENT;
		ino = p->files[dirfd].ino;
		size = p->files[dirfd].size;
		mode = p->files[dirfd].is_console ? 0020620 :
		    p->files[dirfd].is_dir ? 0040755 : 0100644;
		fatclus = 0;
	} else if (fs_stat(path, &ino, &size, &mode, &fatclus) != 0)
		return -ENOENT;
	for (i = 0; i < 144; i++)
		sb[i] = 0;
	sb[16] = 1;				/* st_nlink */
	for (i = 0; i < 4; i++)
		sb[24 + i] = (uint8_t)(mode >> (8 * i));
	for (i = 0; i < 8; i++)
		sb[8 + i] = (uint8_t)(ino >> (8 * i));
	for (i = 0; i < 8; i++)
		sb[48 + i] = (uint8_t)(size >> (8 * i));
	if (copyout(p, ust, sb, 144) != 0)
		return -EFAULT;
	return 0;
}

static long long
sys_brk(struct proc *p, unsigned long long addr)
{
	unsigned long long old = p->brk, a, va;

	if (addr == 0)
		return (long long)p->brk;
	if (addr < p->brk) {
		p->brk = addr;
		return (long long)addr;
	}
	a = (addr + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	for (va = (old + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1); va < a;
	    va += PAGE_SIZE) {
		unsigned long long pg = alloc_phys();
		uint64_t *z;
		int k;

		if (pg == 0)
			return -ENOMEM;
		z = (uint64_t *)phys2virt(pg);
		for (k = 0; k < 512; k++)
			z[k] = 0;
		if (vmm_map(p->cr3, va, pg, PTE_USER_RW) != 0)
			return -ENOMEM;
	}
	p->brk = a;
	return (long long)addr;
}

static long long
sys_mmap(struct proc *p, unsigned long long len)
{
	unsigned long long base = p->mmap_top, va, total;

	if (len == 0)
		return -EINVAL;
	total = (len + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	for (va = base; va < base + total; va += PAGE_SIZE) {
		unsigned long long pg = alloc_phys();
		uint64_t *z;
		int k;

		if (pg == 0)
			return -ENOMEM;
		z = (uint64_t *)phys2virt(pg);
		for (k = 0; k < 512; k++)
			z[k] = 0;
		if (vmm_map(p->cr3, va, pg, PTE_USER_RW) != 0)
			return -ENOMEM;
	}
	p->mmap_top = base + total;
	return (long long)base;
}

/* fork: everything the frame-copying caller needs */
static struct proc *
fork_child(struct proc *p, unsigned long long *frame)
{
	extern char syscall_ret[];
	struct proc *c = 0;
	int i, j, maxpid = 0;
	unsigned long long *save, *dst;

	for (i = 0; i < NPROC; i++)
		if (proc[i].state == UNUSED) {
			c = &proc[i];
			break;
		}
	{
		extern void console_puts(const char *);

		if (c == 0) {
			console_puts("FORK fail: no slot\r\n");
			return 0;
		}
	}

	c->cr3 = vmm_new();
	if (c->cr3 == 0) {
		extern void console_puts(const char *);

		console_puts("FORK fail: vmm_new\r\n");
		return 0;
	}
	{
		unsigned long long base = pmm_stack_alloc();

		if (base == 0) {
			extern void console_puts(const char *);

			vmm_destroy_user(c->cr3);
			free_phys(c->cr3 & ~0xfffull);
			console_puts("FORK fail: kstack\r\n");
			return 0;
		}
		c->kstack = (unsigned long long)phys2virt(base) +
		    KSTACK_PAGES * PAGE_SIZE;
	}

	vmm_copy_range(p->cr3, c->cr3, USER_BASE,
	    p->brk > p->user_top ? p->brk : p->user_top);
	vmm_copy_range(p->cr3, c->cr3, p->stack_lo, STACK_TOP);
	vmm_copy_range(p->cr3, c->cr3, MMAP_BASE, p->mmap_top);
	for (j = 0; j < NPROC; j++)
		if (proc[j].state != UNUSED && proc[j].pid > maxpid)
			maxpid = proc[j].pid;
	c->pid = maxpid + 1;
	c->ppid = p->pid;
	c->exit_code = 0;
	c->brk = p->brk;
	c->mmap_top = p->mmap_top;
	c->user_top = p->user_top;
	c->stack_lo = p->stack_lo;
	c->fsbase = p->fsbase;
	c->name = p->name;
	for (j = 0; j < NOFILE; j++) {
		c->files[j] = p->files[j];
		if (c->files[j].used && c->files[j].is_pipe)
			pipe_ref(&c->files[j]);
	}

	/* child kernel stack, from top down:
	 *   [syscall frame 0xb0][ret=&syscall_ret][6 saved regs]
	 * schedule() will `ret` into syscall_ret which pops the frame
	 * and irets to userland with RAX=0 (child's fork result) */
	dst = (unsigned long long *)(c->kstack - 0xb0);
	for (j = 0; j < 0xb0 / 8; j++)
		dst[j] = frame[j];
	dst[FR_RAX / 8] = 0;
	/* schedule()'s save area: rflags, six callee-saved regs, ret */
	save = (unsigned long long *)(c->kstack - 0xb0 - 64);
	save[0] = 0x202;			/* RFLAGS: IF set */
	for (j = 1; j <= 6; j++)
		save[j] = 0;
	save[7] = (unsigned long long)(unsigned long)syscall_ret;
	c->ksp = (unsigned long long)(unsigned long)save;
	c->state = RUNNABLE;
	return c;
}

static long long
sys_wait(struct proc *p, unsigned long long ustatus)
{
	int i, found;

	for (;;) {
		found = 0;
		for (i = 0; i < NPROC; i++) {
			if (proc[i].state != UNUSED &&
			    proc[i].ppid == p->pid)
				found = 1;
			if (proc[i].state == ZOMBIE &&
			    proc[i].ppid == p->pid) {
				int code = proc[i].exit_code;
				int cpid = proc[i].pid;
				int st = (code & 0xff) << 8;

				if (ustatus)
					copyout(p, ustatus, &st, 4);
				proc[i].state = UNUSED;
				proc_free(&proc[i]);
				return cpid;
			}
		}
		if (!found)
			return -ECHILD;
		p->state = WAITING;
		schedule();
		p->state = RUNNING;
	}
}

static void
wake_parent(struct proc *p)
{
	int i;

	for (i = 0; i < NPROC; i++)
		if (proc[i].state != UNUSED && proc[i].pid == p->ppid &&
		    proc[i].state == WAITING)
			proc[i].state = RUNNABLE;
}

/*
 * A CPU exception raised in ring 3 is the userland process' problem,
 * not the kernel's: mark it a zombie (exit status 128+sig) and switch
 * away.  Without this a crashing program takes the whole machine down
 * with a panic dump.
 */
void
proc_fault_exit(int sig)
{
	struct proc *p = curproc;

	if (p == 0 || p->state == UNUSED) {
		for (;;)
			__asm__ volatile("cli; hlt");
	}
	p->exit_code = (128 + sig) & 0xff;
	p->state = ZOMBIE;
	wake_parent(p);
	schedule();
	for (;;)
		__asm__ volatile("hlt");
}

static long long
sys_exit(struct proc *p, int code)
{
	p->exit_code = code & 0xff;
	p->state = ZOMBIE;
	wake_parent(p);
	schedule();
	/* reaped later; never return to user */
	for (;;)
		__asm__ volatile("hlt");
}

static long long
sys_uname(struct proc *p, unsigned long long ubuf)
{
	static const char un[6][65] = {
		"VodyaOS", "vodya", "0.2.0",
		"#1 Unix Seventh Edition lineage", "x86_64", "(none)"
	};
	int i;

	for (i = 0; i < 6; i++)
		if (copyout(p, ubuf + 65 * i, un[i], 65) != 0)
			return -EFAULT;
	return 0;
}

static long long
sys_readv_write(struct proc *p, int is_write, int fd,
    unsigned long long iov, unsigned long long iovcnt)
{
	unsigned long long i;
	long long total = 0;

	for (i = 0; i < iovcnt && i < 32; i++) {
		uint8_t tmp[32];
		unsigned long long base = 0, len = 0;
		long long r;
		int k;

		if (copyin(p, tmp, iov + 16 * i, 16) != 0)
			return -EFAULT;
		for (k = 0; k < 8; k++) {
			base |= ((unsigned long long)tmp[k]) << (8 * k);
			len |= ((unsigned long long)tmp[8 + k]) << (8 * k);
		}
		r = is_write ?
		    sys_write(p, fd, base, len) :
		    sys_read(p, fd, base, len);
		if (r < 0)
			return r;
		total += r;
		if ((unsigned long long)r < len)
			break;
	}
	return total;
}

/* ---------------------------------------------------------- dispatch */

void
syscall_dispatch(unsigned long long *frame)
{
	struct proc *p = curproc;
	unsigned long long nr = frame[FR_RAX / 8];
	long long ret = -ENOSYS;

	if (p == 0)
		return;
	p->state = RUNNING;

	/* SFMASK cleared IF on syscall entry; the kernel runs with
	 * interrupts on (the tick preempts, IRQ1 feeds the keyboard). */
	sti();

	switch (nr) {
	case 0:					/* read */
		ret = sys_read(p, (int)frame[FR_RDI / 8],
		    frame[FR_RSI / 8], frame[FR_RDX / 8]);
		break;
	case 7:					/* poll */
		ret = sys_poll(p, frame[FR_RDI / 8], frame[FR_RSI / 8]);
		break;
	case 23:				/* select */
		ret = sys_select(p, frame[FR_RDI / 8], frame[FR_RSI / 8],
		    frame[FR_RDX / 8], frame[FR_R10 / 8],
		    frame[FR_R8 / 8], 0);
		break;
	case 270:				/* pselect6 */
		ret = sys_select(p, frame[FR_RDI / 8], frame[FR_RSI / 8],
		    frame[FR_RDX / 8], frame[FR_R10 / 8],
		    frame[FR_R8 / 8], 1);
		break;
	case 109:				/* setpgid */
	case 112:				/* setsid */
	case 157:				/* prctl */
	case 267:				/* syncfs */
	case 273:				/* set_robust_list */
		ret = 0;
		break;
	case 111:				/* getpgrp */
		ret = (long long)p->pid;
		break;
	case 201: {				/* time */
		unsigned long long t = jiffies / 100;

		if (frame[FR_RDI / 8] &&
		    copyout(p, frame[FR_RDI / 8], &t, 8) != 0)
			ret = -EFAULT;
		else
			ret = (long long)t;
		break;
	}
	case 302: {				/* prlimit64 */
		unsigned long long lim[2];

		lim[0] = ~0ull;			/* RLIM_INFINITY */
		lim[1] = ~0ull;
		if (frame[FR_RDX / 8] &&
		    copyout(p, frame[FR_RDX / 8], lim, 16) != 0)
			ret = -EFAULT;
		else
			ret = 0;
		break;
	}
	case 1:					/* write */
		ret = sys_write(p, (int)frame[FR_RDI / 8],
		    frame[FR_RSI / 8], frame[FR_RDX / 8]);
		break;
	case 2:					/* open */
		ret = sys_open(p, frame[FR_RDI / 8]);
		break;
	case 3:					/* close */
		if ((int)frame[FR_RDI / 8] >= 0 &&
		    (int)frame[FR_RDI / 8] < NOFILE) {
			int cfd = (int)frame[FR_RDI / 8];

			if (p->files[cfd].is_pipe)
				pipe_close(p, cfd);
			else
				p->files[cfd].used = 0;
		}
		ret = 0;
		break;
	case 332:				/* statx */
		ret = sys_statx(p, (int)frame[FR_RDI / 8],
		    frame[FR_RSI / 8], frame[FR_R10 / 8],
		    frame[FR_R8 / 8]);
		break;
	case 217:				/* getdents64 */
		ret = sys_getdents64(p, (int)frame[FR_RDI / 8],
		    frame[FR_RSI / 8], frame[FR_RDX / 8]);
		break;
	case 22:				/* pipe */
		ret = sys_pipe(p, frame[FR_RDI / 8]);
		break;
	case 293:				/* pipe2 */
		ret = sys_pipe(p, frame[FR_RDI / 8]);
		break;
	case 5: {				/* fstat */
		uint8_t sb[144];
		int fd = (int)frame[FR_RDI / 8];
		int i;

		if (fd < 0 || fd >= NOFILE || !p->files[fd].used)
			return -EBADF;
		for (i = 0; i < 144; i++)
			sb[i] = 0;
		sb[16] = 1;			/* st_nlink */
		for (i = 0; i < 8; i++)
			sb[56 + i] = (uint8_t)(4096 >> (8 * i));
		if (p->files[fd].is_console) {
			/* console: char device, st_mode 0020620 */
			for (i = 0; i < 4; i++)
				sb[24 + i] =
				    (uint8_t)(0020620 >> (8 * i));
		} else {
			unsigned long long sz = p->files[fd].size;
			unsigned int mode = p->files[fd].is_dir ?
			    0040755 : 0100644;

			for (i = 0; i < 4; i++)
				sb[24 + i] =
				    (uint8_t)(mode >> (8 * i));
			for (i = 0; i < 8; i++)
				sb[48 + i] =
				    (uint8_t)(sz >> (8 * i));
		}
		if (copyout(p, frame[FR_RSI / 8], sb, 144) != 0)
			ret = -EFAULT;
		else
			ret = 0;
		break;
	}
	case 8:					/* lseek */
		if ((int)frame[FR_RDI / 8] > 2 &&
		    (int)frame[FR_RDI / 8] < NOFILE &&
		    p->files[(int)frame[FR_RDI / 8]].used) {
			struct file *f =
			    &p->files[(int)frame[FR_RDI / 8]];
			unsigned long long off = frame[FR_RSI / 8];
			int whence = (int)frame[FR_RDX / 8];

			if (whence == 0)
				f->off = (unsigned int)off;
			else if (whence == 1)
				f->off += (unsigned int)off;
			else if (whence == 2)
				f->off = (unsigned int)f->size;
			ret = (long long)f->off;
		} else
			ret = -EBADF;
		break;
	case 9:					/* mmap (anon) */
		ret = sys_mmap(p, frame[FR_RSI / 8]);
		break;
	case 10:				/* mprotect */
	case 11:				/* munmap */
		ret = 0;
		break;
	case 12:				/* brk */
		ret = sys_brk(p, frame[FR_RDI / 8]);
		break;
	case 13:				/* rt_sigaction */
	case 14:				/* rt_sigprocmask */
	case 131:				/* sigaltstack */
	case 218:				/* set_tid_address */
		ret = (long long)p->pid;
		break;
	case 16:				/* ioctl */
		ret = sys_ioctl(p, (int)frame[FR_RDI / 8],
		    frame[FR_RSI / 8], frame[FR_RDX / 8]);
		break;
	case 20:				/* writev */
		ret = sys_readv_write(p, 1, (int)frame[FR_RDI / 8],
		    frame[FR_RSI / 8], frame[FR_RDX / 8]);
		break;
	case 21: {				/* access */
		char path[256];

		if (copyinstr(p, path, frame[FR_RDI / 8],
		    sizeof(path)) < 0)
			ret = -EFAULT;
		else {
			unsigned long long ino, size;
			unsigned short mode;
			unsigned int fc;

			ret = fs_stat(path, &ino, &size, &mode, &fc);
		}
		break;
	}
	case 24:				/* sched_yield */
		p->state = RUNNABLE;
		schedule();
		p->state = RUNNING;
		ret = 0;
		break;
	case 32: {				/* dup */
		int ofd = (int)frame[FR_RDI / 8];
		int j;

		ret = -EBADF;
		if (ofd >= 0 && ofd < NOFILE && p->files[ofd].used)
			for (j = 0; j < NOFILE; j++)
				if (!p->files[j].used) {
					p->files[j] = p->files[ofd];
					pipe_ref(&p->files[j]);
					ret = j;
					break;
				}
		break;
	}
	case 33: {				/* dup2 */
		int ofd = (int)frame[FR_RDI / 8];
		int nfd = (int)frame[FR_RSI / 8];

		if (ofd >= 0 && ofd < NOFILE && nfd >= 0 &&
		    nfd < NOFILE && p->files[ofd].used) {
			if (p->files[nfd].used && p->files[nfd].is_pipe)
				pipe_close(p, nfd);
			p->files[nfd] = p->files[ofd];
			pipe_ref(&p->files[nfd]);
			ret = nfd;
		} else
			ret = -EBADF;
		break;
	}
	case 39:				/* getpid */
		ret = (long long)p->pid;
		break;
	case 41:				/* socket */
		ret = -ENOSYS;
		break;
	case 56:				/* clone */
		if ((frame[FR_RDI / 8] & 0x100) == 0) {
			/* fork-like clone: fall through to fork logic */
			{
				struct proc *c = fork_child(p, frame);

				ret = c ? (long long)c->pid : -ENOMEM;
			}
		} else
			ret = -ENOSYS;		/* threads: no */
		break;
	case 57:				/* fork */
	case 58: {				/* vfork */
		struct proc *c = fork_child(p, frame);

		ret = c ? (long long)c->pid : -ENOMEM;
		break;
	}
	case 59: {				/* execve */
		char path[256];
		char *argv[16], *envp[16];
		unsigned long long uargv = frame[FR_RSI / 8];
		unsigned long long uenvp = frame[FR_RDX / 8];
		int na = 0, ne = 0;

		if (copyinstr(p, path, frame[FR_RDI / 8],
		    sizeof(path)) < 0) {
			ret = -EFAULT;
			break;
		}
		while (uargv && na < 15) {
			unsigned long long a;

			if (copyin(p, &a, uargv + 8 * na, 8) != 0 || !a)
				break;
			{
				static char astr[16][128];

				copyinstr(p, astr[na], a, 128);
				argv[na] = astr[na];
			}
			na++;
		}
		argv[na] = 0;
		while (uenvp && ne < 15) {
			unsigned long long a;

			if (copyin(p, &a, uenvp + 8 * ne, 8) != 0 || !a)
				break;
			{
				static char estr[16][128];

				copyinstr(p, estr[ne], a, 128);
				envp[ne] = estr[ne];
			}
			ne++;
		}
		envp[ne] = 0;
		execve_proc(p, path, argv, envp);/* irets, no return */
		ret = -ENOENT;			/* exec failed */
		break;
	}
	case 60:				/* exit */
	case 231:				/* exit_group */
		sys_exit(p, (int)frame[FR_RDI / 8]);
		break;
	case 61:				/* wait4 */
		ret = sys_wait(p, frame[FR_RSI / 8]);
		break;
	case 62:				/* kill */
	case 234:				/* tgkill */
		ret = 0;
		break;
	case 63:				/* uname */
		ret = sys_uname(p, frame[FR_RDI / 8]);
		break;
	case 72: {				/* fcntl */
		int fd = (int)frame[FR_RDI / 8];
		unsigned long long cmd = frame[FR_RSI / 8];
		unsigned long long arg = frame[FR_RDX / 8];

		if (fd < 0 || fd >= NOFILE || !p->files[fd].used) {
			ret = -EBADF;
			break;
		}
		if (cmd == 0 || cmd == 1030) {	/* F_DUPFD / F_DUPFD_CLOEXEC */
			int j, nfd = -EBADF;

			for (j = (int)arg; j < NOFILE; j++)
				if (!p->files[j].used) {
					p->files[j] = p->files[fd];
					pipe_ref(&p->files[j]);
					nfd = j;
					break;
				}
			if (nfd < 0 && (int)arg <= 0)
				nfd = -EINVAL;
			ret = nfd;
			break;
		}
		ret = 0;			/* F_GETFL/F_SETFL/etc */
		break;
	}
	case 79: {				/* getcwd */
		const char *root = "/";
		unsigned long long sz = frame[FR_RSI / 8];

		ret = 2;
		if (sz >= 2)
			if (copyout(p, frame[FR_RDI / 8], root, 2) != 0)
				ret = -EFAULT;
		break;
	}
	case 80:				/* chdir */
		ret = 0;
		break;
	case 89:				/* readlink */
		ret = -ENOENT;
		break;
	case 96: {				/* gettimeofday (tv in RDI) */
		uint8_t t[16];
		unsigned long long sec = jiffies / 100;
		unsigned long long usec = (jiffies % 100) * 10000ull;
		int i;

		if (frame[FR_RDI / 8] == 0) {
			ret = 0;
			break;
		}
		for (i = 0; i < 8; i++) {
			t[i] = (uint8_t)(sec >> (8 * i));
			t[8 + i] = (uint8_t)(usec >> (8 * i));
		}
		ret = copyout(p, frame[FR_RDI / 8], t, 16) != 0 ?
		    -EFAULT : 0;
		break;
	}
	case 228: {				/* clock_gettime */
		uint8_t t[16];
		unsigned long long sec = jiffies / 100;
		unsigned long long nsec = (jiffies % 100) * 10000000ull;
		int i;

		for (i = 0; i < 8; i++) {
			t[i] = (uint8_t)(sec >> (8 * i));
			t[8 + i] = (uint8_t)(nsec >> (8 * i));
		}
		if (copyout(p, frame[FR_RSI / 8], t, 16) != 0)
			ret = -EFAULT;
		else
			ret = 0;
		break;
	}
	case 102:				/* getuid */
	case 104:				/* getgid */
	case 107:				/* geteuid */
	case 108:				/* getegid */
		ret = 0;
		break;
	case 110:				/* getppid */
		ret = (long long)p->ppid;
		break;
	case 158:				/* arch_prctl */
		if (frame[FR_RDI / 8] == 0x1002 ||
		    frame[FR_RDI / 8] == 0x1003) {
			p->fsbase = frame[FR_RSI / 8];
			cpu_fsbase_set(p->fsbase);
			ret = 0;
		} else
			ret = -EINVAL;
		break;
	case 153:				/* times */
		ret = (long long)jiffies;
		break;
	case 257:				/* openat */
		ret = sys_open(p, frame[FR_RSI / 8]);
		break;
	case 262:				/* newfstatat */
		ret = sys_stat(p, (int)frame[FR_RDI / 8],
		    frame[FR_RSI / 8], frame[FR_RDX / 8]);
		break;
	case 318: {				/* getrandom */
		uint8_t rnd[64];
		unsigned long long n = frame[FR_RSI / 8], k;

		if (n > 64)
			n = 64;
		for (k = 0; k < n; k++)
			rnd[k] = (uint8_t)(jiffies * 2654435761ull +
			    k * 97 + frame[FR_RIP / 8]);
		if (copyout(p, frame[FR_RDI / 8], rnd, n) != 0)
			ret = -EFAULT;
		else
			ret = (long long)n;
		break;
	}
	default:
		ret = -ENOSYS;
		break;
	}

	frame[FR_RAX / 8] = (unsigned long long)ret;
}
