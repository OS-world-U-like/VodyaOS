/*
 * Shared executive structures between exec.c and syscall.c.
 * Offsets of state/cr3/kstack/ksp are load-bearing in schedule()'s
 * assembly - do not reorder without updating syscall.c.
 */

#ifndef PROC_H
#define PROC_H

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

#define NPROC		8
#define KSTACK_PAGES	16			/* 64 KiB */
#define NOFILE		16

#define USER_BASE	0x400000ull
#define MMAP_BASE	0x100000000000ull
#define STACK_TOP	0x7ffff7ff0000ull
#define STACK_SIZE	0x100000ull

enum pstate { UNUSED = 0, RUNNABLE = 1, RUNNING = 2, WAITING = 3,
	      ZOMBIE = 4 };

struct fatent {
	unsigned int cluster;
	unsigned int size;
};

struct pipe;

struct file {
	unsigned char used;
	unsigned char is_pipe;
	unsigned char pipe_rd;			/* pipe direction */
	unsigned char is_console;		/* console character device */
	unsigned char is_dir;			/* btrfs directory */
	unsigned long long ino;			/* btrfs inode, 0 = console */
	unsigned long long size;
	unsigned int off;
	unsigned int fat_cluster;		/* ESP fallback */
	struct pipe *pipe;
};

struct proc {
	int state;				/* 0x00 (asm: read) */
	int pid;				/* 0x04 */
	int ppid;				/* 0x08 */
	int exit_code;				/* 0x0c */
	unsigned long long cr3;			/* 0x10 (asm) */
	unsigned long long kstack;		/* 0x18 (asm) */
	unsigned long long ksp;			/* 0x20 (asm) */
	unsigned long long brk;
	unsigned long long mmap_top;
	unsigned long long user_top;
	unsigned long long stack_lo;
	unsigned long long fsbase;
	struct file files[NOFILE];
	const char *name;
};

#endif /* PROC_H */
