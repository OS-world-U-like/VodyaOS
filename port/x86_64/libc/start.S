/*
 * x86_64 userland entry point and C runtime startup.
 *
 * V7's crt0.s passed argc/argv and set _environ.  On the System V
 * ABI the process starts with argc at (%rsp), argv just above it and
 * envp after the NULL terminator of argv.
 */

	.text
	.globl	_start
	.type	_start,@function
_start:
	xorl	%ebp, %ebp
	movq	(%rsp), %rdi			/* argc */
	leaq	8(%rsp), %rsi			/* argv */
	leaq	16(%rsp,%rdi,8), %rdx		/* envp */
	movq	%rdx, environ(%rip)
	andq	$-16, %rsp
	call	main
	movl	%eax, %edi
	call	exit
1:
	hlt
	jmp	1b
	.size	_start, .-_start

	.bss
	.globl	environ
	.weak	environ
	.align	8
environ:
	.quad	0
