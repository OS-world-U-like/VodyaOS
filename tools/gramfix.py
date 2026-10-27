import re, sys

def scan_string(s, i, n):
    # i points at opening quote; return index after closing quote
    q = s[i]; j = i+1
    while j < n and s[j] != q:
        if s[j] == '\\': j += 1
        j += 1
    return min(j+1, n)

def skip_ws_comments(s, i, n):
    while i < n:
        if s[i] in ' \t\n': i += 1
        elif s[i]=='/' and i+1<n and s[i+1]=='*':
            i = s.find('*/', i+2)
            i = n if i < 0 else i+2
        else: break
    return i

def find_sections(s):
    # return (decl_end, rules_end) as char offsets of the two %% lines
    n = len(s); i = 0; marks = []
    while i < n and len(marks) < 2:
        # skip %{ %} blocks
        rest = s[i:]
        if s[i:i+2] == '%{':
            j = s.find('%}', i+2)
            i = n if j < 0 else j+2
            continue
        if s[i:i+2] == '%%':
            # must be at line start
            if i == 0 or s[i-1] == '\n':
                marks.append(i)
                i += 2
                continue
        if s[i] in '"\'':
            i = scan_string(s, i, n); continue
        i += 1
    return marks

def transform_rules(s, start, end):
    out = []; i = start; n = end; blocks = []
    depth = 0
    while i < n:
        c = s[i]
        if c=='/' and i+1<n and s[i+1]=='*':
            j = s.find('*/', i+2)
            out.append(s[i:j+2]); i = j+2; continue
        if c=='"':
            j = scan_string(s, i, n); out.append(s[i:j]); i = j; continue
        if c=="'":
            j = scan_string(s, i, n); out.append(s[i:j]); i = j; continue
        if c=='%' and s[i:i+2]=='%{':
            j = s.find('%}', i+2)
            blocks.append(s[i+2:j])
            i = j+2; continue
        if c=='{':
            depth += 1
            out.append(c); i += 1; continue
        if c=='}':
            depth -= 1
            out.append(c); i += 1; continue
        if c=='=' and depth == 0:
            prev = (out[-1][-1] if out and out[-1] else '')
            if prev in '<>!+-*/%&|^=' or (len(out)>=2 and out[-1][-2:]=='<<') or (len(out)>=2 and out[-1][-2:]=='>>'):
                out.append(c); i += 1; continue
            j = skip_ws_comments(s, i+1, n)
            if j < n and s[j]=='{':
                # drop '=' and let the '{' be handled as action
                i = j; continue
            else:
                # '= code ;' action form: consume to ';'
                k = s.find(';', j)
                if k < 0 or k >= n:
                    sys.stderr.write('WARN: unterminated = action at %d\n' % i)
                    out.append(c); i += 1; continue
                out.append('{ '+s[j:k+1]+' }')
                i = k+1; continue
        out.append(c); i += 1
    return ''.join(out), blocks

def transform(src):
    s = src.replace('%term','%token')
    marks = find_sections(s)
    if len(marks) == 2:
        d1, d2 = marks
        decls, rules, trailer = s[:d1], s[d1+2:d2], s[d2+2:]
    elif len(marks) == 1:
        decls, rules, trailer = s[:marks[0]], s[marks[0]+2:], ''
    else:
        raise RuntimeError('bad grammar')
    newrules, blocks = transform_rules(rules, 0, len(rules))
    # merge rules-section %{ %} blocks into declarations
    if blocks:
        m = re.search(r'%\{(.*?)%\}', decls, re.S)
        if m:
            decls = decls[:m.end()-2] + ''.join(blocks) + decls[m.end()-2:]
        else:
            decls = decls.rstrip('\n') + '\n%{' + ''.join(blocks) + '%}\n'
    return decls + '%%' + newrules + ('%%' + trailer if trailer else '')

if __name__ == '__main__':
    src, dst = sys.argv[1], sys.argv[2]
    open(dst,'w').write(transform(open(src).read()))
