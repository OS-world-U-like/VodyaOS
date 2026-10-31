#!/usr/bin/env python3
"""
Userland smoke test: boot vodya.img headless, wait for the bash prompt
(via the btrfs rootfs + ELF exec path), type a command through the QEMU
monitor (sendkey) and verify its output on the serial console.

usage: tools/test-bash.py [image]   (default build/x86_64/vodya.img)

Exit code 0 = bash executed our command, 1 = failure.
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

MARKER = 'VODYA-OK-42'
CMD = 'echo ' + MARKER

KEYNAME = {
    ' ': 'spc', '-': 'minus', '=': 'equal', '[': 'bracket_left',
    ']': 'bracket_right', ';': 'semicolon', "'": 'apostrophe',
    '`': 'grave_accent', '\\': 'backslash', ',': 'comma',
    '.': 'dot', '/': 'slash', '\n': 'ret',
    '!': 'shift-1', '@': 'shift-2', '#': 'shift-3', '$': 'shift-4',
    '%': 'shift-5', '^': 'shift-6', '&': 'shift-7', '*': 'shift-8',
    '(': 'shift-9', ')': 'shift-0', '_': 'shift-minus',
    '+': 'shift-equal', '{': 'shift-bracket_left',
    '}': 'shift-bracket_right', ':': 'shift-semicolon',
    '"': 'shift-apostrophe', '~': 'shift-grave_accent',
    '|': 'shift-backslash', '<': 'shift-comma', '>': 'shift-dot',
    '?': 'shift-slash',
}


def keyname(ch):
    """QEMU sendkey name for one character."""
    if ch in KEYNAME:
        return KEYNAME[ch]
    if 'A' <= ch <= 'Z':
        return 'shift-' + ch.lower()
    return ch


def mon(s, cmd):
    s.sendall(cmd.encode() + b'\n')
    time.sleep(0.05)
    try:
        return s.recv(4096).decode(errors='replace')
    except socket.timeout:
        return ''


def type_line(s, line):
    for ch in line:
        mon(s, 'sendkey %s' % keyname(ch))
        time.sleep(0.03)
    mon(s, 'sendkey ret')


def read_log(path):
    try:
        with open(path, 'rb') as f:
            return f.read().decode(errors='replace')
    except OSError:
        return ''


def main():
    if not os.path.exists(IMG):
        print('no image at %s - run make image first' % IMG)
        return 1

    tmp = tempfile.mkdtemp(prefix='vodya-bash-')
    sockpath = os.path.join(tmp, 'mon.sock')
    seriallog = os.path.join(tmp, 'serial.log')

    qemu = subprocess.Popen([
        'qemu-system-x86_64', '-M', 'pc', '-m', '512',
        # -M pc, not q35: the ATA driver speaks legacy IDE PIO (0x1f0);
        # q35's ICH9 is AHCI-only, 0x1f7 reads 0xFF there.
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

        # wait for the bash prompt (bash's PS1) or banner timeout
        prompt = False
        for _ in range(60):                 # up to ~60s
            log = read_log(seriallog)
            if 'Spawning /gnu/bin/bash' in log and 'exec failed' not in log:
                prompt = True
                if 'vodya' in log.split('Spawning /gnu/bin/bash')[-1]:
                    break
            if 'exec failed' in log or 'FAILED' in log:
                break
            time.sleep(1)

        log = read_log(seriallog)
        if not prompt or 'exec failed' in log:
            print('FAIL: bash never started')
            return 1

        # bash is live: run a command and look for its output
        type_line(s, CMD)
        for _ in range(15):
            time.sleep(1)
            log = read_log(seriallog)
            if MARKER in log:
                break

        log = read_log(seriallog)
        if MARKER in log:
            print('PASS: bash booted from btrfs rootfs and executed a '
                'command (%s)' % MARKER)
            return 0
        print('FAIL: no output from %r' % CMD)
        return 1
    finally:
        qemu.kill()
        body = read_log(seriallog)
        if body:
            clean = body.replace('\x1b', '^[')
            print('--- serial tail ---')
            print('\n'.join(clean.splitlines()[-30:]))


if __name__ == '__main__':
    sys.exit(main())
