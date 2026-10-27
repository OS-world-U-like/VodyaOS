#!/usr/bin/env python3
"""Fix the initializer syntax in the output of the awk `proc` generator:
`} proctab[75] {` and `char *printname[75] {` need `= ` before `{`."""
import sys, re
lines = sys.stdin.read().split('\n')
for i, l in enumerate(lines):
    if re.match(r'^(obj|char )', l) and re.search(r'\[\d+\]', l) \
            and l.rstrip().endswith('{'):
        lines[i] = re.sub(r'\{\s*$', '= {', l)
sys.stdout.write('\n'.join(lines))
