#!/bin/bash
# Build BusyBox 1.37.0 statically (x86_64 Linux ABI) for VodyaOS.
# BusyBox is the VodyaOS toolset: /bin/busybox plus the applet symlinks
# (or the btrfs rootfs equivalent).  Output: build/busybox/bin/busybox.
#
#   tools/build-busybox.sh
#
# Idempotent: skips when build/busybox/bin/busybox exists.
set -e

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/build/busybox"
VER=1.37.0
SRC="${VODYA_BUSYBOX_SRC:-$ROOT/build/src}"
J=$(nproc)

if [ -x "$OUT/bin/busybox" ]; then
	echo "busybox: already built at $OUT/bin/busybox"
	exit 0
fi

mkdir -p "$SRC" "$OUT/bin"
cd "$SRC"

[ -f "busybox-$VER.tar.bz2" ] || {
	curl -L --retry 8 --retry-all-errors --retry-delay 3 --max-time 900 \
		-o "busybox-$VER.tar.bz2" \
		"https://busybox.net/downloads/busybox-$VER.tar.bz2"
}
gzip -t "busybox-$VER.tar.bz2" 2>/dev/null || bzip2 -t "busybox-$VER.tar.bz2"
[ -d "busybox-$VER" ] || tar xf "busybox-$VER.tar.bz2"

echo "== busybox $VER =="
cd "busybox-$VER"
make defconfig >/dev/null
# static + minimal-but-useful configuration tweaks
sed -i -e 's/^# CONFIG_STATIC is not set/CONFIG_STATIC=y/' .config
# init is provided by dinit; disable busybox init to avoid confusion;
# tc no longer builds against modern kernel headers
sed -i -e 's/^CONFIG_INIT=y/# CONFIG_INIT is not set/' \
       -e 's/^CONFIG_TC=y/# CONFIG_TC is not set/' \
       .config || true
yes '' | make oldconfig >/dev/null
make -j$J >"$SRC/busybox.log" 2>&1

cp busybox "$OUT/bin/busybox"
strip "$OUT/bin/busybox" 2>/dev/null || true
echo "busybox: installed to $OUT/bin/busybox ($(du -h "$OUT/bin/busybox" | cut -f1))"
