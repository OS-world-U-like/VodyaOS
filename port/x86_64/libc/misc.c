/*
 * Small pieces of the V7 C library that were historically written in
 * PDP-11 assembly or are needed by the x86_64 runtime.
 */

#include <stdio.h>

extern int errno;
long syscall(long, ...);

void _exit(int);
#pragma weak exit

/*
 * Historical naming note: on the PDP-11, cuexit.s implements C exit()
 * as symbol _exit, and fakcu.s provides C _cleanup() as the flush
 * hook.  Here exit() flushes stdio and exits.
 */
void
exit(int code)
{
	extern int _cleanup();

	_cleanup();
	_exit(code);
}

void
_exit(int code)
{
	__asm__ volatile("syscall"
		: : "a"(231L), "D"((long)code)
		: "rcx", "r11", "memory");
	for (;;)
		;
}

void
abort()
{
	_exit(1);
}

/* Floating point simulator hooks (PDP-11 only). */
void
fakcu()
{
}

void
fakfp()
{
}

void
ldfps(int x)
{
	(void)x;
}

/* Call profiling hook used by the V7 compiler's -p option. */
void
mcount()
{
}

/* Historical csv/cret helpers.  They are no-ops on x86_64. */
void
csv()
{
}

void
cret()
{
}

/* long arithmetic helpers used by the PDP-11 compiler.  x86_64 has
 * native 64-bit arithmetic, but these names are still referenced by a
 * few historical programs. */
long
ldiv(long a, long b)
{
	return a / b;
}

long
lrem(long a, long b)
{
	return a % b;
}

long
lmul(long a, long b)
{
	return a * b;
}

void *
memcpy(void *d, const void *s, unsigned long n)
{
	char *dp = d;
	const char *sp = s;

	while (n--)
		*dp++ = *sp++;
	return d;
}

void *
memmove(void *d, const void *s, unsigned long n)
{
	char *dp = d;
	const char *sp = s;

	if (dp < sp) {
		while (n--)
			*dp++ = *sp++;
	} else {
		dp += n;
		sp += n;
		while (n--)
			*--dp = *--sp;
	}
	return d;
}

void *
memset(void *d, int c, unsigned long n)
{
	char *dp = d;

	while (n--)
		*dp++ = c;
	return d;
}

int
memcmp(const void *a, const void *b, unsigned long n)
{
	const unsigned char *x = a, *y = b;

	while (n--) {
		if (*x != *y)
			return *x - *y;
		x++;
		y++;
	}
	return 0;
}

/* Compatibility with spell(1)'s historical V7 macro. */
int
Tolower(int c)
{
	return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}
