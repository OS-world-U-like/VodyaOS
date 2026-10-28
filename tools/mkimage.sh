#!/bin/bash
# Build the VodyaOS UEFI boot image.
#
# UEFI-only by design (no legacy BIOS support): a raw disk with a GPT
# holding a single EFI System Partition laid out by Limine (BOOTX64.EFI).
#
# usage: tools/mkimage.sh <arch> <kernel.elf> <limine.conf> <limine-dir> <out.img>
set -eu

ARCH=$1; KERNEL=$2; CONF=$3; LIMINE=$4; OUT=$5

[ -f "$LIMINE/BOOTX64.EFI" ] || { echo "missing $LIMINE/BOOTX64.EFI - build limine/ first" >&2; exit 1; }

IMG_MB=32
SECT=512
ESP_START=2048				# 1 MiB
# leave 1 MiB up front plus the GPT backup header area (33 sectors) at the end
ESP_SECTORS=$(( (IMG_MB*1024*1024 - (ESP_START + 2048) * SECT) / SECT ))

rm -f "$OUT"
truncate -s ${IMG_MB}M "$OUT"

# GPT with one EFI System Partition
sfdisk "$OUT" <<EOF
label: gpt
start=$ESP_START, size=$ESP_SECTORS, type=uefi
EOF

# populate the FAT filesystem (mkfs.vfat --offset and mtools -i file@@byte,
# so no root mount is needed)
FSOPT="-i $OUT@@$((ESP_START*SECT))"
# FAT16: our 30 MiB ESP is below the 65525-cluster FAT32 minimum,
# which OVMF's FAT driver refuses
mkfs.vfat -F 16 -s 4 --offset $ESP_START -n VODYA "$OUT"
mmd   $FSOPT ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine
mcopy $FSOPT "$LIMINE/BOOTX64.EFI" ::/EFI/BOOT/BOOTX64.EFI
mcopy $FSOPT "$KERNEL"            ::/boot/kernel.elf
mcopy $FSOPT "$CONF"              ::/boot/limine/limine.conf

echo "wrote $OUT ($(du -h "$OUT" | cut -f1), ESP at sector $ESP_START)"
