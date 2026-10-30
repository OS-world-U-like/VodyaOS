#!/usr/bin/env python3
"""
Keyboard-driver smoke test: boot vodya.img headless, type lines through
the QEMU monitor (sendkey), and verify the kernel echoes and buffers
them.  Requires: qemu-system-x86_64, the OVMF firmware.

usage: tools/test-kbd.py [image]   (default build/x86_64/vodya.img)

The test talks to the monitor over a unix socket and reads the serial
console from a log file; the kernel mirrors every console byte to COM1.
Exit code 0 = all typed lines came back, 1 = failure.
"""
import os
import socket
import subprocess
import sys
import tempfile
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IMG = sys.argv[1] if len(sys.argv) > 1 else os.path.join(
    ROOT, 'build', 'x86_64', 'vodya.img')
OVMF = '/usr/share/ovmf/OVMF.fd'

TYPE_LINES = ['hello vodya', 'x=42', 'halt']

# qemu 'sendkey' names for each ascii char we need
KEYNAME = {
    ' ': 'spc', '-': 'minus', '=': 'equal', '[': 'bracket_left',
    ']': 'bracket_right', ';': 'semicolon', "'": 'apostrophe',
    '`': 'grave_accent', '\\': 'backslash', ',': 'comma',
    '.': 'dot', '/': 'slash', '\n': 'ret',
}


def mon(s, cmd):
    s.sendall(cmd.encode() + b'\n')
    time.sleep(0.05)
    try:
        return s.recv(4096).decode(errors='replace')
    except socket.timeout:
        return ''


def type_line(s, line):
    for ch in line:
        key = KEYNAME.get(ch, ch)
        mon(s, 'sendkey %s' % key)
        time.sleep(0.03)
    mon(s, 'sendkey ret')


def main():
    if not os.path.exists(IMG):
        print('no image at %s - run make image first' % IMG)
        return 1

    tmp = tempfile.mkdtemp(prefix='vodya-kbd-')
    sockpath = os.path.join(tmp, 'mon.sock')
    seriallog = os.path.join(tmp, 'serial.log')

    qemu = subprocess.Popen([
        'qemu-system-x86_64', '-M', 'q35', '-m', '512',
        '-bios', OVMF,
        '-drive', 'file=%s,format=raw,if=ide' % IMG,
        '-serial', 'file:%s' % seriallog,
        '-display', 'none',
        '-monitor', 'unix:%s,server,nowait' % sockpath,
    ], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    try:
        if qemu.poll() is not None:
            print('FAIL: qemu exited immediately:')
            print(qemu.stdout.read().decode(errors='replace'))
            return 1
        # wait for monitor socket
        s = None
        for _ in range(100):
            if os.path.exists(sockpath):
                try:
                    s = socket.socket(socket.AF_UNIX)
                    s.settimeout(2)
                    s.connect(sockpath)
                    break
                except OSError:
                    pass
            if qemu.poll() is not None:
                print('FAIL: qemu exited early:')
                print(qemu.stdout.read().decode(errors='replace'))
                return 1
            time.sleep(0.2)
        if s is None:
            print('FAIL: qemu monitor never appeared')
            return 1

        time.sleep(8)                 # OVMF + limine + kernel banner
        for line in TYPE_LINES:
            type_line(s, line)
            time.sleep(0.5)

        time.sleep(2)
        with open(seriallog, 'rb') as f:
            log = f.read().decode(errors='replace')

        ok = True
        for line in TYPE_LINES:
            if line == 'halt':
                if 'halted.' not in log:
                    print('FAIL: no "halted." after typing halt')
                    ok = False
            else:
                if ('you typed: %s' % line) not in log:
                    print('FAIL: missing echo of %r' % line)
                    ok = False
        if ok:
            print('PASS: keyboard echo + line buffer verified '
                '(%d lines)' % (len(TYPE_LINES) - 1))
        return 0 if ok else 1
    finally:
        qemu.kill()
        for f in (seriallog,):
            if os.path.exists(f):
                body = open(f, 'rb').read().decode(errors='replace')
                clean = body.replace('\x1b', '^[')
                print('--- serial tail ---')
                print('\n'.join(clean.splitlines()[-25:]))


if __name__ == '__main__':
    sys.exit(main())
