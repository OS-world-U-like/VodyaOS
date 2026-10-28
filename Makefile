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
#   gnu       GNU userland (bash/coreutils/grep, gcc + -static) -> build/gnu/bin
#   gen       regenerate yacc/lex-derived sources into build/gen/
#   image     UEFI boot image (GPT + ESP, Limine)
#   run       boot the image in qemu (OVMF)
#   clean     remove build/<ARCH>
#
# Everything architecture-specific lives in port/<ARCH>/ and mk/arch-<ARCH>.mk;
# the heavy lifting is done by tools/build.py (see that file for details).

ARCH ?= x86_64
_mkfile_self := $(realpath mk/arch-$(ARCH).mk)
-include $(_mkfile_self)

DRIVER = python3 tools/build.py --arch $(ARCH)

LIMINE_DIR ?= limine
BUILD_DIR := build/$(ARCH)

.PHONY: all libs kernel userland gnu gen clean image run
ifeq ($(strip $(ARCH_SUPPORTED)),yes)

all:	libs kernel userland

libs:
	$(DRIVER) libs

kernel:	libs
	$(DRIVER) kernel

userland: libs
	$(DRIVER) userland

# GNU userland (GPL): bash, coreutils (single binary), grep, built with
# gcc and statically linked (x86_64 Linux ABI).  Architecture-independent
# for now -- revisit when non-x86_64 targets exist.
gnu:
	bash tools/build-gnu.sh

# --- bootable image (Limine boot protocol, UEFI only) -----------------------
# No legacy BIOS support by design.  Prerequisites: sfdisk, mkfs.vfat,
# mtools; and the limine/ tree cloned from
# github.com/limine-bootloader/limine (v8.x-binary branch).  `make run`
# boots the image with OVMF (apt: ovmf).

IMG := $(BUILD_DIR)/vodya.img

image:	kernel gnu
	bash tools/mkimage.sh $(ARCH) $(BUILD_DIR)/kernel.elf \
		tools/limine.conf $(LIMINE_DIR) $(IMG)

run:	image
	qemu-system-x86_64 -M q35 -m 128M \
		-bios /usr/share/ovmf/OVMF.fd \
		-drive file=$(IMG),format=raw,if=virtio \
		-serial stdio -display none -no-reboot

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
