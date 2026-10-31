/*
 * Interrupt/trap entry stubs for the x86_64 port.
 *
 * Each of the 256 IDT vectors gets a small stub that normalises the
 * stack (exceptions with error codes keep theirs, the others get a
 * dummy zero), pushes the vector number and saves every general
 * register, then calls the C dispatcher with a struct trapframe.
 * iretq undoes everything on the way out.
 *
 * What the CPU actually pushes (verified empirically against QEMU
 * TCG with -d int, for both a timer tick and #PF at CPL 0): in 64-bit
 * mode the CPU first aligns RSP down to 16 bytes and then ALWAYS
 * pushes five quads -- rip, cs, rflags, old rsp, old ss in ascending
 * memory order -- even for same-privilege kernel entries.  With the
 * stub's dummy err + vector below that, a kernel entry looks like
 * (ascending): vec@E, err@E+8, rip@E+0x10, cs@E+0x18, rflags@E+0x20,
 * X@E+0x28, SS@E+0x30, where X is the true interrupted RSP (E =
 * align_down(X) - 0x38 for X = 8 mod 16).  Ring-3 entries get the
 * same five-quad shape, so the interrupted RSP and SS can simply be
 * READ from E+0x28 / E+0x30 instead of being synthesised.  (A real
 * CPU pushes only three quads for same-ring entries; if this port is
 * ever moved to hardware, add shape detection here.)
 *
 * intr_common shifts the whole entry block down one quad into the
 * stub's own space and turns every frame into the same uniform
 * layout:
 *
 *   [ss][rsp][rflags][cs][rip][err][vector][r15..rax]   (0xb0 bytes)
 *
 * The shuffle only ever writes below the interrupted RSP.  The
 * epilogue is then one path for both rings.
 *
 * intr.c only needs the stub addresses (intr_stub[256]).
 */

	.text

intr_common:
	testb	$3, 0x18(%rsp)			/* CPU's CS quad: ring 3? */
	jnz	2f
	/*
	 * Kernel entry: rsp = E, and the stack holds (ascending)
	 * vec@E, err@E+8, rip@E+0x10, cs@E+0x18, rflags@E+0x20,
	 * X@E+0x28, SS@E+0x30 -- X = the true interrupted RSP, pushed
	 * by the CPU as part of its five-quad frame (see header).
	 * The uniform frame base is E-0x88: shift vec..rflags down
	 * 0x10, then copy X and SS into the two freed slots.  Every
	 * destination that overlaps a source is written only after
	 * that source has been read.
	 */
	subq	$0x18, %rsp			/* rsp = E-0x18 */
	pushq	%rax				/* stash interrupted RAX */
	/* shuffle (rsp = E-0x20) */
	movq	0x20(%rsp), %rax		/* vec     (E)       */
	movq	%rax, 0x10(%rsp)		/* -> E-0x10 */
	movq	0x28(%rsp), %rax		/* err     (E+0x08)  */
	movq	%rax, 0x18(%rsp)		/* -> E-0x08 */
	movq	0x30(%rsp), %rax		/* rip     (E+0x10)  */
	movq	%rax, 0x20(%rsp)		/* -> E       */
	movq	0x38(%rsp), %rax		/* cs      (E+0x18)  */
	movq	%rax, 0x28(%rsp)		/* -> E+0x08 */
	movq	0x40(%rsp), %rax		/* rflags  (E+0x20)  */
	movq	%rax, 0x30(%rsp)		/* -> E+0x10 */
	movq	0x48(%rsp), %rax		/* interrupted RSP: [E+0x28] */
	movq	%rax, 0x38(%rsp)		/* -> E+0x18 */
	movq	0x50(%rsp), %rax		/* interrupted SS:  [E+0x30] */
	movq	%rax, 0x40(%rsp)		/* -> E+0x20 */
	addq	$0x10, %rsp			/* rsp = E-0x10 (vec slot) */
	movq	-0x10(%rsp), %rax		/* recover interrupted RAX */
	jmp	3f
2:
3:
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
	addq	$16, %rsp			/* drop vector + error code:
						 * rsp = rip slot of the
						 * uniform frame (both rings) */
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
