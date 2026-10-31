/*
 * The VodyaOS executive: ELF64 loader, process table, and the
 * ring-3 transition -- enough of the real Linux x86_64 ABI to run
 * static GNU binaries (bash, coreutils) and later dinit as PID 1.
 *
 * Root filesystem: btrfs on partition 2 (primary), FAT32 ESP as a
 * fallback bootstrap source.  fd 0/1/2 are the kernel console "tty"
 * (keyboard ring buffer in, framebuffer/serial out).
 *
 * Userland layout:
 *   0x0000000000400000  ELF segments / brk heap grows above
 *   0x0000010000000000  mmap arena
 *   0x00007ffff7ff0000  stack top (grows down)
 */

#include "proc.h"

#define PAGE_SIZE	4096ul
#define PTE_P		0x001
#define PTE_W		0x002
#define PTE_U		0x004
#define PTE_NX		0x8000000000000000ull
#define PTE_USER_RX	(PTE_P | PTE_U)
#define PTE_USER_RO	(PTE_P | PTE_U | PTE_NX)
#define PTE_USER_RW	(PTE_P | PTE_W | PTE_U | PTE_NX)

#define phys2virt(p)	((void *)((uint64_t)(p) + hhdm_offset))

/* --------------------------------------------------------- extern APIs */

/* pmm.c */
uint64_t alloc_phys(void);
void free_phys(uint64_t p);
uint64_t alloc_run(uint64_t npages, uint64_t *got);
uint64_t pmm_stack_alloc(void);
void pmm_stack_free(uint64_t base);
uint64_t pmm_free(void);
/* vmm.c */
uint64_t vmm_new(void);
int vmm_map(uint64_t cr3, uint64_t va, uint64_t pa, uint64_t flags);
uint64_t vmm_phys(uint64_t cr3, uint64_t va);
void vmm_switch(uint64_t cr3);
void vmm_destroy_user(uint64_t cr3);
/* intr.c */
void sti(void);
void cli(void);
/* console.c */
void console_puts(const char *s);
void console_write(const char *s, unsigned long n);
/* limine.c */
void putdec(unsigned long long v);
void ok_prefix(void);
void fail_prefix(void);
void line_end(void);
/* cpu.c */
void cpu_init(void);
void cpu_kstack_set(unsigned long long top, unsigned long long rsp0);
void cpu_fsbase_set(unsigned long long base);
/* keyboard.c */
int kbd_getchar(void);
void kbd_echo_enable(int on);
/* pmm/limine */
extern unsigned long long hhdm_offset;
extern volatile unsigned long long jiffies;
/* btrfs.c */
int btrfs_init(void);
int btrfs_lookup(const char *path, unsigned long long *ino,
    unsigned long long *size, unsigned short *mode);
unsigned int btrfs_read_file(unsigned long long ino, unsigned long long off,
    unsigned int len, unsigned char *buf);
/* fat32.c */
int fat_init(unsigned int lba);
int fat_lookup(const char *path, struct fatent *out);
unsigned int fat_read_at(const struct fatent *e, unsigned int off,
    unsigned int len, unsigned char *buf);

/* ------------------------------------------------------------ proc table */

void proc_exec_fds(struct proc *p);

struct proc proc[NPROC];
struct proc *curproc;
static int next_pid = 1;

/* rootfs availability, set by limine.c boot flow */
int have_btrfs;
int have_fat;

/* filled by syscall entry (sys.S) */
void syscall_dispatch(unsigned long long *frame);
/* scheduler hook (syscall.c, called from the PIT tick) */
void schedule(void);

/* ------------------------------------------------------------- helpers */

static void *
zalloc_page(void)
{
	uint64_t p = alloc_phys();
	uint64_t *v;
	int i;

	if (p == 0)
		return 0;
	v = (uint64_t *)phys2virt(p);
	for (i = 0; i < 512; i++)
		v[i] = 0;
	return v;
}

static void
u64le(uint8_t *p, uint64_t v)
{
	int i;

	for (i = 0; i < 8; i++)
		p[i] = (uint8_t)(v >> (8 * i));
}

static uint64_t
le64(const uint8_t *p)
{
	uint64_t v = 0;
	int i;

	for (i = 0; i < 8; i++)
		v |= ((uint64_t)p[i]) << (8 * i);
	return v;
}

/* ------------------------------------------------------ file sources */

/* read `len` at `off` from a rootfs path (btrfs first, FAT fallback) */
static unsigned int
fs_read(const char *path, unsigned long long off, unsigned int len,
    unsigned char *buf)
{
	unsigned long long ino = 0, size = 0;
	unsigned short mode;
	struct fatent fe;

	if (have_btrfs &&
	    btrfs_lookup(path, &ino, &size, &mode) == 0)
		return btrfs_read_file(ino, off, len, buf);
	if (have_fat && fat_lookup(path, &fe) == 0)
		return fat_read_at(&fe, (unsigned int)off, len, buf);
	return 0;
}

/*
 * elf_load reads the image in 4 KiB pieces; resolving the path through
 * the btrfs directory tree for every piece made exec of a 7 MiB binary
 * take minutes under TCG.  Resolve once, then read by inode/FAT entry.
 */
static unsigned long long ld_ino;
static struct fatent ld_fe;
static int ld_src;		/* 1 = btrfs inode, 2 = FAT entry */

static unsigned int
file_read(unsigned long long off, unsigned int len, unsigned char *buf)
{
	if (ld_src == 1)
		return btrfs_read_file(ld_ino, off, len, buf);
	if (ld_src == 2)
		return fat_read_at(&ld_fe, (unsigned int)off, len, buf);
	return 0;
}

/* ------------------------------------------------------- ELF64 loader */

struct elf_stat {
	unsigned long long entry;
	unsigned long long phoff_vaddr;		/* AT_PHDR */
	unsigned long long brk_base;
	unsigned long long top;
};

static int
elf_load(struct proc *p, const char *path, struct elf_stat *st)
{
	static uint8_t hdr[4096];
	unsigned int n;
	uint64_t i, phoff, phnum, phentsize;
	unsigned short phentsz, phnum16;
	unsigned long long load_min = ~0ull, load_max = 0;
	unsigned long long phdr_vaddr = 0;

	{
		unsigned long long fsz = 0;
		unsigned short fmode;

		ld_src = 0;
		if (have_btrfs &&
		    btrfs_lookup(path, &ld_ino, &fsz, &fmode) == 0)
			ld_src = 1;
		else if (have_fat && fat_lookup(path, &ld_fe) == 0)
			ld_src = 2;
	}

	n = file_read(0, 4096, hdr);
	if (n < 64)
		return -1;
	if (hdr[0] != 0x7f || hdr[1] != 'E' || hdr[2] != 'L' || hdr[3] != 'F')
		return -1;
	if (hdr[4] != 2 || hdr[5] != 1)		/* 64-bit LE */
		return -1;
	if (hdr[16] != 2)			/* ET_EXEC (static) */
		return -1;

	st->entry = le64(hdr + 24);
	phoff = le64(hdr + 32);
	phentsz = hdr[54] | (hdr[55] << 8);
	phnum16 = hdr[56] | (hdr[57] << 8);
	phnum = phnum16;
	phentsize = phentsz;

	for (i = 0; i < phnum; i++) {
		uint8_t ph[64];
		unsigned int type;
		unsigned long long off, vaddr, filesz, memsz;
		uint64_t va;

		if (file_read(phoff + i * phentsize, 64, ph) < 64)
			return -1;
		type = ph[0] | (ph[1] << 8) | (ph[2] << 16) |
		    ((unsigned int)ph[3] << 24);
		if (type != 1)			/* PT_LOAD */
			continue;
		off = le64(ph + 8);
		vaddr = le64(ph + 16);
		filesz = le64(ph + 32);
		memsz = le64(ph + 40);


		/* map [vaddr, vaddr+memsz) with the segment's own
		 * permissions.  PT_LOAD p_flags: PF_X=1, PF_W=2, PF_R=4.
		 * Non-executable pages get NX; an executable page must
		 * NOT, or the first fetch from the ELF entry point dies
		 * with a #PF (P=0,I/D=1 under TCG).  The kernel still
		 * writes the contents through the HHDM, so read-only
		 * segments need no W bit in the user mapping. */
		{
			unsigned int pflags = ph[4] | (ph[5] << 8) |
			    (ph[6] << 16) | ((unsigned int)ph[7] << 24);
			uint64_t segflags = PTE_P | PTE_U;

			if (pflags & 2)		/* PF_W */
				segflags |= PTE_W;
			if (!(pflags & 1))	/* !PF_X */
				segflags |= PTE_NX;

			for (va = vaddr & ~(PAGE_SIZE - 1);
			    va < vaddr + memsz; va += PAGE_SIZE) {
				uint64_t pg;

				if (vmm_phys(p->cr3, va))
					continue;	/* first PT_LOAD wins */
				pg = alloc_phys();
				if (pg == 0)
					return -1;
				if (vmm_map(p->cr3, va, pg, segflags) != 0)
					return -1;
			}
		}
		/* copy file content page-wise */
		{
			unsigned long long done = 0;

			while (done < filesz) {
				uint64_t va = vaddr + done;
				uint64_t pa = vmm_phys(p->cr3,
				    va & ~(PAGE_SIZE - 1));
				uint8_t *dst;
				uint64_t in = va & (PAGE_SIZE - 1);
				uint64_t chunk = PAGE_SIZE - in;

				if (chunk > filesz - done)
					chunk = filesz - done;
				if (pa == 0)
					return -1;
				dst = (uint8_t *)phys2virt(pa) + in;
				if (file_read(off + done,
				    (unsigned int)chunk, dst) < chunk)
					return -1;
				done += chunk;
			}
			/* zero bss tail */
			while (done < memsz) {
				uint64_t va = vaddr + done;
				uint64_t pa = vmm_phys(p->cr3,
				    va & ~(PAGE_SIZE - 1));
				uint8_t *dst;
				uint64_t in = va & (PAGE_SIZE - 1);
				uint64_t chunk = PAGE_SIZE - in;

				if (chunk > memsz - done)
					chunk = memsz - done;
				if (pa == 0)
					return -1;
				dst = (uint8_t *)phys2virt(pa) + in;
				{
					uint64_t k;

					for (k = 0; k < chunk; k++)
						dst[k] = 0;
				}
				done += chunk;
			}
		}
		if (vaddr < load_min)
			load_min = vaddr;
		if (vaddr + memsz > load_max)
			load_max = vaddr + memsz;
		if (phoff >= off && phoff < off + filesz)
			phdr_vaddr = vaddr + (phoff - off);
	}

	if (load_min == ~0ull)
		return -1;
	st->phoff_vaddr = phdr_vaddr;
	st->brk_base = (load_max + 0xffff) & ~0xffffull;
	st->top = load_max;
	return 0;
}

/* --------------------------------------------------------- proc setup */

static struct proc *
proc_alloc(const char *name)
{
	int i, j;
	struct proc *p;

	for (i = 0; i < NPROC; i++)
		if (proc[i].state == UNUSED)
			break;
	if (i == NPROC)
		return 0;
	p = &proc[i];

	p->cr3 = vmm_new();
	if (p->cr3 == 0) {
		console_puts("DBG proc_alloc: vmm_new failed\r\n");
		return 0;
	}

	/* kernel stack: contiguous pages, accessed via HHDM */
	{
		uint64_t base = pmm_stack_alloc();

		if (base == 0) {
			console_puts("DBG proc_alloc: kstack alloc failed\r\n");
			vmm_destroy_user(p->cr3);
			free_phys(p->cr3);
			return 0;
		}
		p->kstack = (uint64_t)phys2virt(base) +
		    KSTACK_PAGES * PAGE_SIZE;
	}

	p->state = RUNNABLE;
	p->pid = next_pid++;
	p->ksp = 0;		/* not yet on the CPU: no saved stack */
	p->ppid = 0;
	p->exit_code = 0;
	p->brk = 0;
	p->mmap_top = MMAP_BASE;
	p->user_top = 0;
	p->stack_lo = STACK_TOP - STACK_SIZE;
	p->fsbase = 0;
	p->name = name;
	for (j = 0; j < NOFILE; j++) {
		uint8_t *f = (uint8_t *)&p->files[j];
		int k;

		for (k = 0; k < (int)sizeof(struct file); k++)
			f[k] = 0;
	}
	return p;
}

void
proc_free(struct proc *p)
{
	int j;

	vmm_destroy_user(p->cr3);
	free_phys(p->cr3);
	/* kernel stack: free via HHDM -> phys */
	{
		uint64_t base = (p->kstack - KSTACK_PAGES * PAGE_SIZE) -
		    hhdm_offset;

		pmm_stack_free(base);
	}
	for (j = 0; j < NOFILE; j++)
		p->files[j].used = 0;
	p->state = UNUSED;
	p->name = 0;
}

/* map user stack, push argv/envp/auxv */
static unsigned long long
stack_setup(struct proc *p, char **argv, int argc, char **envp, int envc)
{
	uint64_t va, sp;
	uint64_t argv_ptrs[16], envp_ptrs[32];
	uint64_t auxv[8];
	uint8_t random16[16];
	int i;
	uint64_t pa;

	for (va = p->stack_lo; va < STACK_TOP; va += PAGE_SIZE) {
		pa = alloc_phys();
		if (pa == 0)
			return 0;
		if (vmm_map(p->cr3, va, pa, PTE_USER_RW) != 0)
			return 0;
	}

	/* AT_RANDOM bytes */
	for (i = 0; i < 16; i++)
		random16[i] = (uint8_t)(0x5a ^ (i * 37) ^
		    (jiffies & 0xff));
	sp = STACK_TOP - 256;
	sp &= ~0xfull;

	sp -= 16;
	pa = vmm_phys(p->cr3, sp & ~(PAGE_SIZE - 1));
	for (i = 0; i < 16; i++)
		((uint8_t *)phys2virt(pa))[(sp & (PAGE_SIZE - 1)) + i] =
		    random16[i];
	auxv[0] = 25;				/* AT_RANDOM */
	auxv[1] = sp;
	auxv[2] = 6;				/* AT_PAGESZ */
	auxv[3] = 4096;
	auxv[4] = 3;				/* AT_PHDR */
	auxv[5] = 0;				/* filled below if known */
	auxv[6] = 0;
	auxv[7] = 0;

	for (i = argc - 1; i >= 0; i--) {
		uint64_t len = 0;
		const char *s = argv[i];

		while (s[len]) len++;
		sp -= len + 1;
		{
			uint64_t k;
			uint64_t page = sp & ~(PAGE_SIZE - 1);
			uint64_t pp = vmm_phys(p->cr3, page);

			for (k = 0; k <= len; k++)
				((uint8_t *)phys2virt(pp))
				    [(sp + k) & (PAGE_SIZE - 1)] = s[k];
		}
		argv_ptrs[i] = sp;
	}
	for (i = envc - 1; i >= 0; i--) {
		uint64_t len = 0;
		const char *s = envp[i];

		while (s[len]) len++;
		sp -= len + 1;
		{
			uint64_t k;
			uint64_t pp = vmm_phys(p->cr3,
			    sp & ~(PAGE_SIZE - 1));

			for (k = 0; k <= len; k++)
				((uint8_t *)phys2virt(pp))
				    [(sp + k) & (PAGE_SIZE - 1)] = s[k];
		}
		envp_ptrs[i] = sp;
	}

	/* align vector start */
	sp &= ~0xfull;
	sp -= ((uint64_t)argc + 1 + envc + 8 + 2) * 8;
	sp &= ~0xfull;

#define PUSHV(v) do { \
		uint64_t pp_ = vmm_phys(p->cr3, sp & ~(PAGE_SIZE-1)); \
		u64le((uint8_t *)phys2virt(pp_) + (sp & (PAGE_SIZE-1)), (v)); \
		sp += 8; \
	} while (0)

	{
		uint64_t vec = sp;
		int k;

		PUSHV((uint64_t)argc);
		for (k = 0; k < argc; k++)
			PUSHV(argv_ptrs[k]);
		PUSHV(0);
		for (k = 0; k < envc; k++)
			PUSHV(envp_ptrs[k]);
		PUSHV(0);
		for (k = 0; k < 8; k++)
			PUSHV(auxv[k]);
		sp = vec;
	}
#undef PUSHV
	return sp;
}

/* --------------------------------------------------------- spawn/exec */

static char *bash_argv[] = { "/gnu/bin/bash", 0 };
static char *bash_envp[] = {
	"PATH=/gnu/bin:/bin:/usr/bin",
	"HOME=/",
	"TERM=linux",
	"PS1=vodya:\\w$ ",
	0
};

int
execve_proc(struct proc *p, const char *path, char **argv, char **envp)
{
	struct elf_stat st;
	unsigned long long sp;
	int argc = 0, envc = 0;
	char *a[16], *e[32];

	while (argv[argc] && argc < 15) { a[argc] = argv[argc]; argc++; }
	while (envp[envc] && envc < 31) { e[envc] = envp[envc]; envc++; }

	/*
	 * Address-space transition, atomic with respect to the timer.
	 *
	 * Order matters: the old PML4 is the *live* CR3, so it must not
	 * be freed before the CPU has left it.  vmm_new() therefore
	 * clones the kernel half out of the old tables, we switch, and
	 * only then release the old PML4.  Freeing it first let the
	 * next alloc_phys() hand the still-active PML4 back as a user
	 * page, and elf_load() overwrote PML4[511] with bash code --
	 * the kernel half vanished under our feet (CR2=0x...70ff8,
	 * #PF on the next stack push).
	 */
	cli();
	{
		uint64_t old = p->cr3;
		uint64_t nc = vmm_new();

		if (nc == 0) {
			sti();
			return -1;
		}
		/* Load into the new address space while the old one is
		 * still intact: execve of a missing/unreadable file must
		 * fail back into the caller with its mappings untouched.
		 * (Wiping first left the child with an empty CR3, so it
		 * resumed at a user RIP that no longer existed and died
		 * with a P=0 instruction-fetch #PF.) */
		vmm_switch(nc);
		p->cr3 = nc;

		if (elf_load(p, path, &st) != 0) {
			vmm_switch(old);
			p->cr3 = old;
			vmm_destroy_user(nc);
			free_phys(nc);
			sti();
			return -1;
		}

		/* success: the old address space is dead now */
		vmm_destroy_user(old);
		free_phys(old);
	}

	p->brk = st.brk_base;
	/* user_top = highest ELF address: bounds fork's address-space
	 * copy.  Never raise it to STACK_TOP -- fork scans [USER_BASE,
	 * user_top) page by page, and that range must stay small. */
	p->user_top = st.top;

	sp = stack_setup(p, a, argc, e, envc);
	if (sp == 0) {
		sti();
		return -1;
	}

	p->state = RUNNABLE;
	p->ksp = 0;				/* fresh: entered via iret */
	p->name = path;
	proc_exec_fds(p);			/* close-on-exec */


	/* switch into it */
	vmm_switch(p->cr3);
	cpu_fsbase_set(0);
	cpu_kstack_set(p->kstack, p->kstack);

	/* iretq to ring 3 */
	__asm__ volatile(
	    "movq %0, %%rsp\n"
	    "pushq $0x23\n"			/* user SS */
	    "pushq %1\n"			/* user RSP */
	    "pushq $0x202\n"			/* RFLAGS: IF=1 */
	    "pushq $0x2b\n"			/* user CS */
	    "pushq %2\n"			/* RIP */
	    "xorq %%rax, %%rax\n"
	    "xorq %%rbx, %%rbx\n"
	    "xorq %%rcx, %%rcx\n"
	    "xorq %%rdx, %%rdx\n"
	    "xorq %%rsi, %%rsi\n"
	    "xorq %%rdi, %%rdi\n"
	    "xorq %%rbp, %%rbp\n"
	    "xorq %%r8, %%r8\n"
	    "xorq %%r9, %%r9\n"
	    "xorq %%r10, %%r10\n"
	    "xorq %%r11, %%r11\n"
	    "xorq %%r12, %%r12\n"
	    "xorq %%r13, %%r13\n"
	    "xorq %%r14, %%r14\n"
	    "xorq %%r15, %%r15\n"
	    "iretq\n"
	    : : "r"(p->kstack), "r"(sp), "r"(st.entry) : "memory");
	return 0;				/* not reached */
}

void
proc_start(void)
{
	struct proc *p;

	p = proc_alloc("/gnu/bin/bash");
	if (p == 0) {
		fail_prefix();
		console_puts("Failed to allocate init process\r\n");
		line_end();
		for (;;)
			__asm__ volatile("hlt");
	}
	/* console fds */
	p->files[0].used = p->files[1].used = p->files[2].used = 1;
	p->files[0].is_console = p->files[1].is_console =
	    p->files[2].is_console = 1;
	curproc = p;

	/* userland owns the console line discipline now (bash/readline
	 * echoes); kernel-side echo would double every keystroke */
	kbd_echo_enable(0);

	ok_prefix();
	console_puts("Spawning /gnu/bin/bash as PID 1");
	line_end();

	execve_proc(p, "/gnu/bin/bash", bash_argv, bash_envp);
	/* not reached on success */
	fail_prefix();
	console_puts("exec /gnu/bin/bash failed\r\n");
	line_end();
	for (;;)
		__asm__ volatile("hlt");
}
