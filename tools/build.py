#!/usr/bin/env python3
"""
Build driver for the VodyaOS (Unix V7) x86_64 port.

Usage:  tools/build.py [--arch ARCH] [libs|kernel|userland|all]

Outputs:
    build/<arch>/obj/...    objects
    build/<arch>/lib/*.a    libraries (libc, libm, libmp, libdbm, libplot,
                            libF77, libI77, libln)
    build/<arch>/bin/*      userland programs
    build/<arch>/kernel.elf the V7 kernel

Architecture-specific behaviour comes from port/<arch>/ and the ARCHCONF
table below, mirroring mk/arch-<arch>.mk.  aarch64 / loongarch64 are planned
(see port/*/README.md) but not yet implemented.
"""
import os, sys, re, glob, argparse, subprocess
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

# ---------------------------------------------------------------- per-arch
ARCHCONF = {
    'x86_64': dict(
        cc=['clang', '--target=x86_64-unknown-none-elf'],
        ld=['ld.lld', '-m', 'elf_x86_64'],
        ar='llvm-ar',
        archcflags=[],
        kernel_cflags=['-mno-red-zone'],
        image_base='0x400000',
        kernel_ld='port/x86_64/kernel/kernel.ld',
        kernel_extra=['start.o', 'context.o'],   # from port/x86_64/kernel
        emu='qemu-x86_64',
        supported=True,
    ),
    # Planned ports (see port/aarch64/README.md, port/loongarch64/README.md):
    'aarch64':     dict(supported=False),
    'loongarch64': dict(supported=False),
}

BASE_CFLAGS = ['-std=gnu89', '-ffreestanding', '-fno-builtin',
               '-fno-stack-protector', '-fno-pic', '-fno-pie', '-fcommon',
               '-Dunix', '-nostdinc', '-Iusr/include',
               '-Iport/{ARCH}/include', '-Wno-everything']

# extra flags per source directory (relative to repo root)
DIR_EXTRA = {
    'usr/src/cmd/cpp':  ['-Iusr/src/cmd/cpp', '-Dunix=1', '-Dpdp11=1'],
    'usr/src/cmd/uucp': ['-Iusr/src/cmd/uucp', '-Iusr/sys/h'],
    'usr/src/cmd/mip':  ['-Iusr/src/cmd/mip', '-Iusr/src/cmd/pcc'],
    'usr/src/cmd/pcc':  ['-Iusr/src/cmd/pcc', '-Iusr/src/cmd/mip'],
    'usr/src/cmd/f77':  ['-Iusr/src/cmd/f77', '-Ibuild/gen/f77',
                         '-DTARGET=PDP11', '-DFAMILY=DMR', '-DHERE=PDP11',
                         '-DOUTPUT=BINARY', '-DPOLISH=POSTFIX'],
    'usr/src/libF77':   ['-Iusr/src/libF77', '-Iusr/src/libI77',
                         '-DTARGET=PDP11', '-DFAMILY=DMR', '-DHERE=PDP11',
                         '-DOUTPUT=BINARY', '-DPOLISH=POSTFIX'],
    'usr/src/libI77':   ['-Iusr/src/libI77'],
    'usr/src/cmd/lint': ['-Iusr/src/cmd/mip', '-Iusr/src/cmd/lint'],
    'usr/src/cmd/ratfor': ['-Iusr/src/cmd/ratfor', '-Ibuild/gen/ratfor'],
}

F77_DFLAGS = ['-DTARGET=PDP11', '-DFAMILY=DMR', '-DHERE=PDP11',
              '-DOUTPUT=BINARY', '-DPOLISH=POSTFIX']

# ------------------------------------------------------------------ state
ARCH = 'x86_64'
CONF = None
OBJS = {}          # src -> obj path (dedup across programs)
FAILED = []        # (src, first error line)
JOBS = 12

def out(p):
    return os.path.join('build', ARCH, p)

def cflags(extra=None, kernel=False):
    cf = ARCHCONF[ARCH]['cc'] + BASE_CFLAGS + ARCHCONF[ARCH]['archcflags']
    cf = [c.replace('{ARCH}', ARCH) for c in cf]
    if kernel:
        cf += ['-Iusr/sys', '-Iport/%s/kernel' % ARCH] + ARCHCONF[ARCH]['kernel_cflags']
    if extra:
        cf += extra
    return cf

def compile_file(task):
    """task = (src, obj, extra_flags, kernel)"""
    src, obj, extra, kernel = task
    if os.path.exists(obj) and os.path.getmtime(obj) >= os.path.getmtime(src):
        return True
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    cmd = cflags(extra, kernel) + ['-c', src, '-o', obj]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        err = [l for l in r.stderr.splitlines() if 'error:' in l]
        FAILED.append((src, err[0].strip() if err else 'compile failed'))
        return False
    return True


# ------------------------------------------------------------------ libc
def libc_sources():
    srcs = []
    for d in ('usr/src/libc/gen', 'usr/src/libc/stdio', 'usr/src/libc/sys',
              'usr/src/libc/v6'):
        for f in sorted(os.listdir(d)):
            if not f.endswith('.c'):
                continue
            if f in ('printf.c', 'fprintf.c', 'sprintf.c', 'scanf.c',
                     'doscan.c'):
                continue          # replaced by port/<arch>/libc/{format,scan}.c
            if d.endswith('/v6') and f != 'ftime.c':
                continue          # v6 compat: only ftime has C source
            srcs.append(os.path.join(d, f))
    for f in sorted(glob.glob('port/%s/libc/*.c' % ARCH)):
        srcs.append(f)
    return srcs

def build_libc():
    tasks, objs = [], []
    for src in libc_sources():
        obj = out('obj/libc/%s.o' % src.replace('/', '_')[:-2])
        tasks.append((src, obj, [], False)); objs.append(obj)
    for s in ('start.S', 'setjmp.S'):
        src = 'port/%s/libc/%s' % (ARCH, s)
        obj = out('obj/libc/%s.o' % s[:-2])
        tasks.append((src, obj, [], False))
        if s == 'setjmp.S':
            objs.append(obj)
    run(tasks)
    ar(out('lib/libc.a'), [o for o in objs if os.path.exists(o)])
    return True

# ------------------------------------------------------------------ libs
def build_libs():
    start = build_libc()
    groups = {
        'libm':    sorted(glob.glob('usr/src/libm/*.c')) +
                   ['port/%s/libm/math.c' % ARCH],
        'libmp':   sorted(glob.glob('usr/src/libmp/*.c')),
        'libdbm':  ['usr/src/libdbm/dbm.c'],
        'libplot': ['port/%s/libplot/plotstub.c' % ARCH],
        'libF77':  sorted(glob.glob('usr/src/libF77/*.c')),
        'libI77':  sorted(glob.glob('usr/src/libI77/*.c')),
        'libln':   sorted(glob.glob('usr/src/cmd/lex/lib/*.c')),
    }
    for lib, srcs in groups.items():
        tasks, objs = [], []
        for src in srcs:
            obj = out('obj/%s/%s.o' % (lib, src.replace('/', '_')[:-2]))
            extra = DIR_EXTRA.get(os.path.dirname(src), [])
            tasks.append((src, obj, extra, False)); objs.append(obj)
        run(tasks)
        ar(out('lib/%s.a' % lib), [o for o in objs if os.path.exists(o)])
    return start

def ar(path, objs):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    if os.path.exists(path):
        os.unlink(path)
    subprocess.run([ARCHCONF[ARCH]['ar'], 'rcs', path] + objs, check=True)

def run(tasks):
    with ThreadPoolExecutor(JOBS) as ex:
        list(ex.map(compile_file, tasks))

# ------------------------------------------------------------------ kernel
def build_kernel():
    tasks, ksys, kdev = [], [], []
    for src in sorted(glob.glob('usr/sys/sys/*.c')):
        obj = out('obj/kernel/%s.o' % os.path.basename(src)[:-2])
        tasks.append((src, obj, [], True)); ksys.append(obj)
    for src in sorted(glob.glob('usr/sys/dev/*.c')):
        obj = out('obj/kernel/%s.o' % os.path.basename(src)[:-2])
        tasks.append((src, obj, [], True)); kdev.append(obj)
    archsrc = 'port/%s/kernel/arch.c' % ARCH
    archobj = out('obj/kernel/arch.o')
    tasks.append((archsrc, archobj, [], True)); ksys.append(archobj)
    # conf.c (cdevsw/bdevsw tables) links explicitly, like the V7 makefile
    confsrc = 'usr/sys/conf/c.c'
    confobj = out('obj/kernel/c.o')
    tasks.append((confsrc, confobj, [], True))
    run(tasks)
    ar(out('lib/libksys.a'), [o for o in ksys if os.path.exists(o)])
    ar(out('lib/libkdev.a'), [o for o in kdev if os.path.exists(o)])
    # start.o / context.o from port/<arch>/kernel
    startobj = out('obj/kernel/start.o')
    ctxobj = out('obj/kernel/context.o')
    run([('port/%s/kernel/start.S' % ARCH, startobj, [], True),
         ('port/%s/kernel/context.S' % ARCH, ctxobj, [], True)])
    elf = out('kernel.elf')
    cmd = ARCHCONF[ARCH]['ld'] + ['-T', ARCHCONF[ARCH]['kernel_ld'],
        '-o', elf, startobj, ctxobj, confobj,
        out('lib/libksys.a'), out('lib/libkdev.a')]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stderr, file=sys.stderr)
        print('kernel: LINK FAILED', file=sys.stderr)
        return False
    print('kernel: %s' % elf)
    return True

# ---------------------------------------------------------------- userland
MAIN_RE = re.compile(r'^\s*(?:int\s+)?main\s*\(', re.M)
DEFAULT_LIBS = ['lib/libc.a', 'lib/libm.a', 'lib/libmp.a', 'lib/libdbm.a',
                'lib/libplot.a']

def P(name, srcs, inc=None, defs=None, libs=None, link=True, drop=None):
    return dict(name=name, srcs=srcs, inc=inc or [], defs=defs or [],
                libs=libs, link=link, drop=drop or [])

def _dir_c(d):
    return sorted(os.path.basename(f) for f in glob.glob(d + '/*.c'))

def special_programs():
    """Programs whose grouping differs from the auto-discovered one."""
    pr = []
    C = 'usr/src/cmd'
    # --- cmd/c: the V7 PDP-11 C compiler (c1 has no portable table object)
    pr.append((C + '/c', [P('c0', [C+'/c/c00.c',C+'/c/c01.c',C+'/c/c02.c',C+'/c/c03.c',C+'/c/c04.c',C+'/c/c05.c'], ['usr/src/cmd/c']),
                          P('c1', [C+'/c/c10.c',C+'/c/c11.c',C+'/c/c12.c',C+'/c/c13.c'], ['usr/src/cmd/c'], link=False),
                          P('c2', [C+'/c/c20.c',C+'/c/c21.c'], ['usr/src/cmd/c']),
                          P('cvopt', [C+'/c/cvopt.c'], ['usr/src/cmd/c'])]))
    # --- cpp / m4 / lex (yacc-generated parsers)
    pr.append((C + '/cpp', [P('cpp', ['usr/src/cmd/cpp/cpp.c', 'build/gen/cpp/y.tab.c'], ['usr/src/cmd/cpp'])]))
    pr.append((C + '/m4', [P('m4', ['usr/src/cmd/m4/m4.c', 'build/gen/m4/y.tab.c'], ['usr/src/cmd/m4'])]))
    pr.append((C + '/lex', [P('lex', ['usr/src/cmd/lex/lmain.c', 'build/gen/lex/y.tab.c',
                                      'usr/src/cmd/lex/sub1.c', 'usr/src/cmd/lex/sub2.c',
                                      'usr/src/cmd/lex/header.c'], ['usr/src/cmd/lex'])]))
    # --- awk (all generated pieces live in build/gen/awk)
    awksrc = ['build/gen/awk/y.tab.c', 'build/gen/awk/awk.lx.c',
              'usr/src/cmd/awk/b.c', 'usr/src/cmd/awk/main.c',
              'build/gen/awk/token.c', 'usr/src/cmd/awk/tran.c',
              'usr/src/cmd/awk/lib.c', 'usr/src/cmd/awk/run.c',
              'usr/src/cmd/awk/parse.c', 'build/gen/awk/proctab.c']
    pr.append((C + '/awk', [P('awk', awksrc, ['usr/src/cmd/awk', 'build/gen/awk'])]))
    # --- eqn / neqn
    eqn = ['build/gen/eqn/e.c'] + [C + '/eqn/' + f for f in _dir_c(C + '/eqn')]
    neqn = ['build/gen/neqn/e.c'] + [C + '/neqn/' + f for f in _dir_c(C + '/neqn')]
    pr.append((C + '/eqn', [P('eqn', eqn, ['usr/src/cmd/eqn', 'build/gen/eqn'])]))
    pr.append((C + '/neqn', [P('neqn', neqn, ['usr/src/cmd/neqn', 'build/gen/neqn'])]))
    # --- struct / beautify
    st = C + '/struct'
    pr.append((st, [P('structure', [st + '/' + f for f in _dir_c(st)
                                    if f[0] in '01234' or f == 'main.c'],
                        [st]),
                    P('beautify', ['build/gen/struct/y.tab.c', st + '/tree.c',
                                   'build/gen/struct/lextab.c', st + '/bdef.c'],
                        [st, 'build/gen/struct'])]))
    # --- refer family (refer..c compiled once per -DreferN)
    R = C + '/refer'
    G = lambda *fs: [R + '/' + f for f in fs]
    pr.append((R, [
        P('mkey',   G('mkey1.c','mkey2.c','mkey3.c','deliv2.c'), [R]),
        P('inv',    G('inv1.c','inv2.c','inv3.c','inv5.c','inv6.c','deliv2.c','thash.c'), [R]),
        P('hunt',   G('hunt1.c','hunt2.c','hunt3.c','hunt5.c','hunt6.c','hunt7.c','hunt8.c','hunt9.c','refer3.c','shell.c','deliv2.c','glue4.c','glue5.c'), [R]),
        P('refer',  G('glue1.c','glue2.c','glue3.c','glue4.c','glue5.c','refer0.c','refer1.c','refer2.c','refer4.c','refer5.c','refer6.c','refer7.c','refer8.c','hunt2.c','hunt3.c','hunt5.c','hunt6.c','hunt7.c','hunt8.c','hunt9.c','mkey3.c','shell.c','deliv2.c'), [R]),
    ]))
    # --- learn: tee/lcount are standalone, one file each
    LE = 'usr/src/cmd/learn'
    pr.append((LE, [P('learn', [LE + '/' + f for f in
                ('copy.c','dounit.c','learn.c','list.c','makpipe.c',
                 'maktee.c','mem.c','mysys.c','selsub.c','selunit.c',
                 'start.c','whatnow.c','wrapup.c')], [LE]),
                    P('tee', [LE + '/tee.c'], [LE]),
                    P('lcount', [LE + '/lcount.c'], [LE])]))
    # --- adb: dummy.c is the alternative (no-ptrace) subpcs; never linked
    A = C + '/adb'
    pr.append((A, [P('adb', [A + '/' + f for f in
                ('access.c','command.c','expr.c','findfn.c','format.c',
                 'input.c','main.c','message.c','opset.c','output.c',
                 'pcs.c','print.c','runpcs.c','setup.c','sym.c')], [A])]))
    # --- ratfor
    RA = C + '/ratfor'
    pr.append((RA, [P('ratfor', [RA + '/' + f for f in
                ('r0.c','r1.c','r2.c','rio.c','rlook.c','rlex.c')] +
                ['build/gen/ratfor/y.tab.c'], [RA, 'build/gen/ratfor'])]))
    # --- uucp (object lists straight from the V7 makefile)
    U = C + '/uucp'
    GU = lambda *fs: [U + '/' + f for f in fs]
    uofiles = ('cpmv.c','expfile.c','gename.c','getpwinfo.c','index.c',
               'lastpart.c','prefix.c','shio.c','ulockf.c','xqt.c')
    pr.append((U, [
        P('uucp',   GU('uucp.c','gwd.c') + GU(*uofiles) +
                    GU('chkpth.c','getargs.c','logent.c','versys.c'), [U]),
        P('uux',    GU('uux.c','gwd.c') + GU(*uofiles) +
                    GU('chkpth.c','getargs.c','getprm.c','versys.c'), [U]),
        P('uuxqt',  GU('uuxqt.c') + GU(*uofiles) +
                    GU('getprm.c','gnamef.c','logent.c'), [U]),
        P('uucico', GU('cico.c','cntrl.c','conn.c','pk0.c','pk1.c','gio.c',
                       'sdmail.c','pkon.c','ioctl.c') + GU(*uofiles) +
                    GU('anlwrk.c','chkpth.c','getargs.c','gnamef.c','gnsys.c',
                       'gnxseq.c','imsg.c','logent.c','sysacct.c','systat.c'), [U]),
        P('uulog',  GU('uulog.c','prefix.c','xqt.c','ulockf.c','gnamef.c'), [U]),
        P('uuclean', GU('uuclean.c','gnamef.c','prefix.c','sdmail.c','getpwinfo.c'), [U]),
        P('uurecover', GU('uurecover.c'), [U], link=False),
    ]))
    # --- lpr / lpd (spool.c and daemon.c are #included by the mains)
    L = C + '/lpr'
    pr.append((L, [P('lpr', [L + '/lpr.c'], [L]),
                   P('lpd', [L + '/lpd.c'], [L])]))
    # --- make
    MK = C + '/make'
    pr.append((MK, [P('make', [MK + '/' + f for f in
                ('main.c','doname.c','dosys.c','files.c','ident.c','misc.c')] +
                ['build/gen/make/gram.c'], [MK, 'build/gen/make'])]))
    # --- lint (pass 1 is the ccom front end plus lint.c)
    LI = C + '/lint'
    pr.append((LI, [P('lpass1', [LI + '/lint.c', 'build/gen/mip/cgram.c'] +
                    ['usr/src/cmd/mip/' + f for f in
                     ('xdefs.c','scan.c','comm1.c','pftn.c','trees.c','optim.c')],
                    [LI, 'usr/src/cmd/mip'],
                    drop=['-Iusr/src/cmd/pcc']),
                    P('lpass2', [LI + '/lpass2.c'], [LI, 'usr/src/cmd/mip'])]))
    # --- f77: driver + pass1
    F = C + '/f77'
    f77p1 = ['main.c','init.c','gram','lex.c','proc.c','equiv.c','data.c',
             'expr.c','exec.c','intr.c','io.c','misc.c','error.c','put.c',
             'putdmr.c','pdp11.c','pdp11x.c']
    f77p1 = [(F + '/' + f) if f.endswith('.c') else 'build/gen/f77/gram.c' for f in f77p1]
    pr.append((F, [P('f77', [F + '/driver.c', F + '/pdp11x.c'], [F, 'build/gen/f77'], F77_DFLAGS),
                   P('f77pass1', f77p1, [F, 'build/gen/f77'], F77_DFLAGS)]))
    # --- mip/pcc: the portable C compiler
    M, PC = C + '/mip', C + '/pcc'
    mipsrc = ['trees.c','optim.c','pftn.c','xdefs.c','scan.c','reader.c',
              'match.c','allo.c','comm1.c']
    ccom = ['build/gen/mip/cgram.c'] + [M + '/' + f for f in mipsrc] + \
           [PC + '/' + f for f in ['code.c','local.c','local2.c','order.c','table.c']]
    pr.append((M, [P('ccom', ccom, [M, PC])]))
    # --- troff / nroff
    T = C + '/troff'
    nroff = [T + '/%s' % f for f in ('n1.c','n2.c','n3.c','n4.c','n5.c','n6.c',
             'n7.c','n8.c','n9.c','n10.c','ni.c','nii.c','ntab.c','hytab.c','suftab.c')]
    troff = [T + '/%s' % f for f in ('n1.c','n2.c','n3.c','n4.c','n5.c','t6.c',
             'n7.c','n8.c','n9.c','t10.c','ni.c','nii.c','tab3.c',
             'hytab.c','suftab.c')]
    pr.append((T, [P('nroff', nroff, [T], ['-DNROFF']),
                   P('troff', troff, [T])]))
    # --- compile-only trees (need PDP-11 asm pieces to link)
    pr.append((C + '/standalone', [P(f[:-2], [C + '/standalone/' + f], [C + '/standalone'],
               link=False) for f in _dir_c(C + '/standalone')]))
    pr.append(('usr/src/games/chess', [P(f[:-2], ['usr/src/games/chess/' + f],
               ['usr/src/games/chess'], link=False) for f in _dir_c('usr/src/games/chess')]))
    return pr

SKIP_DIRS = {'usr/src/cmd/as', 'usr/src/cmd/bas', 'usr/src/cmd/roff',
             'usr/src/cmd/c', 'usr/src/cmd/cpp', 'usr/src/cmd/m4',
             'usr/src/cmd/lex', 'usr/src/cmd/awk', 'usr/src/cmd/eqn',
             'usr/src/cmd/neqn', 'usr/src/cmd/struct', 'usr/src/cmd/refer',
             'usr/src/cmd/f77', 'usr/src/cmd/mip', 'usr/src/cmd/troff',
             'usr/src/cmd/standalone', 'usr/src/games/chess',
             'usr/src/cmd/pcc', 'usr/src/cmd/uucp', 'usr/src/cmd/lpr',
             'usr/src/cmd/make', 'usr/src/cmd/lint', 'usr/src/cmd/ratfor',
             'usr/src/cmd/adb', 'usr/src/cmd/learn'}

def build_userland():
    start = out('obj/libc/start.o')
    groups = []   # (dir, [P...])
    seen = set(SKIP_DIRS)
    for d, progs in special_programs():
        groups.append((d, progs))
    # auto-discovery: every .c file / dir of .c files becomes a program
    for f in sorted(glob.glob('usr/src/cmd/*.c')):
        d = 'usr/src/cmd'
        groups.append((d, [P(f[:-2], [f], [d])]))
    for base in ('usr/src/cmd', 'usr/src/games'):
        for d in sorted(glob.glob(base + '/*/')):
            d = d.rstrip('/')
            if d in seen or d in SKIP_DIRS:
                continue
            cs = _dir_c(d)
            if not cs:
                continue
            progs, mains = [], []
            for f in cs:
                if MAIN_RE.search(open(d + '/' + f, errors='ignore').read()):
                    mains.append(f)
            if not mains:
                continue
            support = [d + '/' + f for f in cs if f not in mains]
            for mf in mains:
                nm = os.path.basename(d) if len(mains) == 1 \
                     else os.path.basename(d) + '-' + mf[:-2]
                progs.append(P(nm, [d + '/' + mf] + support, [d]))
            groups.append((d, progs))
    # compile everything, then link
    tasks = []
    for d, progs in groups:
        for p in progs:
            for src in p['srcs']:
                key = (src, tuple(p['defs']), tuple(p['inc']))
                if key in OBJS:
                    continue
                extra = DIR_EXTRA.get(os.path.dirname(src), [])
                extra = list(dict.fromkeys(extra + ['-I' + i for i in p['inc']]))
                if p['drop']:
                    extra = [f for f in extra if f not in p['drop']]
                if p['defs']:
                    extra = extra + p['defs']
                obj = out('obj/cmd/%s_%s.o' % (os.path.basename(d),
                          re.sub(r'\W+', '_', src)[:-2]))
                OBJS[key] = obj
                tasks.append((src, obj, extra, False))
    run(tasks)
    # link
    n_ok = n_fail = 0
    for d, progs in groups:
        for p in progs:
            if not p['link']:
                continue
            objs = [OBJS[(s, tuple(p['defs']), tuple(p['inc']))] for s in p['srcs']
                    if (s, tuple(p['defs']), tuple(p['inc'])) in OBJS and os.path.exists(OBJS[(s, tuple(p['defs']), tuple(p['inc']))])]
            if len(objs) != len(p['srcs']):
                continue          # some sources failed to compile
            binp = out('bin/' + p['name'])
            os.makedirs(os.path.dirname(binp), exist_ok=True)
            libs = ['build/' + ARCH + '/' + l for l in (p['libs'] or DEFAULT_LIBS)]
            cmd = ARCHCONF[ARCH]['ld'] + ['-static', '--image-base=%s' % ARCHCONF[ARCH]['image_base'],
                  '-o', binp, start] + objs + ['--start-group'] + libs + ['--end-group']
            r = subprocess.run(cmd, capture_output=True, text=True)
            if r.returncode != 0:
                err = [l for l in r.stderr.splitlines() if 'error:' in l]
                print('LINK FAIL %-14s %s' % (p['name'], err[0] if err else ''), file=sys.stderr)
                n_fail += 1
            else:
                n_ok += 1
    print('userland: %d linked, %d failed' % (n_ok, n_fail))
    return n_fail == 0


# -------------------------------------------------------------------- main
def main():
    global ARCH, CONF, JOBS
    ap = argparse.ArgumentParser()
    ap.add_argument('--arch', default='x86_64')
    ap.add_argument('-j', type=int, default=JOBS)
    ap.add_argument('--strict', action='store_true',
                    help='fail if any source fails to compile')
    ap.add_argument('target', nargs='?', default='all',
                    choices=['libs', 'kernel', 'userland', 'all'])
    args = ap.parse_args()
    ARCH = args.arch
    JOBS = args.j
    CONF = ARCHCONF.get(ARCH)
    if not CONF or not CONF.get('supported'):
        sys.exit("""============================================================
 ARCH=%s is planned but not yet implemented.
 Provide the files listed in port/%s/README.md and
 mk/arch-%s.mk, then enable it in tools/build.py.
============================================================""" % (ARCH, ARCH, ARCH))
    for d in ('obj', 'lib', 'bin'):
        os.makedirs(out(d), exist_ok=True)
    ok = True
    if args.target in ('libs', 'all'):
        ok &= build_libs()
    if args.target in ('kernel', 'all'):
        ok &= build_kernel()
    if args.target in ('userland', 'all'):
        ok &= build_userland()
    if FAILED:
        print('\n%d source file(s) failed to compile:' % len(FAILED))
        for src, err in FAILED:
            print('  %-44s %s' % (src, err))
    if FAILED and args.strict:
        sys.exit(1)
    if not ok and args.target != 'userland':
        sys.exit(1)

if __name__ == '__main__':
    main()
