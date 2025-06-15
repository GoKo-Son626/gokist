.
├── gdbinit        // GDB调试器启动时自动执行的命令序列，用于设置调试环境。
├── kernel         // 包含操作系统核心源代码及相关头文件的目录。
│   ├── defs.h       // 包含通用函数声明、全局宏和外部变量声明的头文件。
│   ├── entry.S      // RISC-V 架构的汇编入口点，负责最早期的启动和模式切换。
│   ├── kalloc.c     // 内核内存分配器（kmalloc/kfree）的实现，管理物理内存页。
│   ├── kernel.ld    // 链接器脚本文件，定义内核各段（代码、数据）在内存中的布局。
│   ├── kernelvec.S  // RISC-V 架构的汇编陷阱（中断/异常）入口点。
│   ├── main.c       // 内核的主入口文件，负责系统各部分的初始化调用。
│   ├── memlayout.h  // 定义内存布局的头文件，如物理内存范围、IO地址等。
│   ├── param.h      // 包含系统参数、限制和配置的头文件。
│   ├── printf.c      // 实现了简单的内核级打印（printf）函数。
│   ├── proc.c       // 进程管理的核心代码，包括进程创建、调度等。
│   ├── proc.h       // 进程相关的数据结构（如struct cpu, struct proc）和函数声明。
│   ├── riscv.h      // RISC-V 特定的寄存器操作宏和辅助函数。
│   ├── spinlock.c   // 自旋锁的实现，用于多核同步和防止竞态条件。
│   ├── spinlock.h   // 自旋锁数据结构和相关函数声明。
│   ├── start.c      // 内核的C语言启动部分，在汇编入口点之后执行。
│   ├── string.c     // 实现了基本的字符串和内存操作函数（如memset, memcpy）。
│   ├── trap.c       // 陷阱处理（中断和异常）的C语言部分，负责分发和处理。
│   ├── types.h      // 定义基本数据类型（如uint、pde_t等）的头文件。
│   ├── uart.c       // 串口（UART）驱动，用于早期的调试输出和控制台。
│   └── vm.c         // 虚拟内存管理代码，包括页表操作、映射等。
├── LICENSE        // 项目的许可文件，定义了代码的使用和分发条款。
├── Makefile       // 项目的构建脚本，用于编译、链接和运行内核。
├── note.md        // 包含项目相关笔记、文档。
└── README.md      // 项目的介绍文件、项目描述、构建和运行指南。

riscv: trap: exception and interrupt
  exception(同步): syscall, /0, ISA...
  interrupt(异步): out-devices, disk, UART...: CPU停下处理中断
  diff: mcause的execption位决定
    1:interrupt
    2:exception

