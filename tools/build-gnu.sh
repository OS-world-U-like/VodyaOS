#!/bin/bash
# Build the GNU userland for VodyaOS: bash, coreutils (single binary) and
# grep -- compiled with gcc, statically linked on the x86_64 Linux ABI, so
# they run on the host, under qemu-x86_64, and later inside VodyaOS once
# the kernel can execve.  All three are GPL software, matching the
# project license.
#
# Idempotent: skips the download/build when build/gnu/bin/bash exists.
#   tools/build-gnu.sh           (or: make gnu)
#
# Output: build/gnu/bin/{bash, coreutils, grep, <coreutils symlinks>}
set -e

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/build/gnu"
mkdir -p "$OUT/bin"

if [ -x "$OUT/bin/bash" ]; then
	echo "gnu: already built at $OUT/bin (rm -rf build/gnu to rebuild)"
	exit 0
fi

BASH_VER=5.2.37
CU_VER=9.5
GREP_VER=3.11
SRC="${VODYA_GNU_SRC:-$ROOT/build/gnu-src}"
J=$(nproc)
# coreutils' configure refuses root for its mknod probe; this build is
# a freestanding cross staging, not a host install, so bypass it.
export FORCE_UNSAFE_CONFIGURE=1

mkdir -p "$SRC"
cd "$SRC"

fetch() {
	[ -f "$2" ] || curl -sL --max-time 600 -o "$2" "$1"
}
fetch "https://ftp.gnu.org/gnu/bash/bash-$BASH_VER.tar.gz"      bash.tar.gz
fetch "https://ftp.gnu.org/gnu/coreutils/coreutils-$CU_VER.tar.gz" coreutils.tar.gz
fetch "https://ftp.gnu.org/gnu/grep/grep-$GREP_VER.tar.gz"      grep.tar.gz

[ -d bash-$BASH_VER ]    || tar xf bash.tar.gz
[ -d coreutils-$CU_VER ] || tar xf coreutils.tar.gz
[ -d grep-$GREP_VER ]    || tar xf grep.tar.gz

echo "== bash $BASH_VER =="
# gcc 14 defaults to C23 where "char *f()" means no-args; bash has K&R
# internals (mkbuiltins et al), so build as gnu11
if ! (cd bash-$BASH_VER \
	&& CC="gcc -std=gnu11" ./configure --prefix=/ --enable-static-link \
		--without-bash-malloc --disable-nls \
	&& make -j$J LDFLAGS="-static") >"$SRC/bash.log" 2>&1; then
	echo "gnu: bash build FAILED (see $SRC/bash.log)" >&2
	exit 1
fi
make -C bash-$BASH_VER install DESTDIR="$SRC/stage/bash" >/dev/null \
	|| { echo "gnu: bash install FAILED" >&2; exit 1; }
echo "gnu: bash done"

echo "== coreutils $CU_VER =="
if ! (cd coreutils-$CU_VER \
	&& CC=gcc ./configure --prefix=/ --disable-nls --disable-acl \
		--disable-xattr --disable-libcap \
		--enable-single-binary=symlinks LDFLAGS="-static" \
	&& make -j$J) >"$SRC/cu.log" 2>&1; then
	echo "gnu: coreutils build FAILED (see $SRC/cu.log)" >&2
	exit 1
fi
make -C coreutils-$CU_VER install DESTDIR="$SRC/stage/cu" >/dev/null \
	|| { echo "gnu: coreutils install FAILED" >&2; exit 1; }
echo "gnu: coreutils done"

echo "== grep $GREP_VER =="
if ! (cd grep-$GREP_VER \
	&& CC=gcc ./configure --prefix=/ --disable-nls --disable-perl-regexp \
		LDFLAGS="-static" \
	&& make -j$J) >"$SRC/grep.log" 2>&1; then
	echo "gnu: grep build FAILED (see $SRC/grep.log)" >&2
	exit 1
fi
make -C grep-$GREP_VER install DESTDIR="$SRC/stage/grep" >/dev/null \
	|| { echo "gnu: grep install FAILED" >&2; exit 1; }
echo "gnu: grep done"

cp "$SRC/stage/bash/bin/bash"    "$OUT/bin/"
cp "$SRC/stage/cu/bin/coreutils" "$OUT/bin/"
cp -a "$SRC/stage/cu/bin/."      "$OUT/bin/"
cp "$SRC/stage/grep/bin/grep"    "$OUT/bin/"
strip "$OUT/bin/bash" "$OUT/bin/coreutils" "$OUT/bin/grep" 2>/dev/null || true

echo "gnu: installed to $OUT/bin"
ls -la "$OUT/bin" | grep -vE '^l' | head
