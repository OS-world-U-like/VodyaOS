# VodyaOS

## 追逐梦想

VodyaOS 是一个以 Unix 血脉为底色的操作系统研究与重构项目,目标是从历史 Unix 的根源出发,重新理解系统设计、接口、内核与用户态构成,并在现代工程实践中延续"追逐梦想"的精神。

我们不是在复制历史,而是在研究历史;我们不是在模仿旧代码,而是在从经典中汲取灵感,并重新定义未来的系统构建方式。

当前主线:**把整棵 Unix V7(TUHS 扁平化源码树)移植到 x86_64**——不是模拟,而是真正编译出 64 位的 libc、用户态程序和内核,并能引导运行。架构上为未来的 aarch64 / loongarch64 移植预留了结构。

## 历史来源:TUHS / Unix 历史档案

本项目采用公开的、权威性更高的 Unix 历史源码档案,优先参考 TUHS(The Unix Heritage Society)及其整理仓库,而不是普通 GitHub 上的非官方二次镜像。

- TUHS: https://www.tuhs.org/
- Unix history repo: https://github.com/dspinellis/unix-history-repo
- 参考分支: `Research-PDP7-Snapshot-Development`

## 当前状态(2026-10-28)

| 部分 | 状态 |
|---|---|
| 用户态 | ✅ **167/167 全部链接成功**(V7 全套:sh、awk、sed、lex、yacc、ccom、troff/nroff、uucp……),sh / cat / sort / awk / sed / grep 等已在 qemu-x86_64 下实测可运行 |
| GNU 用户态 | ✅ **bash 5.2 + coreutils 9.5 + grep 3.11** 以 gcc `-static` 构建(`make gnu`),coreutils 为单二进制 busybox 式分发;已装入镜像 `::/gnu/bin` |
| libc / 库 | ✅ libc、libm、libmp、libdbm、libplot、libF77、libI77、libln 全部构建 |
| 内核 | 🔨 V7 内核 C 代码全量随链(`-mcmodel=kernel`,高半区链接),但 `main()` 尚未启用——缺 IDT/时钟中断/页表 |
| 引导 | ✅ **Limine UEFI-only 最小启动已打通**:OVMF → BOOTX64.EFI → kernel.elf → framebuffer 文本控制台(真机可见)+ 串口镜像,启动日志为 systemd 风格(绿色 `[  OK  ]`,CPU 型号 + 完整内存映射)。按项目要求**只支持 UEFI,不做传统 BIOS**;引导界面保持英文,内核 console 原生支持中文(UTF-8 + GB2312 点阵字模) |
| 镜像内用户态 | ✅ 167 个 V7 工具已装入镜像 `::/bin`（GNU 工具在 `::/gnu/bin`、源码树在 `::/source`），等内核具备 execve 能力即可直接使用 |
| CI | ✅ GitHub Actions 自动构建 + qemu 冒烟测试,每次构建产出可启动的 `vodya.img` |

## 快速开始

需要:clang + lld + llvm、bison(仅 `make gen` 需要)、qemu(`qemu-system-x86_64` + OVMF、`qemu-x86_64`)、sfdisk/mkfs.vfat/mtools(仅镜像需要)。

```bash
make                # libs + kernel + userland(默认 x86_64)
make gnu            # GNU 用户态:bash/coreutils/grep(gcc -static,需联网下源码)
make image          # UEFI 引导镜像 build/x86_64/vodya.img(需要 limine/ 下有 Limine v8.x-binary)
make run            # qemu + OVMF 启动镜像,串口可见内核横幅

# 用户态单跑
echo hello | qemu-x86_64 build/x86_64/bin/cat
echo 'x=42; echo $x' | qemu-x86_64 build/x86_64/bin/sh
```

Limine 引导器不在仓库内(见 `.gitignore`),获取方式:

```bash
git clone --branch v8.x-binary --depth 1 \
  https://github.com/limine-bootloader/limine.git limine && make -C limine
```

## 目录结构

```text
VodyaOS/
├── usr/src/            Unix V7 源码树(cmd/ libc/ sys/ games/ ...),移植的主战场
├── port/x86_64/        x86_64 架构相关(内核入口、framebuffer 控制台、字模、链接脚本、Limine 请求)
├── mk/                 架构描述(工具链、标志位);aarch64/loongarch64 预留
├── tools/              构建驱动 build.py、GNU 用户态 build-gnu.sh、字体生成 genfont.py/gencjkfont.py、mkimage.sh、limine.conf
├── build/gen/          预生成的 yacc/lex 产物(检出即可构建,无需 bison/lex)
├── build/x86_64/       构建产物(bin/ lib/ kernel.elf vodya.img)
├── docs/HANDOFF.md     ★ 交接文档:移植过程中的所有根因分析、踩坑记录、环境说明
└── limine/             (本地)Limine 引导器 clone,不入库
```

## 给接手的 AI / 贡献者

- **先读 `docs/HANDOFF.md`**。它是完整的交接文档:环境与工具链、已修复问题的根因(V7 老式赋值运算符、PDP-11 内存模型假设、nroff/troff 对象冲突等)、Limine UEFI 引导的全部调试记录、多架构预留说明。
- 构建系统入口是 `tools/build.py`(`Makefile` 只是薄封装);改头文件后注意它不追踪头文件依赖,需手动删对应 `.o`。
- 用户态调试:`qemu-x86_64 -g <port>` + gdb;静态 x86_64 产物也可以直接本机 gdb 跑。
- 架构约束:引导只支持 UEFI;用户态二进制链接在 `--image-base=0x400000`;内核高半区 `vaddr = paddr + 0xffffffff80000000`。

## 说明

这个仓库主要用于:

- 研究经典 Unix 的设计思想
- 参考历史源码的结构与实现方式
- 在现代工程中重新组织和扩展 Unix 血统的概念

### 许可

- 本项目以 **GPL v3** 发布(见 `LICENSE`)
- 树内 TUHS/Unix V7 历史代码的来源:TUHS(The Unix Heritage Society)
- `port/*/kernel/cjkfont.h` 字模数据源自 GNU Unifont(GPL 2+),生成方式见 `tools/gencjkfont.py`

## 结语

VodyaOS 所追逐的,不只是系统本身,而是理解计算机历史、理解 Unix 精神、以及理解如何构造可靠且有意义的操作系统。

我们希望从经典中走出来,重新定义未来。
