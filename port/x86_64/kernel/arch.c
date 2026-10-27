/*
 * x86_64 machine dependent helpers for the VodyaOS/V7 kernel.
 *
 * The original implementation of these routines lived in mch.s and
 * was written for the PDP-11 (MFPD/MTPD, segmentation registers,
 * PSW priority levels, ...).  This file supplies equivalent
 * operations using the x86_64 instruction set.  Where the original
 * code depended on the PDP-11 MMU we provide a simple direct-mapped
 * implementation; that is sufficient to compile and link the kernel
 * before the real VM/architecture layer is brought up.
 */

#include "h/param.h"
#include "h/types.h"
#include "h/systm.h"
#include "h/dir.h"
#include "h/user.h"
#include "h/seg.h"
#include "h/proc.h"

/* The PDP-11 kernel kept the u-area at absolute address 0140000 and
 * the "ka6" pointer in mch.s.  Give both of them normal storage. */
struct user u;

static struct { int r[16]; } fake_ka6;
physadr ka6 = (physadr)&fake_ka6;

static struct { int r[8]; } fake_lks;
physadr lks = (physadr)&fake_lks;

int cputype = 70;		/* pretend to be an 11/70 for the C code */

char *waitloc = 0;

/* Return value of the processor status word.  On the PDP-11 this
 * carried the interrupt priority.  On x86_64 we map spl levels onto
 * the interrupt flag: level 0 enables interrupts, everything above
 * disables them.  splx() restores the saved flags. */

static int
x86_spl(int level)
{
	unsigned long flags;

	__asm__ volatile("pushfq; popq %0" : "=r"(flags) : : "memory");
	if (level == 0)
		__asm__ volatile("sti" : : : "memory");
	else
		__asm__ volatile("cli" : : : "memory");
	return (int)flags;
}

int spl0() { return x86_spl(0); }
int spl1() { return x86_spl(1); }
int spl4() { return x86_spl(4); }
int spl5() { return x86_spl(5); }
int spl6() { return x86_spl(6); }
int spl7() { return x86_spl(7); }

int
splx(int flags)
{
	__asm__ volatile("pushq %0; popfq" : : "r"((long)flags) : "memory", "cc");
	return 0;
}

/* User <-> kernel copies.  Without a protected address space these
 * are plain memory moves. */

int
copyin(caddr_t from, caddr_t to, unsigned count)
{
	char *s = from, *d = to;
	unsigned i;

	for (i = 0; i < count; i++)
		d[i] = s[i];
	return 0;
}

int
copyout(caddr_t from, caddr_t to, unsigned count)
{
	return copyin(from, to, count);
}

int
copyiin(caddr_t from, caddr_t to, unsigned count)
{
	return copyin(from, to, count);
}

int
copyiout(caddr_t from, caddr_t to, unsigned count)
{
	return copyin(from, to, count);
}

int
fubyte(caddr_t addr)
{
	return *(unsigned char *)addr;
}

int
fuibyte(caddr_t addr)
{
	return fubyte(addr);
}

int
subyte(caddr_t addr, int value)
{
	*(unsigned char *)addr = value;
	return 0;
}

int
suibyte(caddr_t addr, int value)
{
	return subyte(addr, value);
}

int
fuiword(caddr_t addr)
{
	return *(int *)addr;
}

int
fuword(caddr_t addr)
{
	return *(int *)addr;
}

int
suiword(caddr_t addr, int value)
{
	*(int *)addr = value;
	return 0;
}

int
suword(caddr_t addr, int value)
{
	*(int *)addr = value;
	return 0;
}

/* A "segment" is one V7 page: 512 bytes. */

void
clearseg(int addr)
{
	char *p = (char *)(long)addr;
	int i;

	for (i = 0; i < 512; i++)
		p[i] = 0;
}

void
copyseg(int from, int to)
{
	char *s = (char *)(long)from;
	char *d = (char *)(long)to;
	int i;

	for (i = 0; i < 512; i++)
		d[i] = s[i];
}

/* Profiling hooks.  The PDP-11 implementation programmed the KW11-P
 * clock; there is no equivalent here (yet), so these are no-ops. */

void
addupc(caddr_t pc, void *prof, int n)
{
}

void
display()
{
}

int
backup(int *ar0)
{
	return 1;
}

void
savfp(int *fp)
{
}

void
restfp(int *fp)
{
}

void
stst(int *p)
{
	*p = 0;
}

/* Bootstrap entry points referenced by the old boot code. */

void
rkboot()
{
	panic("rkboot: no RK bootstrap on x86_64");
}

void
rpboot()
{
	panic("rpboot: no RP bootstrap on x86_64");
}
