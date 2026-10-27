# port/aarch64 — ARM64 port [PLANNED]

Not implemented yet.  The x86_64 port under `port/x86_64/` defines the
layout every architecture must provide:

    kernel/{start.S,context.S,arch.c,kernel.ld}
    libc/{start.S,setjmp.S,syscall.c,misc.c,format.c,scan.c}
    libm/math.c
    libplot/plotstub.c

See `mk/arch-aarch64.mk` for the detailed checklist and the toolchain
variables to fill in, then enable it in the Makefile by setting
`ARCH_SUPPORTED := yes`.  The build driver (tools/build.py) needs no changes;
it reads everything from `port/$(ARCH)/`.
