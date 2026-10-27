/*
 * x86_64 implementations of the low level context primitives that
 * the V7 scheduler expects (save()/resume()).
 *
 * label_t is long[8] in the x86_64 port:
 *   0 rbx, 1 rbp, 2 r12, 3 r13, 4 r14, 5 r15, 6 rsp, 7 rip
 */

	.text

	.globl	save
	.type	save,@function
save:
	movq	%rbx, 0(%rdi)
	movq	%rbp, 8(%rdi)
	movq	%r12, 16(%rdi)
	movq	%r13, 24(%rdi)
	movq	%r14, 32(%rdi)
	movq	%r15, 40(%rdi)
	leaq	8(%rsp), %rax
	movq	%rax, 48(%rdi)
	movq	(%rsp), %rax
	movq	%rax, 56(%rdi)
	xorl	%eax, %eax
	ret
	.size	save, .-save

	.globl	resume
	.type	resume,@function
resume:
	/* rdi = address space / process address (unused without an MMU),
	 * rsi = saved label */
	movq	0(%rsi), %rbx
	movq	8(%rsi), %rbp
	movq	16(%rsi), %r12
	movq	24(%rsi), %r13
	movq	32(%rsi), %r14
	movq	40(%rsi), %r15
	movq	48(%rsi), %rsp
	movl	$1, %eax
	jmp	*56(%rsi)
	.size	resume, .-resume

	.globl	idle
	.type	idle,@function
idle:
	sti
	hlt
	ret
	.size	idle, .-idle
