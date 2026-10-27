# Architecture description: x86_64
# -------------------------------
# Toolchain (host is assumed to be any machine with LLVM installed;
# we always cross-compile with clang + lld so no native toolchain is needed).
CC      := clang --target=x86_64-unknown-none-elf
AS      := clang --target=x86_64-unknown-none-elf
LD      := ld.lld -m elf_x86_64
AR      := llvm-ar
# Emulator used to run x86_64 build-time tools (e.g. the awk `proc` generator)
EMU     ?= qemu-x86_64

# Extra flags
ARCHCFLAGS    :=
KERNEL_CFLAGS := -mno-red-zone
# Static userland binaries must live above 0x400000 to be runnable
# (e.g. under qemu-user or a future x86_64 kernel).
IMAGE_BASE    := 0x400000

# Kernel link script and objects that replace the historical mch.s/l.s
KERNEL_LD     := port/$(ARCH)/kernel/kernel.ld
KERNEL_EXTRA_OBJS := start.o context.o

# Supported: yes
ARCH_SUPPORTED := yes
