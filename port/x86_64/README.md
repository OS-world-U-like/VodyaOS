# port/x86_64 — x86_64 (amd64) port of VodyaOS / Unix Seventh Edition
# ====================================================================

This directory contains everything architecture-specific that replaces the
PDP-11 assembly which the V7 distribution shipped for the kernel and libc.

## Layout

    kernel/start.S       kernel entry point (_start), sets up stacks,
                         calls main()/startup per V7 flow
    kernel/context.S     save/resume (setjmp-style label_t save), and the
                         low-level return-from-interrupt trampoline
    kernel/arch.c        C code that mch.s used to provide:
                         `struct user u`, `physadr ka6`/`lks` (fake),,
                         `cputype = 70`, spl*(), copyin/copyout, fu*/su*,
                         clearseg/copyseg, and related machine helpers.
                         (regloc[] still lives in usr/sys/sys/trap.c.)
    kernel/kernel.ld     kernel link script (ELF64, linked like the PDP-11
                         layout: text first, then data)

    libc/start.S         userland crt0 (_start -> main -> exit), `environ`
                         is a weak symbol
    libc/setjmp.S        setjmp/longjmp
    libc/syscall.c       syscall wrappers on the Linux x86_64 ABI
                         (so binaries run under qemu-x86_64 while we have
                         no real V7 kernel yet); compiled with weak
                         definitions so programs that provide their own
                         symbol win
    libc/misc.c          exit/_exit/_cleanup, 64-bit ldiv/lrem/lmul,
                         memcpy/memmove/memset/memcmp, csv/cret
    libc/format.c        printf/fprintf/sprintf family (__builtin_va_list)
    libc/scan.c          scanf/fscanf/sscanf family

    libm/math.c          frexp/ldexp/modf (the libm asm helpers)
    libplot/plotstub.c   weak no-op plot() family; V7 shipped libplot as a
                         prebuilt PDP-11 archive, so the portable front
                         ends link against these stubs

## Toolchain

The port builds with clang/lld cross-tools regardless of the host machine:

    clang --target=x86_64-unknown-none-elf   (compile)
    ld.lld -m elf_x86_64                     (link; kernel uses kernel.ld)
    llvm-ar                                  (archives)

Userland binaries are linked `-static --image-base=0x400000` so they can be
executed under `qemu-x86_64` against the host kernel (the libc syscalls use
the Linux ABI).  The kernel is an ELF64 image (`build/x86_64/kernel.elf`);
making it actually boot x86_64 hardware/qemu is future work.

## Multi-architecture

Everything arch-specific lives under `port/<arch>/`.  Planned:
`port/aarch64/` (ARM64) and `port/loongarch64/` — see mk/arch-*.mk for the
file lists each new architecture must provide.  The build driver
(tools/build.py) and the Makefile are architecture-agnostic.

## Legacy / intentionally not ported

The following are pure PDP-11 assembly (or prebuilt PDP-11 binaries) with no
C source to port; they are kept in the tree for reference but are not built:

    usr/src/cmd/as            PDP-11 assembler
    usr/src/cmd/bas/bas.s     BASIC
    usr/src/cmd/roff/roff*.s  roff (superseded by nroff/troff, which are built)
    usr/src/games/chess/*.s   chess move tables (the C parts do build)
    usr/src/cmd/standalone/*.s  standalone boot crt0 (the C parts compile)
    usr/src/cmd/c/table.s     PDP-11 codegen tables of the V7 C compiler
    usr/src/cmd/{factor,primes}.s
    usr/src/libfpsim/*.s      floating point simulator
    usr/mdec/*.s              PDP-11 boot blocks
    bin/, etc/                prebuilt PDP-11 binaries
