# 交接文档：VodyaOS x86_64 移植

> 状态时间点：commit `1325010`（已推送到 `origin/master`，GitHub: OS-world-U-like/VodyaOS）
> 目标：把整棵 Unix V7（TUHS 扁平化源码树）改为 x86_64 架构、**可编译**；暂不要求启动。
> 附加要求：未来要支持 **aarch64 (ARM64)** 与 **loongarch64**，结构上必须预留。

---

## 1. 环境与工具链

- 宿主：aarch64 Linux（无 x86_64 gcc/binutils 可用）。
- 交叉编译：
  - C 编译器：`clang --target=x86_64-unknown-none-elf`
  - 链接器：`ld.lld -m elf_x86_64`
  - 归档：`llvm-ar`
  - 运行产物：`qemu-x86_64`（用户态）
  - 语法生成：`bison`（apt 安装）
- 用户态可执行文件统一静态链接 `--image-base=0x400000`，以便 qemu-user 直接运行。
- libc 系统调用走 **Linux x86_64 ABI**（目前没有真正的 V7 内核可跑），符号用 `#pragma weak`，
  允许程序自带同名符号覆盖。

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

- **160 个程序链接成功**（`make userland`）。
- 全部 `usr/src/cmd`、`usr/src/games` 的 C 文件均可编译，**仅剩 2 个生成文件缺失**：
  `build/gen/awk/awk.lx.c`、`build/gen/struct/lextab.c`（需要 `lex` 生成，见第 4 节）。
- 剩余 5 个链接失败（详见第 4 节）：`structure`、`inv`、`nroff`、`troff`、`f77pass1`。

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

## 4. 遗留问题与下一步（按优先级）

### 4.1 `lex` 在 qemu 下崩溃（阻塞 awk / beautify）

现象：

```
$ qemu-x86_64 build/x86_64/bin/lex /tmp/t.l
2: (Warning) Invalid request %
qemu: uncaught target signal 11 (Segmentation fault) - core dumped
```

- 崩溃发生在**第一次输出刷新之后**（生成的 `lex.yy.c` 只有 512 字节，即一个 stdio 缓冲区）。
- 普通的 8 KB printf 输出程序 `./big` 在 qemu 下正常 → libc 的 stdio 大输出没问题。
- `-strace` 最后几步：`brk(...)` 若干次 → `ioctl(1, 0x7408, ...)` → `write(1, ...)` 成功 → SIGSEGV
  `si_addr=0x0000000000000018`（空指针偏移 0x18）。
- 建议排查顺序：
  1. `lldb`/`gdb` 挂 `qemu-x86_64 -g`（或直接用 `qemu-x86_64 -d in_asm,cpu` 看崩溃指令）定位到函数；
  2. 重点怀疑 lex 自己的表分配（`ldefs.c` 的 `trees`/`nextn`/`calloc` 使用）或 `fout` 的 stdio 路径；
  3. 对照 TUHS 原始 `lex` 的行为，确认不是移植层 `write`/`fflush` 的 bug；
  4. 临时绕过方案：用宿主 `flex`（若已安装）生成 `awk.lx.c` / `lextab.c`，或手工在宿主上构建一份
     x86_64 lex（宿主是 aarch64，需 qemu 或改用 flex 输出）。
- 生成命令（修好后）：

```
bash tools/gen.sh        # stage 2b 会用 build/x86_64/bin/lex 生成
# 产物： build/gen/awk/awk.lx.c、build/gen/struct/lextab.c
make userland
```

### 4.2 5 个链接失败

| 程序 | 错误 | 建议下一步 |
|---|---|---|
| `structure` | duplicate symbol: `create` | 用 `llvm-nm build/x86_64/obj/cmd/structure_*` 找出两个 `T create` 的对象；源码里只看到 `0.parts.c:100` 定义，另一个可能是 `0.alloc.c` 里不同写法的定义或库里同名符号。把其一改为 `static`/重命名 |
| `inv` | duplicate symbol: `main` | `inv` 的源码列表为 inv1/2/3/5/6 + deliv2 + thash；`inv1.c` 有 main，另有一个文件也定义了 main（用 `llvm-nm` 在两个对象里查 `T main`）。V7 makefile 原本 `inv?.o` 通配，注意 `inv3.c`/`inv5.c` 可能是测试用 main |
| `nroff` | undefined symbol: `t` | `t` 是终端表实例（`struct t`）。检查 `usr/src/cmd/troff/ntab.c`（nroff）与 `tab*.c`（troff）里 `t` 的定义；V7 里 `t` 很可能定义在 `n1.c` 或 `ntab.c`，需要把缺失的定义补回，或在对应主文件里加 `struct t t;` |
| `troff` | undefined symbol: `t` | 同上；troff 的 TFILES 为 n1–n5 + t6 + n7–n9 + t10 + ni + nii + tab3 + hytab + suftab（**不含 n10**，n10 只给 nroff） |
| `f77pass1` | undefined symbol: `setbounds` | `usr/src/cmd/f77/setbounds.c` 已补（原树缺失该文件，stub 语义降级），但**尚未加入 `tools/build.py` 的 f77p1 源列表**；在 `f77p1 = [...]` 里加 `'setbounds.c'` 即可 |

### 4.3 已排除但需在文档中保持说明

- `usr/src/cmd/mip/fort.c` 依赖的 `fort.h` 在原树中缺失（TUHS 上也未必有），当前不构建；
  如需构建，需从 TUHS 其他版本找 `fort.h` 或自行复原。
- 纯 PDP-11 汇编无法机械移植，明确不构建（保留源码作参考）：
  `cmd/as`、`cmd/bas/bas.s`、`cmd/roff/*.s`、`games/chess/*.s`（C 部分可编译）、
  `cmd/standalone/*.s`（C 部分仅编译不链接）、`cmd/c/table.s`（因此 `c1` 只编译不链接）、
  `cmd/{factor,primes}.s`、`libfpsim/*.s`、`mdec/*.s`、`bin/`、`etc/`。
- `cmd/standalone` 与 `games/chess` 的 C 文件标记为 compile-only（链接需要 PDP-11 crt0/汇编）。

---

## 5. 常用命令

```bash
cd <repo>

make                      # libs + kernel + userland（x86_64）
make libs                 # 只构建库
make kernel               # 只构建 build/x86_64/kernel.elf
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

1. 修复 `lex` 崩溃 → 生成 `awk.lx.c`、`lextab.c` → `awk`、`beautify` 链接。
2. 修 5 个链接失败（4.2 表格）。
3. 把 `/tmp/opencode/cc.py` 整理成 `tools/check.py`，作为 CI 式回归检查。
4. `make all` 全绿后，补写 `docs/PORTING-x86_64.md`（范围、架构分层、legacy asm 决策），
   与本文档合并/去重。
5. 再考虑启动（x86_64 引导、分页、trap、驱动）——当前明确不在范围内。
6. 之后按第 6 节加 aarch64、loongarch64。
