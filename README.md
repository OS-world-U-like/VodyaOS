# VodyaOS

## 追逐梦想

VodyaOS 是一个以 Unix 血脉为底色的操作系统研究与重构项目，目标是从历史 Unix 的根源出发，重新理解系统设计、接口、内核与用户态构成，并在现代工程实践中延续“追逐梦想”的精神。

我们不是在复制历史，而是在研究历史；我们不是在模仿旧代码，而是在从经典中汲取灵感，并重新定义未来的系统构建方式。

## 历史来源：TUHS / Unix 历史档案

本项目采用公开的、权威性更高的 Unix 历史源码档案，优先参考 TUHS（The Unix Heritage Society）及其整理仓库，而不是普通 GitHub 上的非官方二次镜像。

- TUHS: https://www.tuhs.org/
- Unix history repo: https://github.com/dspinellis/unix-history-repo
- 参考分支: `Research-PDP7-Snapshot-Development`

这意味着：
- 我们参考的是历史源码档案与公开存档资料
- 我们承认这些资料是对经典 Unix 研究的重要依据
- 我们不把普通 GitHub 镜像当作权威历史源

## V7 参考来源

本项目将 Unix V7 视为关键的历史研究对象，并将公开历史档案中的 V7 资料作为参考源。

为了保证可追溯性，仓库已接入 `unix-history-repo` 作为历史源码参考入口：

- 路径: `third_party/unix-history-repo`
- 仓库: `https://github.com/dspinellis/unix-history-repo.git`
- 分支: `Research-PDP7-Snapshot-Development`

## 目录结构

```text
VodyaOS/
├── README.md
├── .gitmodules
├── LICENSE
├── third_party/
│   └── unix-history-repo/   # 公开历史 Unix 源码参考
└── src/
```

## 说明

这个仓库主要用于：

- 研究经典 Unix 的设计思想
- 参考历史源码的结构与实现方式
- 在现代工程中重新组织和扩展 Unix 血统的概念

## 结语

VodyaOS 所追逐的，不只是系统本身，而是理解计算机历史、理解 Unix 精神、以及理解如何构造可靠且有意义的操作系统。

我们希望从经典中走出来，重新定义未来。
