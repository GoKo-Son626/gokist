#ifndef __TYPES_H__
#define __TYPES_H__

// 定义了 xv6 内核中使用的基本数据类型和结构
// 它确保了代码在不同 RISC-V 平台上数据类型的
// 一致性和可移植性，并定义了如页表项等重要结构

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int  uint32;
typedef unsigned long uint64;

typedef uint64 pde_t;

#endif // !__TYPES_H__
