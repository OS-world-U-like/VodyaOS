# 交接文档：VodyaOS x86_64 移植

> 状态时间点：2026-10-28（本轮完成 userland 167/167 全链接、sh 可运行；**Limine UEFI 最小启动已打通**，见 §9）
> 目标：把整棵 Unix V7（TUHS 扁平化源码树）改为 x86_64 架构、**可编译**；现已进入可运行阶段。
> 附加要求：未来要支持 **aarch64 (ARM64)** 与 **loongarch64**，结构上必须预留。

---

## 1. 环境与工具链

- 宿主（本轮起已更换）：**x86_64 Linux**（Ubuntu 24.04），全部工具链经 apt 安装：
  - `clang` / `ld.lld` / `llvm-ar` / `llvm-nm`（交叉参数不变，见下）
  - `qemu-system-x86_64` + `qemu-x86_64`（qemu-user，用户态运行验证）
  - `bison`、`flex`、`gdb`（配合 `qemu-x86_64 -g` 调试；静态 x86_64 产物也可直接本机 gdb 运行）
- 交叉编译：
  - C 编译器：`clang --target=x86_64-unknown-none-elf`
  - 链接器：`ld.lld -m elf_x86_64`
  - 归档：`llvm-ar`
  - 语法生成：`bison`（apt 安装）
- 用户态可执行文件统一静态链接 `--image-base=0x400000`，qemu-user 或本机直接运行。
- libc 系统调用走 **Linux x86_64 ABI**（目前没有真正的 V7 内核可跑），符号用 `#pragma weak`，
  允许程序自带同名符号覆盖。
- 运行 lex 需要 `/usr/lib/lex/ncform`（树内 `usr/lib/lex/ncform`，需拷到宿主该路径；
  未来打 rootfs 时放进镜像即可）。

标准编译参数（`tools/build.py` 内置）：

```
--target=x86_64-unknown-none-elf -std=gnu89 -ffreestanding -fno-builtin
-fno-stack-protector -fno-pic -fno-pie -fcommon -Dunix
-nostdinc -Iusr/include -Iport/x86_64/include -Wno-everything
```

内核额外：`-Iusr/sys -Iport/x86_64/kernel -mno-red-zone`。

---

## 2. 目录结构与职责

```
Makefile                     入口：make [ARCH=x86_64] [all|libs|kernel|userland|gen|clean]
mk/arch-x86_64.mk            已实现：工具链/参数/kernel.ld/image base
mk/arch-aarch64.mk           占位：文件清单 + 需要填写的变量（ARCH_SUPPORTED := no）
mk/arch-loongarch64.mk       占位：同上
tools/build.py               构建驱动（架构无关）：libs/kernel/userland、程序清单、并行编译
tools/gen.sh                 重新生成 build/gen/ 下所有 yacc/lex 派生源码
tools/gramfix.py             把 V7 yacc 旧语法（%term、`= action`、rules 区的 %{ %}）转换为 bison 可吃
tools/genawk.py              由 awk y.tab.h 生成 token.c（等价 V7 tokenscript 的 ed 脚本）
tools/fixproctab.py          修正 awk proc 生成器输出里的 `[] {` 初始化
tools/fixcgram.py            把 mip/cgram.c 的 enum yytokentype 换成 #define（与 manifest 的 #define 冲突）
port/x86_64/kernel/          start.S / context.S / arch.c / kernel.ld（替代 V7 mch.s、l.s）
port/x86_64/libc/            start.S / setjmp.S / syscall.c / misc.c / format.c / scan.c
port/x86_64/libm/math.c      frexp/ldexp/modf
port/x86_64/libplot/plotstub.c  弱符号空实现（V7 的 libplot 是预编译 PDP-11 归档）
port/x86_64/README.md        x86_64 移植层说明 + 明确列出不移植的纯 PDP-11 asm
port/aarch64/README.md       未来 ARM64 移植需要提供的文件清单
port/loongarch64/README.md   未来 LoongArch64 同上
build/gen/                   已提交的生成源码（awk/eqn/neqn/cpp/m4/lex/mip/ratfor/struct/f77/make）
build/<arch>/                构建产物（已 .gitignore）：kernel.elf、lib/*.a、bin/*
usr/include/sys/*.h          从 usr/sys/h 复制（V7 安装时同样这么做），供用户态 -nostdinc 使用
```

---

## 3. 已完成的工作

### 3.1 构建系统

- `make` / `make ARCH=x86_64` 一条命令构建 `libs → kernel → userland`。
- 输出：`build/x86_64/kernel.elf`、`build/x86_64/lib/*.a`、`build/x86_64/bin/*`。
- `make gen` 可重新生成 `build/gen/`（需要 bison；stage 2 还需要已构建的 libc 与 lex）。
- `make ARCH=aarch64` / `loongarch64` 会给出明确的"未实现 + 需要补哪些文件"提示。
- `tools/build.py` 中的程序清单按 V7 makefile 还原，特殊的（awk、refer、uucp、f77、mip/pcc、
  lint、troff、learn、lpr、make、ratfor、c0/c1/c2、standalone、chess）显式列出，其余自动发现 main。

### 3.2 内核

- `usr/sys/sys/*.c` + `usr/sys/dev/*.c` + `usr/sys/conf/c.c` + `port/x86_64/kernel/*` 编译通过。
- **`kernel.elf` 是合法 ELF64 可执行文件，链接成功**；启动未做（当前不要求）。
- 为绕过 V7 的"同一目录多个互斥驱动"（如 dhdm/dhfdm、fakemx/mx1+mx2），链接采用归档方式：
  `libksys.a`（sys + arch.c）与 `libkdev.a`（dev），由归档解析决定拉取哪个目标文件。
- 关键源码修补（保持 V7 语义，只改现代 C 不接受之处）：
  - `usr/sys/h/tty.h`：匿名 union 展开为内联匿名 struct。
  - `usr/sys/dev/lp.c`：去掉 `struct { char lobyte, hibyte; }` 左值 hack，显式按字节访问。
  - `usr/sys/dev/mx2.c`：`FP = getf(...)` 左值强转改为 `cp = (struct chan *)getf(...)`。
  - `usr/sys/dev/tty.c`：为历史拼写不一致补 `ttioccom` 包装。
  - `usr/sys/h/{types,param,smallparam}.h` 与 `usr/include/sys/param.h`：`label_t` 扩为 `long[8]`。

### 3.3 libc / 库

- `libc.a`：由 `usr/src/libc/{gen,stdio,sys}` + `v6/ftime.c` + `port/x86_64/libc/*` 构建。
  - 排除并替换：`stdio/{printf,fprintf,sprintf,scanf,doscan}.c`（由 `port/x86_64/libc/{format,scan}.c` 提供），
    所有 libc `.s`、`v6/*`（除 ftime.c）、`csu/*`。
  - `port/x86_64/libc/syscall.c` 提供 Linux ABI 包装；`stat` 做 `struct stat` 字段翻译。
- `libm.a`、`libmp.a`、`libdbm.a`、`libplot.a`（仅弱符号 stub）、`libF77.a`、`libI77.a`、`libln.a` 全部构建成功。
- 已验证：`cat` 可直接在 `qemu-x86_64` 下正确读写；`sh` 链接成功（49 KB x86_64）；stdio（fopen/getc/printf/fflush）
  与 `exit()` 的 `_cleanup()` 链路正常。

### 3.4 用户态移植进度

- **167 个程序链接成功**（`make userland`，含 awk/beautify），**0 个失败**。
- 全部 `usr/src/cmd`、`usr/src/games` 的 C 文件均可编译。
- 已验证可运行：`cat`、`echo`、`sort`、`wc`、`sed`、`grep`、`awk`、`head 缺失（V7 无此源码）`、
  `lex`（可完整生成 lex.yy.c）、**`sh`**（赋值/变量展开/for 循环/管道/`-c` 均可）。
- awk 的 `awk.lx.c`、struct 的 `lextab.c` 已由修好的 lex 生成并入库 `build/gen/`。

已处理的 V7 方言/移植问题类别（今后改代码时请沿用同样思路）：

| 问题 | 处理方式 | 代表文件 |
|---|---|---|
| 匿名 union/struct 成员重名/覆盖 | 命名内层 struct、合并为成员超集 struct、或展开为内联匿名 struct | `usr/sys/h/tty.h`、`mip/{manifest,mfile1,mfile2}`、`sed/sed.h`、`cmd/c/{c0.h,c1.h}`、`adb/{mode.h,defs.h}`、`f77/defs` |
| 老式赋值运算符 `=+ =- =| =/ =% =& =^ =<< =>>` | 改为 `+= -= |= /= %= &= ^= <<= >>=` | `games/chess/*.c`、`cmd/c/*`、`cmd/osh.c`、`cmd/standalone/*`、`cmd/lex/sub1.c` |
| 无 `=` 的初始化（`int x 1;`、`char a[] "s";`、`} t {`、`[] {`） | 补 `=` | adb、refer、troff/font、troff/term、lex/once.c 等（大多数已修） |
| `static` 定义出现在非 static 声明之后 | 去掉定义处的 `static`（保持外部链接一致） | f77、libF77、uucp、make、standalone、libc/v6/stat.c |
| 函数内 `extern` 泄漏到文件作用域（老 C 特性） | 把声明提到文件作用域 | `m4/m4y.y`、`refer/{mkey2,glue4}.c`、`uucp/conn.c`、`make/{dosys,main}.c` |
| 隐式 int 实为指针 | 补正确类型/局部指针 | `cmd/c/c01.c`、`c02.c`、`c12.c`、`refer/glue5.c`、`adb/*` |
| `inline` / `const` 被当函数名 | 改名（`doinline`、`inline0`、`constop`、`konst`） | `eqn/io.c`、`neqn/io.c`、`f77/intr.c`、`f77/defs`、`cmd/c` |
| 缺失的宏/字段名拼写 | 按同目录既有定义对齐 | `uucp/chkpth.c`（st_nlink）、`f77/{driver,lex,pdp11,proc,io}.c`、`libI77` |
| PDP-11 字节/字覆盖（如 byteswap） | 用 `char *` 显式按字节实现 | `games/chess/book.c` |
| 函数指针数组存成 `int[]` | 改为 `int (*x[])()` | `games/chess/data.c`（wheur/bheur） |
| 缺失的生成文件 | 用 bison 生成或用 Python 复刻 ed 脚本 | `build/gen/*`、`tools/genawk.py` |

---

## 4. 已修复的问题（本轮，2026-10-28）

原第 4 节列出的遗留问题已全部解决。记录根因，避免今后重蹈：

### 4.1 `lex` 崩溃 → 已修复，根因是老式赋值运算符残留

- `usr/src/cmd/lex/parser.y:635` 的 `ccptr =+ slength(token) + 1;`（`lmain.c`、`sub1.c`、
  `sub2.c` 等也有）在现代 C 里解析为 `ccptr = (+...)`，把指针赋成了小整数 → `yyparse` 里
  `*ccptr++` 写到地址 11 段错误。
- 全树扫掉了 **23 处**残留的 `=+ =- =* =| =&`（osh.c、c02.c、backgammon.c、wump.c、
  neqn/sqrt.c、sub1/sub2/parser.y 等）。printf 格式串里的 `=+`/`=%` 是误报，勿盲改。
- `tools/gramfix.py` 新增 `fix_oldops()`：再生成 pre.y 时自动转换（只认 V7 风格"运算符后跟
  空白"的形式，避免误伤 `x = -1`）。
- `sub2.c:797` 的 `for(i=0;i<=yytop;i=+4)` 会被含 `<=` 的过滤条件漏掉，注意。
- lex 还需要 `/usr/lib/lex/ncform`（见 §1）。

### 4.2 5 个链接失败 → 全部修复

| 程序 | 真实根因 | 修复 |
|---|---|---|
| `structure` | libc 的 `stdio/endopen.c` 定义了非 static 的 `create`，被链接拉入后与 structure 自己的冲突 | `endopen.c` 的 `create` 改 `static`（补前置声明，C89 不允许块内 static 声明） |
| `inv` | `build.py` 的 inv 列表多加了 `thash.c`（V7 原版 makefile 的 inv 不含 thash；thash 是自带 main 的独立测试程序） | 从列表删除 `thash.c` |
| `nroff`/`troff` | **build.py 的对象文件名不含宏定义**：n1.c 同时以 `-DNROFF`（nroff）与无宏（troff）编译到同一个 `.o` 路径，互相覆盖 | obj 文件名追加 defs 标签（`..._n2_DNROFF.o`）；注意旧产物会被 mtime 判断误保留，需删除重建 |
| `f77pass1` | `setbounds.c` 在树内但没进 `build.py` 的 f77p1 列表，且该文件缺 `#include "defs"` | 列表加入 `setbounds.c`；文件头补 include |

### 4.3 `awk`/`beautify` 生成文件与符号

- `awk.lx.l` 的 `int lineno 1;`（无 `=` 老式初始化）原样穿透到生成的 `awk.lx.c` → 补 `=`。
- `beautify` 需要 `libln.a`（yywrap）→ `DEFAULT_LIBS` 加入 `lib/libln.a`；同时从 `libF77.a`
  和 `libln.a` 归档中排除 `main.c`（各自自带 main，会在 `--start-group` 时被拉入与其他程序的
  main 冲突）。

### 4.4 `sh` 从段错误到可运行（对移植最有参考价值的一组）

V7 程序有一批**依赖 PDP-11 内存模型**的隐式行为，Linux/qemu-user 上都会踩坑：

1. `defs.h` 的 `address end[];`（意图是引用 ld 自动提供的 `end` 符号= bss 末尾）在现代链接器下
   变成普通 BSS 变量，alloc 竞技场从 bss 中间开始，一分配就覆盖全局变量。改为
   `extern char end[];`（lld 会提供真正的 `end`）。**注意 build.py 不跟踪头文件依赖，改 .h 后
   必须删掉对应 .o 强制重编。**
2. V7 的数据段里 break 之上到栈是**常映射**的，sh 大量 push 路径只记账不 brk。Linux 上必须
   真 brk：`addblok` 扩 arena 前调 `setbrk(reqd)`；`main` 启动时多预映射 `BRKSLACK`(128K，
   `brkincr.h`)；`staknam`（绕过 locstak 的路径）补 brkend 检查。
3. V7 用户地址 0 可读（`syslook(0)` 解引用 NULL 判首字符无害）→ `syslook` 加空指针保护。

### 4.5 已排除但需在文档中保持说明

- `usr/src/cmd/mip/fort.c` 依赖的 `fort.h` 在原树中缺失（TUHS 上也未必有），当前不构建；
  如需构建，需从 TUHS 其他版本找 `fort.h` 或自行复原。
- 纯 PDP-11 汇编无法机械移植，明确不构建（保留源码作参考）：
  `cmd/as`、`cmd/bas/bas.s`、`cmd/roff/*.s`、`games/chess/*.s`（C 部分可编译）、
  `cmd/standalone/*.s`（C 部分仅编译不链接）、`cmd/c/table.s`（因此 `c1` 只编译不链接）、
  `cmd/{factor,primes}.s`、`libfpsim/*.s`、`mdec/*.s`、`bin/`、`etc/`。
- `cmd/standalone` 与 `games/chess` 的 C 文件标记为 compile-only（链接需要 PDP-11 crt0/汇编）。
- V7 无 `head` 源码（`head` 是后起的命令），不要在测试脚本里假设它存在。

---

## 5. 常用命令

```bash
cd <repo>

make                      # libs + kernel + userland（x86_64）
make libs                 # 只构建库
make kernel               # 只构建 build/x86_64/kernel.elf
make image                # UEFI 引导镜像 build/x86_64/vodya.img（见 §9）
make userland             # 只构建 build/x86_64/bin
make gen                  # 重新生成 build/gen（需要 bison；stage2 需要已构建 libc/lex）
make clean                # 删除 build/x86_64

# 直接驱动（可加 -j、--strict）
python3 tools/build.py --arch x86_64 all
python3 tools/build.py --arch x86_64 -j 16 userland

# 运行验证（用户态）
echo hello | qemu-x86_64 build/x86_64/bin/cat
qemu-x86_64 build/x86_64/bin/echo hi

# 检查内核产物
readelf -h build/x86_64/kernel.elf
```

编译检查脚本（在仓库外，上一轮批量诊断用过）：
`/tmp/opencode/cc.py`（逐文件编译、汇总失败；对应用 `tools/build.py` 的 per-dir -I/-D 规则）。
如果还要继续批量排查，建议把它整理进 `tools/check.py`。

---

## 6. 多架构（aarch64 / loongarch64）预留说明

架构相关代码**全部**在 `port/<arch>/` 下，构建驱动与 Makefile 不含任何 x86_64 专有逻辑：

- 新增架构时需要提供（x86_64 版可直接参考/复制）：
  - `port/<arch>/kernel/{start.S, context.S, arch.c, kernel.ld}`
    - 内核入口、trap/中断入口、`spl*`/`splx`、`copyin/copyout`、`fu*/su*`、`clearseg/copyseg`、
      `save/resume`（`label_t` 已统一为 `long[8]`）、以及 mch.s 曾提供的全局量
      （`struct user u`、`cputype`、`waitloc` 等；`regloc[]` 仍在 `usr/sys/sys/trap.c`，不要重复定义）。
  - `port/<arch>/libc/{start.S, setjmp.S, syscall.c, misc.c, format.c, scan.c}`
    - 用户态 crt0（`_start → main → exit`）、setjmp/longjmp、系统调用包装（Linux aarch64：
      `x8` 传调用号；loongarch64：`a7` 传调用号），便于 qemu-user 下先跑通。
  - `port/<arch>/libm/math.c`、`port/<arch>/libplot/plotstub.c`（基本可原样复制）。
- 在 `mk/arch-<arch>.mk` 填好 `CC/LD/AR/EMU/ARCHCFLAGS/KERNEL_CFLAGS/IMAGE_BASE/KERNEL_LD`，
  并把 `ARCH_SUPPORTED := yes`。
- 在 `tools/build.py` 的 `ARCHCONF` 填入对应项（结构见文件开头）。
- 注意点：
  - aarch64 内核建议 `-mgeneral-regs-only`（V7 内核无 FPU 上下文）；
  - loongarch64 的 `spl*` 要映射到 CRMD/PRMD 中断级别；
  - 两种架构的 `copyin/copyout` 建议用异常修复表（extable）或 access-with-fixup 方式；
  - 内存模型/原子性：V7 内核依赖 PDP-11 的 spl 屏蔽，移植时需保证 `spl*` 与中断路径正确。

---

## 7. Git 状态

- 当前提交：`1325010 port: x86_64 build system and initial 64-bit port`
- 已推送：`origin/master`（`https://github.com/OS-world-U-like/VodyaOS`）
- 提交身份：`相见丿 <136219691+xiangjian520@users.noreply.github.com>`（`gh` 登录账号 `xiangjian520`）
- `.gitignore` 已排除 `build/<arch>/`、`build/{bin,lib,obj}/`、`*.o/*.a` 等；`build/gen/` 是**有意提交**的，
  保证没有 bison 也能直接 `make`。

---

## 8. 建议的后续顺序

1. ~~修复 lex 崩溃 / 5 个链接失败~~（已完成，见 §4）。
2. ~~Limine 最小启动~~（已完成，见 §9）。
3. 把 `/tmp/opencode/cc.py` 整理成 `tools/check.py`，作为 CI 式回归检查。
4. 补写 `docs/PORTING-x86_64.md`（范围、架构分层、legacy asm 决策），与本文档合并/去重。
5. 内核真正跑起来：Limine 之上搭 V7 main 所需环境——IDT/trap 入口、8259A 或 APIC、
   PIT 时钟、物理页帧分配器 + 恒等映射页表（V7 `main()` 假设 bss 清零、`cputype` 等
   arch 全局量已备好），然后让 `start.S` 的 `call main` 重新生效。
6. sh/awk 等在 qemu-user 下的深水区问题继续按 §4.4 的套路逐个排掉。
7. 之后按第 6 节加 aarch64、loongarch64。

---

## 9. Limine 最小启动（UEFI only，已打通 ✅）

> 按用户要求**只支持 UEFI，不做传统 BIOS 引导**（不打包 limine-bios-*.bin、
> 不做 El Torito ISO、不需要 `limine bios-install`）。

### 9.1 设计

- 引导器 **Limine 8.7.0**（`limine/`，clone 自
  `github.com/limine-bootloader/limine` 的 `v8.x-binary` 分支，host 工具已 `make`）。
  启动链：OVMF/UEFI 固件 → `\EFI\BOOT\BOOTX64.EFI` → 读取
  `/boot/limine/limine.conf` → 按 ELF PHDR 加载 `/boot/kernel.elf` → 跳入口。
- 镜像：32MB 裸盘 + **GPT 单一 EFI 系统分区**（FAT16 —— 30MB 分区低于 FAT32
  最小 65525 簇数，OVMF 的 FAT 驱动会拒绝 FAT32）。
- **内核必须高半区链接**：Limine 协议要求
  `vaddr = paddr + 0xffffffff80000000`（LIMINE_KERNEL_BASE），物理从 1MiB 起。
  Limine 进 long mode 后已开分页映射好内核与 HHDM，入口在链接地址直接可跑。
  每个权限组（RX / R / RW）的输出段**按 4K 对齐**——Limine 拒绝同一物理页内
  权限不同的 PHDR。
- 内核 C 代码因此加 `-mcmodel=kernel`（默认 code model 的 32 位绝对重定位
  在高半区放不下）。V7 内核 C 全量随链，但入口暂只跑最小引导代码。
- `.limine_requests` 段携带 base revision + framebuffer 请求；输出走
  **COM1 串口 0x3F8**（qemu `-serial` 可见）。`limine.conf` 里 `serial: yes`
  让 Limine 自身的菜单/报错也走串口，调试必备。
- 最小入口 `limine_start`：打印横幅 + framebuffer 信息 + `hlt` 循环，
  **暂不调用 V7 `main()`**（需要先有 IDT/中断/页表，见 §8.5）。

### 9.2 文件

```
port/x86_64/kernel/limine.S     请求结构（.limine_requests 段，magic/revision/framebuffer）
port/x86_64/kernel/limine.c     limine_start()：串口初始化 + 横幅 + hlt
port/x86_64/kernel/start.S      入口：设栈 → call limine_start → hlt（call main 已注释待启用）
port/x86_64/kernel/kernel.ld    高半区脚本：KERNEL_BASE=0xffffffff80000000，各段 AT(paddr)，
                                4K 对齐，KEEP(*(.limine_requests))
tools/limine.conf               serial: yes / timeout / protocol: limine / kernel_path
tools/mkimage.sh                32MB 裸盘 + GPT + FAT16 ESP，mtools/mkfs.vfat --offset 免 root 填充
Makefile                        image/run 目标（run 用 -bios /usr/share/ovmf/OVMF.fd）
tools/build.py                  kernel_cflags 加 -mcmodel=kernel；链接目标追加 limine.o
limine/                         v8.x-binary 分支（BOOTX64.EFI 等；无 CONFIG.md 文档，配置
                                语法见上游主分支 CONFIG.md）
```

### 9.3 构建 / 运行

```bash
make kernel                 # build/x86_64/kernel.elf（高半区 ELF，entry 0xffffffff80000000）
make image                  # build/x86_64/vodya.img（GPT + ESP，含 BOOTX64.EFI/kernel.elf/limine.conf）
make run                    # qemu-system-x86_64 -M q35 -bios OVMF.fd -drive vodya.img -serial stdio
# 预期串口输出：
#   VodyaOS x86_64 kernel: booted via Limine
#   framebuffer: 1280x800x32 @ ffff800080000000
```

无显示环境调试时用 `-serial file:/tmp/serial.log -display none`，
`tr -d '\033' < /tmp/serial.log | sed 's/\[[0-9;=]*[A-Za-z]//g'` 可滤掉 ANSI 码读文本。

### 9.4 踩过的坑（按序，都是真实报错）

1. **菜单出现但内核不加载、串口无声**：Limine 控制台默认走图形 framebuffer，
   串口看不到报错 —— `limine.conf` 顶部加 `serial: yes` 后能看到 panic。
2. `PANIC: Boot protocol not specified for this entry`：Limine v8 不再自动
   探测，entry 必须显式写 `protocol: limine`。
3. `PANIC: elf: Lower half PHDRs are not allowed`：内核是平坦链接
   0x100000，需改高半区链接脚本 + `-mcmodel=kernel` 重编（否则
   `R_X86_64_32 out of range`）。
4. `PANIC: elf: PHDRs with different permissions sharing the same memory
   page`：RX/R/RW 各输出段 4K 对齐即可。
5. 小 ESP 上 FAT32 会被 OVMF 拒绝（BdsDxe "failed to load Boot0001"），
   用 `mkfs.vfat -F 16 -s 4 --offset <起始扇区>` + mtools `-i img@@"偏移字节"`。
6. 升级 Limine 版本时 `port/x86_64/kernel/limine.S` 里的 base revision
   魔数要同步。
