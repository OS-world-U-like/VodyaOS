#!/usr/bin/env python3
"""Generate build/gen/awk/token.c from build/gen/awk/y.tab.h.

Reproduces the V7 `ed -s token.c < tokenscript` step: the historical
token.c shipped with an empty `} proc[] {` table which the ed script
filled with `{"NAME", NUMBER},` lines taken from y.tab.h.
"""
import re, os
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
h = open('build/gen/awk/y.tab.h').read()
entries = []
for m in re.finditer(r'^#define\s+([A-Z][A-Z0-9]*)\s+(-?\d+)\s*$', h, re.M):
    entries.append((m.group(1), m.group(2)))
tok = open('usr/src/cmd/awk/token.c').read()
out, inserted = [], False
for line in tok.split('\n'):
    if re.match(r'^\}\s*proc\[\]\s*\{', line):
        out.append('} proc[] = {')
        out.extend('\t{ "%s", %s },' % e for e in entries)
        inserted = True
        continue
    if inserted and re.match(r'^\{', line):
        continue
    if inserted and re.match(r'^\};', line):
        inserted = False
    out.append(line)
open('build/gen/awk/token.c', 'w').write('\n'.join(out))
print('token.c: %d tokens' % len(entries))
