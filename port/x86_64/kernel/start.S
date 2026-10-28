/*
 * x86_64 kernel entry point (Limine boot protocol).
 *
 * The historical V7 startup code (l.s / mch.s) built the PDP-11
 * MMU and then jumped into main().  Limine hands us long mode with
 * the kernel mapped, so this entry only has to establish a stack
 * and clear the direction flag.
 *
 * Minimal boot: limine_start() reports on the COM1 serial line and
 * halts.  Calling main() is deferred until the kernel has an IDT,
 * a clock and page tables (HANDOFF.md section 8.5) - re-enable the
 * call below at that point.
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
	call	limine_start
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
