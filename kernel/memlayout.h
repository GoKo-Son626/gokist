// 头文件定义了 xv6 内核在 RISC-V 架构下的内存布局
// 它包含了物理和虚拟内存地址范围、大小以及重要的内存段
// （如内核代码、数据、设备映射区）的定义，是内核内存管理
// 和地址映射的基础，确保了代码和数据在内存中的正确位置

#ifndef __MEMLAYOUT__
#define __MEMLAYOUT__

#define UART0 0x10000000L

// core local interruptor (CLINT), which contains the timer.
#define CLINT 0x2000000L
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 + 8*(hartid))
#define CLINT_MTIME (CLINT + 0xBFF8) // cycles since boot.

#endif // __MEMLAYOUT__


