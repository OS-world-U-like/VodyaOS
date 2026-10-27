# Architecture description: aarch64 (ARM64)  [PLANNED / NOT YET IMPLEMENTED]
# --------------------------------------------------------------------------
# The x86_64 port established the port/<arch>/ layout.  To add aarch64:
#
#   port/aarch64/kernel/{start.S,context.S,arch.c,kernel.ld}
#       - replaces usr/sys mch.s/l.s: trap entry, spl*, copyin/copyout,
#         fu*/su*, clearseg/copyseg, save/resume, and the mch-provided
#         globals (struct user u, cputype, ...).  See port/x86_64/kernel.
#   port/aarch64/libc/{start.S,setjmp.S,syscall.c,misc.c,format.c,scan.c}
#       - freestanding libc runtime; syscall wrappers use the Linux aarch64
#         syscall ABI (x8=nr, x0-x5 args) so binaries also run under
#         qemu-aarch64 for testing.
#   port/aarch64/libm/math.c, port/aarch64/libplot/plotstub.c
#       - copies of the x86_64 helpers (they are mostly arch-independent).
#
# Once the files exist, fill in the toolchain below:
#   CC      := clang --target=aarch64-unknown-none-elf
#   LD      := ld.lld -m aarch64linux  (or -m aarch64elf for the kernel)
#   IMAGE_BASE := 0x400000
#   KERNEL_CFLAGS := -mgeneral-regs-only   (V7 kernel has no FPU context)
#
# The build driver (tools/build.py) and Makefile are architecture-agnostic;
# only this file and the port/aarch64/ sources are arch-specific.

CC      :=
AS      :=
LD      :=
AR      :=
EMU     ?= qemu-aarch64
ARCHCFLAGS    :=
KERNEL_CFLAGS :=
IMAGE_BASE    :=
KERNEL_LD     := port/$(ARCH)/kernel/kernel.ld
KERNEL_EXTRA_OBJS := start.o context.o
ARCH_SUPPORTED := no
