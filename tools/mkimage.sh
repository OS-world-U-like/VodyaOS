#!/bin/bash
# Build the VodyaOS UEFI boot image.
#
# UEFI-only by design (no legacy BIOS support): a raw disk with a GPT
# holding an EFI System Partition (FAT32) for the bootloader, kernel and
# tools, plus a btrfs data partition for the future rootfs.
#
# ESP layout (each kind of content in its own place):
#
#   ::/EFI/BOOT/BOOTX64.EFI     Limine bootloader (UEFI spec path)
#   ::/boot/limine/limine.conf  boot menu config
#   ::/boot/kernel/kernel.elf   the kernel
#   ::/bin/                     V7 userland tools (build/<arch>/bin)
#   ::/gnu/bin/                 GNU userland (bash/coreutils/grep)
#   ::/source/                  full source tree (usr/ port/ mk/ tools/ docs/)
#
# usage: tools/mkimage.sh <arch> <kernel.elf> <limine.conf> <limine-dir> <out.img>
set -eu

ARCH=$1; KERNEL=$2; CONF=$3; LIMINE=$4; OUT=$5

[ -f "$LIMINE/BOOTX64.EFI" ] || { echo "missing $LIMINE/BOOTX64.EFI - build limine/ first" >&2; exit 1; }

IMG_MB=1024
ESP_MB=512
SECT=512
ESP_START=2048				# 1 MiB
# leave 1 MiB up front plus the GPT backup header area (33 sectors) at the end
ESP_SECTORS=$((ESP_MB * 1024 * 1024 / SECT))
DATA_START=$((ESP_START + ESP_SECTORS))
DATA_SECTORS=$(((IMG_MB * 1024 * 1024 - (DATA_START + 2048) * SECT) / SECT))

rm -f "$OUT"
truncate -s ${IMG_MB}M "$OUT"

# GPT: p1 = EFI System Partition (FAT32, what UEFI firmware reads),
#      p2 = Linux data partition (btrfs -- the future VodyaOS rootfs;
#           mountable from any Linux host today, kernel support to come)
sfdisk "$OUT" <<EOF
label: gpt
start=$ESP_START, size=$ESP_SECTORS, type=uefi
start=$DATA_START, size=$DATA_SECTORS, type=linux
EOF

# populate the FAT filesystem (mkfs.vfat --offset and mtools -i file@@byte,
# so no root mount is needed)
FSOPT="-i $OUT@@$((ESP_START*SECT))"
# array form for use inside functions that play with IFS (an unquoted
# $FSOPT there would be split on '/' too)
FSOPTA=(-i "$OUT@@$((ESP_START*SECT))")
# FAT32 on the 512 MiB ESP (>= 65525 clusters, which is exactly why the old
# 32 MiB ESP had to stay FAT16 -- too few clusters for FAT32).  FAT32 is
# the UEFI-standard filesystem every firmware can read.
mkfs.vfat -F 32 -s 8 --offset $ESP_START -n VODYA "$OUT"

# mmd that creates every path component (mtools' mmd needs the parent);
# accepts multiple paths like mmd does
mmd_p() {
	local path cur seg
	local IFS='/'
	for path in "$@"; do
		path="${path#::}"; path="${path#/}"	# normalize ::/ and /
		cur=""
		for seg in $path; do
			[ -n "$seg" ] || continue
			cur="$cur/$seg"
			mmd "${FSOPTA[@]}" "::$cur" 2>/dev/null || true
		done
	done
}

# Deterministic tree copy: mcopy -s chokes unpredictably, so create every
# directory first, then copy file by file to its full path.
copy_tree() {	# <host_dir> <fat_path>
	local d f
	mmd_p "$2"
	while IFS= read -r d; do
		mmd_p "$2${d#"$1"}"
	done < <(find "$1" -type d | sort)
	while IFS= read -r f; do
		# retry once: mtools occasionally misses the first write into
		# a freshly mmd'ed directory
		if ! mcopy $FSOPT "$f" "$2${f#"$1"}" 2>/dev/null \
		   && ! mcopy $FSOPT "$f" "$2${f#"$1"}" 2>/dev/null; then
			# FAT is case-insensitive: V7 trees have case-variant
			# names (usr/doc/yacc: ssA/ssa, ssB/ssb) that can't
			# coexist here -- they DO coexist in the btrfs copy
			d="${2}${f#"$1"}"
			if mdir $FSOPT "${d%/*}" 2>/dev/null \
			   | tr -s ' \t' ' ' | tr 'A-Z' 'a-z' \
			   | grep -qw "$(basename "$f" | tr 'A-Z' 'a-z')"; then
				echo "note: skipped $f (case-clash on FAT; kept in btrfs /usr/src)"
			else
				echo "WARN: cannot copy $f"
			fi
		fi
	done < <(find "$1" -type f | sort)
}

ROOT="$(cd "$(dirname "$0")/.." && pwd)"

# --- bootloader + kernel -----------------------------------------------------
mmd_p /EFI/BOOT /boot/limine /boot/kernel
mcopy $FSOPT "$LIMINE/BOOTX64.EFI" ::/EFI/BOOT/BOOTX64.EFI
mcopy $FSOPT "$CONF"               ::/boot/limine/limine.conf
mcopy $FSOPT "$KERNEL"             ::/boot/kernel/kernel.elf

# --- V7 userland tools -------------------------------------------------------
# Statically linked build/<arch>/bin; they wait in the image until the
# kernel can execve -- nothing at boot reads them yet.
BIN_DIR="$(dirname "$KERNEL")/bin"
if [ -d "$BIN_DIR" ]; then
	mmd_p /bin
	mcopy $FSOPT "$BIN_DIR"/* ::/bin/
	echo "installed $(ls "$BIN_DIR" | wc -l) V7 tools to ::/bin"
fi

# --- GNU userland (GPL) ------------------------------------------------------
# bash, coreutils single binary, grep.  Only regular files go in -- FAT
# has no symlinks, so the coreutils swiss-army binary must be invoked as
# `coreutils <cmd>` until VodyaOS has a real rootfs.
GNU_BIN="$ROOT/build/gnu/bin"
if [ -x "$GNU_BIN/bash" ]; then
	mmd_p /gnu/bin
	for f in "$GNU_BIN"/*; do
		# only real files: FAT can't host the coreutils command
		# symlinks, and -f would happily follow each one
		[ -f "$f" ] && [ ! -L "$f" ] || continue
		mcopy $FSOPT "$f" ::/gnu/bin/
	done
	echo "installed GNU userland: $(find "$GNU_BIN" -maxdepth 1 -type f | wc -l) files"
fi

# --- source tree -------------------------------------------------------------
# The full tree, read-only on the ESP: the V7 sources (usr/ -- including
# usr/lib/lex/ncform at its rootfs path), the port layer, build driver,
# generated parsers, docs and license.  Build outputs stay out.
if [ -d "$ROOT/usr" ]; then
	copy_tree "$ROOT/usr"   ::/source/usr
	copy_tree "$ROOT/port"  ::/source/port
	copy_tree "$ROOT/mk"    ::/source/mk
	copy_tree "$ROOT/tools" ::/source/tools
	copy_tree "$ROOT/docs"  ::/source/docs
	copy_tree "$ROOT/build/gen" ::/source/build/gen
	mcopy $FSOPT "$ROOT/Makefile" "$ROOT/LICENSE" \
	      "$ROOT/README.md" "$ROOT/README.V7.md" ::/source/
	echo "installed source tree to ::/source"
fi

# ------------------------------------------------------------- data (btrfs)
# Format and seed the btrfs rootfs on partition 2.  This is what the
# kernel mounts at boot (btrfs first, FAT32 ESP as fallback), so it
# carries the real rootfs layout:
#
#   /gnu/bin/   bash + coreutils (hardlinks) + grep
#   /bin/       V7 userland + busybox (applet hardlinks)
#   /sbin/      dinit (init system, future PID 1)
#   /etc/dinit.d/  dinit service tree (boot -> getty -> bash)
#   /usr/src/   full source tree
#
# Needs root (loop device + mount); skipped gracefully otherwise.  The
# FAT side keeps a reduced copy of everything as bootstrap fallback.
if command -v mkfs.btrfs >/dev/null 2>&1 && LOOP=$(losetup --find --show --partscan "$OUT" 2>/dev/null); then
	SEEDED=""
	if mkfs.btrfs -L VODYA -f "${LOOP}p2" >/dev/null 2>&1 \
	   && MNT=$(mktemp -d) \
	   && mount "${LOOP}p2" "$MNT" 2>/dev/null; then
		# base layout
		mkdir -p "$MNT/bin" "$MNT/sbin" "$MNT/gnu/bin" "$MNT/etc/dinit.d" \
		         "$MNT/tmp" "$MNT/home" "$MNT/dev" "$MNT/proc" \
		         "$MNT/var/log" "$MNT/mnt"

		# GNU userland: real files copied, coreutils command
		# hardlinks recreated (symlinks would need symlink support
		# in the kernel's read-only btrfs driver)
		if [ -d "$ROOT/build/gnu-src/stage/cu/bin" ]; then
			# the stage tree holds host-side symlinks; a host
			# hardlink would be cross-device.  Copy the binary
			# once, then re-create every applet name as a
			# hardlink *inside* the btrfs filesystem.
			cp -L "$ROOT/build/gnu-src/stage/cu/bin/coreutils" \
			   "$MNT/gnu/bin/coreutils" 2>/dev/null || true
			for f in "$ROOT/build/gnu-src/stage/cu/bin/"*; do
				b=$(basename "$f")
				[ "$b" = coreutils ] && continue
				ln "$MNT/gnu/bin/coreutils" "$MNT/gnu/bin/$b" \
				   2>/dev/null || true
			done
			echo "installed coreutils (single binary + hardlinks) to btrfs /gnu/bin"
		fi
		for f in bash grep; do
			[ -f "$ROOT/build/gnu-src/stage/$f/bin/$f" ] \
				&& cp "$ROOT/build/gnu-src/stage/$f/bin/$f" "$MNT/gnu/bin/"
		done

		# V7 userland
		BIN_DIR="$(dirname "$KERNEL")/bin"
		if [ -d "$BIN_DIR" ]; then
			cp "$BIN_DIR"/* "$MNT/bin/" 2>/dev/null || true
			echo "installed $(ls "$BIN_DIR" | wc -l) V7 tools to btrfs /bin"
		fi

		# busybox + applet hardlinks
		if [ -x "$ROOT/build/busybox/bin/busybox" ]; then
			cp "$ROOT/build/busybox/bin/busybox" "$MNT/bin/busybox"
			"$ROOT/build/busybox/bin/busybox" --list 2>/dev/null |
			while read -r app; do
				[ "$app" = busybox ] && continue
				ln "$MNT/bin/busybox" "$MNT/bin/$app" 2>/dev/null || true
			done
			echo "installed busybox + applet hardlinks to btrfs /bin"
		fi

		# dinit (init system) + control tool
		if [ -x "$ROOT/build/dinit/sbin/dinit" ]; then
			cp "$ROOT/build/dinit/sbin/dinit" "$MNT/sbin/dinit"
			cp "$ROOT/build/dinit/bin/dinitctl" "$MNT/bin/dinitctl" 2>/dev/null || true
			echo "installed dinit to btrfs /sbin/dinit"
		fi

		# dinit service tree + base configs
		if [ -d "$ROOT/port/x86_64/rootfs" ]; then
			cp -a "$ROOT/port/x86_64/rootfs/." "$MNT/"
			echo "installed rootfs configs (dinit services) to btrfs /etc"
		fi

		# source tree (same set the ESP carries)
		if [ -d "$ROOT/usr" ]; then
			mkdir -p "$MNT/usr/src"
			cp -a "$ROOT/usr/src" "$ROOT/usr/include" "$ROOT/usr/sys" \
			      "$MNT/usr/" 2>/dev/null || true
			cp -a "$ROOT/port" "$ROOT/mk" "$ROOT/tools" "$ROOT/docs" \
			      "$ROOT/build/gen" "$MNT/usr/src/" 2>/dev/null || true
			cp "$ROOT/Makefile" "$ROOT/LICENSE" "$ROOT/README.md" \
			   "$ROOT/README.V7.md" "$MNT/usr/src/" 2>/dev/null || true
		fi

		sync
		umount "$MNT" && rmdir "$MNT"
		SEEDED=1
		echo "seeded btrfs rootfs (${LOOP}p2 detached)"
	fi
	if [ -z "$SEEDED" ]; then
		umount "${LOOP}p2" 2>/dev/null || true
		echo "note: could not seed btrfs partition, left unformatted (boot image unaffected)"
	fi
	losetup -d "$LOOP" 2>/dev/null || true
else
	echo "note: losetup/mkfs.btrfs unavailable, data partition left unformatted"
fi

echo "wrote $OUT ($(du -h "$OUT" | cut -f1), ESP at sector $ESP_START)"
