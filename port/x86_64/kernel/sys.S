/*
 * SYSCALL entry/exit (EFER.SCE fast path).
 *
 * On entry the CPU has put the user RIP in rcx and user RFLAGS in
 * r11 and switched to kernel CS/SS (STAR).  RSP is still the user
 * stack, so the first order of business is the kernel stack switch,
 * then build the SAME trapframe layout the interrupt path uses
 * (intr.S/intr.c) -- fork's child stack setup (syscall.c) and the
 * dispatch offsets depend on it:
 *
 * No swapgs is used: a context resumed by schedule() may come from
 * an interrupt taken in user mode (GS already user) or from kernel
 * code (GS kernel), so an unconditional swapgs is wrong either way.
 * The single CPU keeps the user RSP and kernel stack top in plain
 * globals instead.
 *
 *   [ss][rsp][rflags][cs][rip][err=0][vec=-1][r15..rax]   (0xb0 bytes)
 *
 * Return value travels in frame RAX.  syscall_ret is the epilogue
 * label: a forked child's first schedule() rets here with the
 * parent's frame already on its kernel stack (RAX forced to 0).
 *
 * SFMASK clears IF on entry, so syscall_dispatch re-enables
 * interrupts; sysretq reloads user RIP from rcx, RFLAGS from r11.
 */

	.text

.globl syscall_entry
syscall_entry:
	movq	%rsp, syscall_user_rsp(%rip)	/* save user RSP */
	movq	syscall_kstack(%rip), %rsp	/* per-proc kernel stack */

	pushq	$0x23				/* user SS */
	pushq	syscall_user_rsp(%rip)		/* user RSP */
	pushq	%r11				/* user RFLAGS */
	pushq	$0x2b				/* user CS */
	pushq	%rcx				/* user RIP */
	pushq	$0				/* no error code */
	pushq	$-1				/* vector: syscall */

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

	cld
	movq	%rsp, %rdi
	call	syscall_dispatch		/* syscall.c */

	/* fallthrough into the shared epilogue */

.globl syscall_ret
syscall_ret:
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
	popq	%rcx				/* user RIP */
	popq	%rbx
	popq	%rax
	addq	$16, %rsp			/* drop vector + error code */
	popq	%rcx				/* user RIP (frame slot) */
	addq	$8, %rsp			/* skip user CS */
	popq	%r11				/* user RFLAGS */
	popq	%rsp				/* user RSP; the SS slot is
						 * abandoned on the kernel
						 * stack -- every entry resets
						 * RSP from syscall_kstack/TSS */

	sysretq

	.data
.globl syscall_user_rsp
syscall_user_rsp:
	.quad 0
.globl syscall_kstack
syscall_kstack:
	.quad 0
