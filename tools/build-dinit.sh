#!/bin/bash
# Build Dinit (service manager / init) statically for VodyaOS.
# Dinit is the VodyaOS init system (PID 1).  Output:
#   build/dinit/sbin/dinit        the init daemon
#   build/dinit/bin/dinitctl      service control tool
#
#   tools/build-dinit.sh
#
# Idempotent: skips when build/dinit/sbin/dinit exists.
set -e

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/build/dinit"
VER=0.19.4
SRC="${VODYA_DINIT_SRC:-$ROOT/build/src}"
J=$(nproc)

if [ -x "$OUT/sbin/dinit" ]; then
	echo "dinit: already built at $OUT/sbin/dinit"
	exit 0
fi

mkdir -p "$SRC" "$OUT/sbin" "$OUT/bin"
cd "$SRC"

[ -f "dinit-$VER.tar.gz" ] || {
	curl -L --retry 8 --retry-all-errors --retry-delay 3 --max-time 900 \
		-o "dinit-$VER.tar.gz" \
		"https://github.com/davmac314/dinit/archive/refs/tags/v$VER.tar.gz"
}
gzip -t "dinit-$VER.tar.gz"
[ -d "dinit-$VER" ] || tar xf "dinit-$VER.tar.gz"

echo "== dinit $VER =="
cd "dinit-$VER"
# the ./configure wrapper drives the classic Makefile build; static via
# LDFLAGS + CXXFLAGS, no gettext, SHADOW_PASSWORD off (no libshadow)
(./configure --sysroot=/ \
	 CXXFLAGS="-O2 -static -static-libstdc++ -static-libgcc" \
	 LDFLAGS="-static" ) >"$SRC/dinit.log" 2>&1
make -j$J >>"$SRC/dinit.log" 2>&1

cp src/dinit "$OUT/sbin/dinit"
cp src/dinitctl "$OUT/bin/dinitctl"
strip "$OUT/sbin/dinit" "$OUT/bin/dinitctl" 2>/dev/null || true
echo "dinit: installed to $OUT/sbin/dinit ($(du -h "$OUT/sbin/dinit" | cut -f1))"
