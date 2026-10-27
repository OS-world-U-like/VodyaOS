#!/bin/bash
# Regenerate the yacc/lex-derived sources under build/gen/.
#
# Two stages:
#   1. grammars (bison) + the awk token table           - always works
#   2. proctab.c (needs libc + qemu; runs the awk `proc` generator),
#      awk.lx.c and lextab.c (need the freshly built `lex`) - run after
#      `make libs` and, for stage-2b, after lex/beautify are linked.
#
# Requires: bison, python3, clang, ld.lld, $EMU (default qemu-x86_64).
set -e
cd "$(dirname "$0")/.."
TOP="$(pwd)"
ARCH=${ARCH:-x86_64}
EMU=${EMU:-qemu-x86_64}
G=build/gen
CFLANG="--target=x86_64-unknown-none-elf -std=gnu89 -ffreestanding -fno-builtin \
 -fno-stack-protector -fno-pic -fno-pie -fcommon -Dunix -nostdinc -Iusr/include \
 -Iport/$ARCH/include -Wno-everything"
LDFLAGS="-m elf_x86_64 -static --image-base=0x400000"
[ "$ARCH" != x86_64 ] && { echo "gen.sh: stage-2 steps are x86_64-specific; grammars only" ; }

mkdir -p $G/{awk,eqn,neqn,cpp,m4,lex,mip,ratfor,struct,f77,make}

gram() { # gram <name> <src.y> [mip]
	python3 tools/gramfix.py "$2" $G/$1/pre.y
	case "$3" in
	mip) bison -y -o $G/mip/cgram.c $G/mip/pre.y 2>$G/mip/gen.log ;;
	d)   bison -y -d -o $G/$1/y.tab.c $G/$1/pre.y 2>$G/$1/gen.log ;;
	*)   bison -y -o $G/$1/y.tab.c $G/$1/pre.y 2>$G/$1/gen.log ;;
	esac
}

gram awk  usr/src/cmd/awk/awk.g.y d
cp $G/awk/y.tab.h $G/awk/awk.h
gram eqn  usr/src/cmd/eqn/e.y d
mv $G/eqn/y.tab.h $G/eqn/e.def; mv $G/eqn/y.tab.c $G/eqn/e.c
sed -i 's|#include "y.tab.h"|#include "e.def"|' $G/eqn/e.c
gram neqn usr/src/cmd/neqn/e.y d
mv $G/neqn/y.tab.h $G/neqn/e.def; mv $G/neqn/y.tab.c $G/neqn/e.c
sed -i 's|#include "y.tab.h"|#include "e.def"|' $G/neqn/e.c
gram cpp  usr/src/cmd/cpp/cpy.y
gram m4   usr/src/cmd/m4/m4y.y
gram lex  usr/src/cmd/lex/parser.y
gram ratfor usr/src/cmd/ratfor/r.g d
gram struct usr/src/cmd/struct/beauty.y d
gram mip  usr/src/cmd/mip/cgram.y mip
python3 tools/fixcgram.py

# f77: tokdefs -> gram.in -> gram.c
( cd usr/src/cmd/f77
  grep -n . tokens | sed "s/\([^:]*\):\(.*\)/#define \2 \1/" > "$TOP"/$G/f77/tokdefs
  sed "s/#define/%token/" "$TOP"/$G/f77/tokdefs > "$TOP"/$G/f77/gram.in
  cat gram.head gram.dcl gram.expr gram.exec gram.io >> "$TOP"/$G/f77/gram.in )
python3 tools/gramfix.py $G/f77/gram.in $G/f77/gram.t && mv $G/f77/gram.t $G/f77/gram.in
bison -y -o $G/f77/y.tab.c $G/f77/gram.in 2>$G/f77/gen.log
mv $G/f77/y.tab.c $G/f77/gram.c
cp usr/src/cmd/f77/pdp11defs $G/f77/locdefs

# make: grammar -> gram.c
gram make usr/src/cmd/make/gram.y
mv $G/make/y.tab.c $G/make/gram.c

# awk token.c from y.tab.h
python3 tools/genawk.py

STAGE2=${1:-}
if [ -f build/$ARCH/lib/libc.a ]; then
	echo "== stage 2: awk proctab.c =="
	O=$G/awk
	clang $CFLANG -Iusr/src/cmd/awk -Ibuild/gen/awk -c usr/src/cmd/awk/proc.c  -o $O/proc.o
	clang $CFLANG -Iusr/src/cmd/awk -Ibuild/gen/awk -c $O/token.c -o $O/token.o
	ld.lld $LDFLAGS -o $O/proc build/$ARCH/obj/libc/start.o $O/proc.o $O/token.o \
		build/$ARCH/lib/libc.a
	$EMU $O/proc | python3 tools/fixproctab.py > $O/proctab.c
else
	echo "== build/$ARCH/lib/libc.a missing; skipping proctab stage =="
fi

if [ -x build/$ARCH/bin/lex ]; then
	echo "== stage 2b: lex-generated tables =="
	( cd usr/src/cmd/awk && $EMU "$TOP"/build/$ARCH/bin/lex awk.lx.l ) \
		> /dev/null && mv usr/src/cmd/awk/lex.yy.c $G/awk/awk.lx.c
	( cd usr/src/cmd/struct && $EMU "$TOP"/build/$ARCH/bin/lex lextab.l ) \
		> /dev/null && mv usr/src/cmd/struct/lex.yy.c $G/struct/lextab.c
else
	echo "== build/$ARCH/bin/lex missing; skipping lex table generation =="
fi
echo "gen done."
