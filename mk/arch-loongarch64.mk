# Architecture description: loongarch64  [PLANNED / NOT YET IMPLEMENTED]
# ----------------------------------------------------------------------
# Planned exactly like aarch64 (see mk/arch-aarch64.mk).  Differences:
#
#   CC      := clang --target=loongarch64-unknown-none-elf
#   LD      := ld.lld -m elf64loongarch
#   EMU     := qemu-loongarch64
#   IMAGE_BASE := 0x400000
#
# port/loongarch64/kernel/{start.S,context.S,arch.c,kernel.ld} must provide:
#   - kernel entry, trap/interrupt vector setup, spl*/splx (LoongArch uses
#     CRMD/PRMD interrupt levels - map V7 spl0..spl7 onto them),
#   - copyin/copyout/fubyte/subyte/fuword/suword (use the LoongArch
#     exception-restore trick or access-with-fixup tables),
#   - clearseg/copyseg, save/resume (label_t is long[8] on all modern ports),
#   - the mch.s globals: struct user u, cputype, waitloc, lks (fake).
# port/loongarch64/libc/{start.S,setjmp.S,syscall.c,...} use the Linux
# LoongArch syscall ABI (a7=nr, a0-a5 args) so qemu-loongarch64 can run the
# result during bring-up.

CC      :=
AS      :=
LD      :=
AR      :=
EMU     ?= qemu-loongarch64
ARCHCFLAGS    :=
KERNEL_CFLAGS :=
IMAGE_BASE    :=
KERNEL_LD     := port/$(ARCH)/kernel/kernel.ld
KERNEL_EXTRA_OBJS := start.o context.o
ARCH_SUPPORTED := no
