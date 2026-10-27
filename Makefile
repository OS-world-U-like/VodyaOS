# VodyaOS — Unix Seventh Edition, ported to modern 64-bit architectures.
#
#   make                     build everything for the default architecture
#   make ARCH=x86_64         x86_64 (implemented; runs under qemu-x86_64)
#   make ARCH=aarch64        planned (see mk/arch-aarch64.mk)
#   make ARCH=loongarch64    planned (see mk/arch-loongarch64.mk)
#
# Targets:
#   all       libs + kernel + userland
#   libs      libc, libm, libmp, libdbm, libplot, libF77, libI77, libln
#   kernel    build/<ARCH>/kernel.elf
#   userland  build/<ARCH>/bin/*
#   gen       regenerate yacc/lex-derived sources into build/gen/
#   clean     remove build/<ARCH>
#
# Everything architecture-specific lives in port/<ARCH>/ and mk/arch-<ARCH>.mk;
# the heavy lifting is done by tools/build.py (see that file for details).

ARCH ?= x86_64
_mkfile_self := $(realpath mk/arch-$(ARCH).mk)
-include $(_mkfile_self)

DRIVER = python3 tools/build.py --arch $(ARCH)

.PHONY: all libs kernel userland gen clean
ifeq ($(strip $(ARCH_SUPPORTED)),yes)

all:	libs kernel userland

libs:
	$(DRIVER) libs

kernel:	libs
	$(DRIVER) kernel

userland: libs
	$(DRIVER) userland

gen:
	ARCH=$(ARCH) EMU=$(EMU) bash tools/gen.sh

clean:
	rm -rf build/$(ARCH)

else	# unsupported/planned architecture

all libs kernel userland:
	@echo "============================================================"
	@echo " ARCH=$(ARCH) is planned but not yet implemented."
	@echo " Provide the files listed in port/$(ARCH)/README.md and"
	@echo " mk/arch-$(ARCH).mk, then set ARCH_SUPPORTED := yes."
	@echo "============================================================"
	@exit 1

gen clean:
	@exit 1

endif
