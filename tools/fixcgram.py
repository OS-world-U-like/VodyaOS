#!/usr/bin/env python3
"""Post-process build/gen/mip/cgram.c for the V7 portable C compiler.

manifest/mfile1 already #define the token numbers (e.g. `# define NAME 2`),
which clashes with bison's generated `enum yytokentype { NAME = 2, ... }`.
Replace the enum with equivalent #defines.
"""
import re, os
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
p = 'build/gen/mip/cgram.c'
s = open(p).read()
m = re.search(r'enum yytokentype\s*\{(.*?)\};', s, re.S)
if not m:
    print('no yytokentype enum found; nothing to do')
    sys.exit(0)
defines = []
for line in m.group(1).split('\n'):
    mm = re.match(r'\s*(\w+)\s*=\s*(-?\d+)\s*,?\s*(?:/\*.*\*/)?$', line)
    if mm:
        defines.append('#define %s %s' % (mm.group(1), mm.group(2)))
block = '\n'.join(defines) + '\n'
s = s[:m.start()] + block + s[m.end():]
# any `enum yytokentype` type references become plain int
s = s.replace('enum yytokentype', 'int')
open(p, 'w').write(s)
print('cgram.c: %d token defines' % len(defines))
