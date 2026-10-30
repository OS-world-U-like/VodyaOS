/*
 * Interrupt/trap entry stubs for the x86_64 port.
 *
 * Each of the 256 IDT vectors gets a small stub that normalises the
 * stack (exceptions with error codes keep theirs, the others get a
 * dummy zero), pushes the vector number and saves every general
 * register, then calls the C dispatcher with a struct trapframe.
 * iretq undoes everything on the way out.
 *
 * Stack layout below intr_common (see struct trapframe in intr.c):
 *   [ss][rsp][rflags][cs][rip][err][vector][r15..rax]
 *
 * intr.c only needs the stub addresses (intr_stub[256]).
 */

	.text

intr_common:
	pushq	%rax
	pushq	%rbx
	pushq	%rcx
	pushq	%rdx
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	pushq	%r8
	pushq	%r9
	pushq	%r10
	pushq	%r11
	pushq	%r12
	pushq	%r13
	pushq	%r14
	pushq	%r15
	cld					/* C ABI wants DF clear */
	movq	%rsp, %rdi			/* frame pointer */
	call	intr_dispatch			/* void intr_dispatch(uint64_t *frame) */
	popq	%r15
	popq	%r14
	popq	%r13
	popq	%r12
	popq	%r11
	popq	%r10
	popq	%r9
	popq	%r8
	popq	%rbp
	popq	%rsi
	popq	%rdi
	popq	%rdx
	popq	%rcx
	popq	%rbx
	popq	%rax
	addq	$16, %rsp			/* drop vector + error code */
	iretq

/* IESTUB n err - stub for vector n; err = 1 when the CPU pushes a code */
.macro	IESTUB n err
	.globl	intr_stub\n
intr_stub\n:
	.if \err
		pushq	$\n			/* vector above CPU's error code */
		jmp	intr_common
	.else
		pushq	$0			/* dummy error code */
		pushq	$\n
		jmp	intr_common
	.endif
.endm

IESTUB	0 0
IESTUB	1 0
IESTUB	2 0
IESTUB	3 0
IESTUB	4 0
IESTUB	5 0
IESTUB	6 0
IESTUB	7 0
IESTUB	8 1				/* #DF has an error code */
IESTUB	9 0
IESTUB	10 1				/* #TS */
IESTUB	11 1				/* #NP */
IESTUB	12 1				/* #SS */
IESTUB	13 1				/* #GP */
IESTUB	14 1				/* #PF */
IESTUB	15 0
IESTUB	16 0
IESTUB	17 1				/* #AC */
IESTUB	18 0
IESTUB	19 0
IESTUB	20 0
IESTUB	21 0
IESTUB	22 0
IESTUB	23 0
IESTUB	24 0
IESTUB	25 0
IESTUB	26 0
IESTUB	27 0
IESTUB	28 0
IESTUB	29 0
IESTUB	30 0
IESTUB	31 0

/* IRQs, vectors 32..47: no CPU error codes */
IESTUB	32 0
IESTUB	33 0
IESTUB	34 0
IESTUB	35 0
IESTUB	36 0
IESTUB	37 0
IESTUB	38 0
IESTUB	39 0
IESTUB	40 0
IESTUB	41 0
IESTUB	42 0
IESTUB	43 0
IESTUB	44 0
IESTUB	45 0
IESTUB	46 0
IESTUB	47 0

/* vectors 48..255: catch-all stubs, no error codes */
.altmacro
.set	__gvec, 48
.rept	256 - 48
	IESTUB	%__gvec 0
	.set	__gvec, __gvec + 1
.endr
.noaltmacro
