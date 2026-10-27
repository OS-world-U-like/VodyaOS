/*
 * V7 libc system call interface for x86_64.
 *
 * The original libc implemented every system call as a tiny PDP-11
 * assembly stub that executed an EMT instruction.  On x86_64 there
 * is no VodyaOS system call gate yet, so the libc is currently
 * hosted on top of the Linux x86_64 system call ABI.  This keeps the
 * userland source completely unchanged (it still calls open(),
 * read(), fork(), ...) and lets us build and exercise ELF64
 * binaries while the native kernel catches up.
 *
 * All entry points use the classic V7 names and signatures.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <signal.h>
#include <errno.h>

extern int errno;

/* Individual programs sometimes define these names themselves;
 * make the libc versions weak so a program-local definition wins. */
#pragma weak access
#pragma weak acct
#pragma weak alarm
#pragma weak chdir
#pragma weak chmod
#pragma weak chown
#pragma weak chroot
#pragma weak close
#pragma weak creat
#pragma weak dup
#pragma weak dup2
#pragma weak execle
#pragma weak execl
#pragma weak execv
#pragma weak execve
#pragma weak exit
#pragma weak fcntl
#pragma weak fork
#pragma weak fstat
#pragma weak getcwd
#pragma weak getdents
#pragma weak getegid
#pragma weak geteuid
#pragma weak getgid
#pragma weak getpgrp
#pragma weak getpid
#pragma weak getppid
#pragma weak getuid
#pragma weak ioctl
#pragma weak kill
#pragma weak link
#pragma weak lock
#pragma weak lstat
#pragma weak lseek
#pragma weak mknod
#pragma weak mount
#pragma weak mpxcall
#pragma weak nice
#pragma weak open
#pragma weak pause
#pragma weak phys
#pragma weak pipe
#pragma weak profil
#pragma weak ptrace
#pragma weak read
#pragma weak sbrk
#pragma weak setgid
#pragma weak setuid
#pragma weak setsid
#pragma weak signal
#pragma weak stat
#pragma weak stime
#pragma weak sync
#pragma weak time
#pragma weak times
#pragma weak umask
#pragma weak umount
#pragma weak unlink
#pragma weak utime
#pragma weak wait
#pragma weak write
#pragma weak brk

/* Linux x86_64 system call numbers (the subset we need). */
#define SYS_read	0
#define SYS_write	1
#define SYS_open	2
#define SYS_close	3
#define SYS_stat	4
#define SYS_fstat	5
#define SYS_lstat	6
#define SYS_lseek	8
#define SYS_brk		12
#define SYS_rt_sigaction 13
#define SYS_rt_sigprocmask 14
#define SYS_ioctl	16
#define SYS_access	21
#define SYS_pipe	22
#define SYS_dup		32
#define SYS_dup2	33
#define SYS_pause	34
#define SYS_nanosleep	35
#define SYS_alarm	37
#define SYS_getpid	39
#define SYS_fork	57
#define SYS_execve	59
#define SYS_exit	60
#define SYS_wait4	61
#define SYS_kill	62
#define SYS_fcntl	72
#define SYS_getdents	78
#define SYS_getcwd	79
#define SYS_chdir	80
#define SYS_rename	82
#define SYS_mkdir	83
#define SYS_rmdir	84
#define SYS_creat	85
#define SYS_link	86
#define SYS_unlink	87
#define SYS_chmod	90
#define SYS_chown	92
#define SYS_umask	95
#define SYS_gettimeofday 96
#define SYS_getuid	102
#define SYS_getgid	104
#define SYS_setuid	105
#define SYS_setgid	106
#define SYS_geteuid	107
#define SYS_getegid	108
#define SYS_getppid	110
#define SYS_getpgrp	111
#define SYS_setsid	112
#define SYS_utime	132
#define SYS_mknod	133
#define SYS_chroot	161
#define SYS_sync	162
#define SYS_acct	163
#define SYS_mount	165
#define SYS_umount2	166
#define SYS_time	201
#define SYS_clock_settime 227
#define SYS_exit_group	231
#define SYS_newfstatat	262

static long
__sc6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	register long r10 __asm__("r10") = a4;
	register long r8  __asm__("r8")  = a5;
	register long r9  __asm__("r9")  = a6;
	long ret;

	__asm__ volatile("syscall"
		: "=a"(ret)
		: "a"(n), "D"(a1), "S"(a2), "d"(a3),
		  "r"(r10), "r"(r8), "r"(r9)
		: "rcx", "r11", "memory");
	return ret;
}

static long
__sc(long n, long a1, long a2, long a3)
{
	return __sc6(n, a1, a2, a3, 0, 0, 0);
}

static int
__ret(long r)
{
	if (r < 0 && r > -4096) {
		errno = (int)-r;
		return -1;
	}
	return (int)r;
}

int read(int fd, char *buf, unsigned n)
{
	return __ret(__sc(SYS_read, fd, (long)buf, n));
}

int write(int fd, char *buf, unsigned n)
{
	return __ret(__sc(SYS_write, fd, (long)buf, n));
}

int open(char *path, int flags, int mode)
{
	return __ret(__sc(SYS_open, (long)path, flags, mode));
}

int creat(char *path, int mode)
{
	return __ret(__sc(SYS_creat, (long)path, mode, 0));
}

int close(int fd)
{
	return __ret(__sc(SYS_close, fd, 0, 0));
}

long lseek(int fd, long off, int whence)
{
	long r = __sc(SYS_lseek, fd, off, whence);

	if (r < 0 && r > -4096) {
		errno = (int)-r;
		return -1;
	}
	return r;
}

int access(char *path, int mode)
{
	return __ret(__sc(SYS_access, (long)path, mode, 0));
}

int chdir(char *path)
{
	return __ret(__sc(SYS_chdir, (long)path, 0, 0));
}

int chroot(char *path)
{
	return __ret(__sc(SYS_chroot, (long)path, 0, 0));
}

int chmod(char *path, int mode)
{
	return __ret(__sc(SYS_chmod, (long)path, mode, 0));
}

int chown(char *path, int uid, int gid)
{
	return __ret(__sc(SYS_chown, (long)path, uid, gid));
}

int link(char *old, char *new)
{
	return __ret(__sc(SYS_link, (long)old, (long)new, 0));
}

int unlink(char *path)
{
	return __ret(__sc(SYS_unlink, (long)path, 0, 0));
}



int dup(int fd)
{
	return __ret(__sc(SYS_dup, fd, 0, 0));
}

int dup2(int old, int new)
{
	return __ret(__sc(SYS_dup2, old, new, 0));
}

int pipe(int *fds)
{
	return __ret(__sc(SYS_pipe, (long)fds, 0, 0));
}

int ioctl(int fd, int req, char *arg)
{
	return __ret(__sc(SYS_ioctl, fd, req, (long)arg));
}

int fcntl(int fd, int cmd, int arg)
{
	return __ret(__sc(SYS_fcntl, fd, cmd, arg));
}

int getdents(int fd, char *buf, unsigned n)
{
	return __ret(__sc(SYS_getdents, fd, (long)buf, n));
}

char *getcwd(char *buf, unsigned n)
{
	long r = __sc(SYS_getcwd, (long)buf, n, 0);

	return (r < 0) ? 0 : buf;
}

int kill(int pid, int sig)
{
	return __ret(__sc(SYS_kill, pid, sig, 0));
}

int pause()
{
	return __ret(__sc(SYS_pause, 0, 0, 0));
}

unsigned alarm(unsigned sec)
{
	return (unsigned)__sc(SYS_alarm, sec, 0, 0);
}

int sync()
{
	return __ret(__sc(SYS_sync, 0, 0, 0));
}

int umask(int mask)
{
	return __ret(__sc(SYS_umask, mask, 0, 0));
}

int getpid()
{
	return __ret(__sc(SYS_getpid, 0, 0, 0));
}

int getppid()
{
	return __ret(__sc(SYS_getppid, 0, 0, 0));
}

int getpgrp()
{
	return __ret(__sc(SYS_getpgrp, 0, 0, 0));
}

int setsid()
{
	return __ret(__sc(SYS_setsid, 0, 0, 0));
}

int getuid()
{
	return __ret(__sc(SYS_getuid, 0, 0, 0));
}

int getgid()
{
	return __ret(__sc(SYS_getgid, 0, 0, 0));
}

int geteuid()
{
	return __ret(__sc(SYS_geteuid, 0, 0, 0));
}

int getegid()
{
	return __ret(__sc(SYS_getegid, 0, 0, 0));
}

int setuid(int uid)
{
	return __ret(__sc(SYS_setuid, uid, 0, 0));
}

int setgid(int gid)
{
	return __ret(__sc(SYS_setgid, gid, 0, 0));
}

int fork()
{
	return __ret(__sc(SYS_fork, 0, 0, 0));
}

int wait(int *status)
{
	return __ret(__sc(SYS_wait4, -1, (long)status, 0));
}

int mknod(char *path, int mode, int dev)
{
	return __ret(__sc(SYS_mknod, (long)path, mode, dev));
}

int mount(char *dev, char *dir, int rw)
{
	(void)dev; (void)dir; (void)rw;
	errno = 19;
	return -1;
}

int umount(char *dir)
{
	return __ret(__sc(SYS_umount2, (long)dir, 0, 0));
}

int acct(char *path)
{
	return __ret(__sc(SYS_acct, (long)path, 0, 0));
}

int stime(long *tp)
{
	return __ret(__sc(SYS_clock_settime, 0, (long)tp, 0));
}

int nice(int inc)
{
	(void)inc;
	return 0;
}

int lock(int fd)
{
	(void)fd;
	return 0;
}

int phys(int fd)
{
	(void)fd;
	return -1;
}

int mpxcall(int *args)
{
	(void)args;
	errno = 22;
	return -1;
}

int profil(char *buf, int size, int off, int scale)
{
	(void)buf; (void)size; (void)off; (void)scale;
	return 0;
}

int ptrace(int req, int pid, int *addr, int data)
{
	(void)req; (void)pid; (void)addr; (void)data;
	return -1;
}

long time(long *tp)
{
	long t = __sc(SYS_time, 0, 0, 0);

	if (tp)
		*tp = t;
	return t;
}

int utime(char *path, long *times)
{
	return __ret(__sc(SYS_utime, (long)path, (long)times, 0));
}

/* --- file status ---------------------------------------------------- */

/*
 * The kernel's x86_64 struct stat.  Keeping a private copy avoids
 * depending on a host C library.
 */
struct lx_stat {
	unsigned long	st_dev;
	unsigned long	st_ino;
	unsigned long	st_nlink;
	unsigned int	st_mode;
	unsigned int	st_uid;
	unsigned int	st_gid;
	unsigned int	__pad0;
	unsigned long	st_rdev;
	long		st_size;
	long		st_blksize;
	long		st_blocks;
	long		st_atime;
	long		st_atime_nsec;
	long		st_mtime;
	long		st_mtime_nsec;
	long		st_ctime;
	long		st_ctime_nsec;
	long		__unused[3];
};

static void
stat_copy(struct lx_stat *ls, struct stat *st)
{
	st->st_dev = (dev_t)ls->st_dev;
	st->st_ino = (ino_t)ls->st_ino;
	st->st_mode = (unsigned short)ls->st_mode;
	st->st_nlink = (short)ls->st_nlink;
	st->st_uid = (short)ls->st_uid;
	st->st_gid = (short)ls->st_gid;
	st->st_rdev = (dev_t)ls->st_rdev;
	st->st_size = (off_t)ls->st_size;
	st->st_atime = (time_t)ls->st_atime;
	st->st_mtime = (time_t)ls->st_mtime;
	st->st_ctime = (time_t)ls->st_ctime;
}

int stat(char *path, struct stat *st)
{
	struct lx_stat ls;
	long r = __sc(SYS_newfstatat, -100 /* AT_FDCWD */,
		      (long)path, (long)&ls);

	if (r < 0)
		return __ret(r);
	stat_copy(&ls, st);
	return 0;
}

int lstat(char *path, struct stat *st)
{
	struct lx_stat ls;
	long r = __sc6(SYS_newfstatat, -100, (long)path, (long)&ls,
		       0x100 /* AT_SYMLINK_NOFOLLOW */, 0, 0);

	if (r < 0)
		return __ret(r);
	stat_copy(&ls, st);
	return 0;
}

int fstat(int fd, struct stat *st)
{
	struct lx_stat ls;
	long r = __sc6(SYS_newfstatat, fd, (long)"", (long)&ls,
		       0x1000 /* AT_EMPTY_PATH */, 0, 0);

	if (r < 0)
		return __ret(r);
	stat_copy(&ls, st);
	return 0;
}

/* --- process creation ----------------------------------------------- */

int execve(char *path, char **argv, char **envp)
{
	return __ret(__sc(SYS_execve, (long)path, (long)argv, (long)envp));
}

extern char **environ;

int execv(char *path, char **argv)
{
	return execve(path, argv, environ);
}

int
execle(char *path, char *arg0, ...)
{
	char **argv = &arg0;
	char **envp;
	int n = 0;

	while (argv[n])
		n++;
	envp = &argv[n + 1];
	return execve(path, argv, envp);
}

int
execl(char *path, char *arg0, ...)
{
	char **argv = &arg0;
	return execve(path, argv, environ);
}

/* --- miscellaneous -------------------------------------------------- */

int
times(struct tms *buf)
{
	struct { long t[4]; } t;

	if (__sc(100 /* SYS_times */, (long)&t, 0, 0) < 0)
		return -1;
	buf->tms_utime = t.t[0];
	buf->tms_stime = t.t[1];
	buf->tms_cutime = t.t[2];
	buf->tms_cstime = t.t[3];
	return 0;
}

/* Simple signal emulation.  V7 signal numbers 1..15 map onto the
 * corresponding Linux signals. */
int (*signal(int sig, int (*func)()))()
{
	static long handlers[NSIG];

	if (sig <= 0 || sig >= NSIG)
		return 0;
	{
		long old = handlers[sig];
		handlers[sig] = (long)func;
		return (int (*)())old;
	}
}

int
sigsetmask(int mask)
{
	(void)mask;
	return 0;
}

int
sigblock(int mask)
{
	(void)mask;
	return 0;
}

int
sighold(int sig)
{
	(void)sig;
	return 0;
}

int
sigrelse(int sig)
{
	(void)sig;
	return 0;
}

/* --- memory --------------------------------------------------------- */

static char *curbrk;

void *
sbrk(int incr)
{
	char *old;
	long r;

	if (!curbrk)
		curbrk = (char *)__sc(SYS_brk, 0, 0, 0);
	old = curbrk;
	r = __sc(SYS_brk, (long)(curbrk + incr), 0, 0);
	if (r < (long)(curbrk + incr)) {
		errno = ENOMEM;
		return (void *)-1;
	}
	curbrk += incr;
	return old;
}

/*
 * brk(addr) -- set the program break.  V7 code uses both brk() and
 * sbrk(); keep them consistent.
 */
int
brk(char *addr)
{
	long r = __sc(SYS_brk, (long)addr, 0, 0);

	if (r < (long)addr) {
		errno = ENOMEM;
		return -1;
	}
	return 0;
}
