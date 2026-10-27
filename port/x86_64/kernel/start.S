/*
 * x86_64 kernel entry point.
 *
 * The historical V7 startup code (l.s / mch.s) built the PDP-11
 * MMU and then jumped into main().  This port keeps the same
 * contract: establish a stack, clear the direction flag and call
 * main().  Booting is deliberately out of scope for now; the image
 * is linked as a flat ELF64 kernel so that all of the portable V7
 * code can be compiled and inspected on a modern toolchain.
 */

	.text
	.globl	_start
	.globl	start
	.type	_start,@function
_start:
start:
	cli
	cld
	xorl	%ebp, %ebp
	leaq	kernel_stack_top(%rip), %rsp
	call	main
1:
	hlt
	jmp	1b
	.size	_start, .-_start

	.section .bss
	.balign	16
	.globl	kernel_stack
kernel_stack:
	.space	32768
	.globl	kernel_stack_top
kernel_stack_top:
