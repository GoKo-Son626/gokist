// 核心头文件，包含了整个 xv6 内核中几乎所有函数、全局变量的外部声明（extern）
// 它的作用是提供一个集中的声明列表，使得不同 C 语言源文件中的函数能够互相调用
// 并确保编译器在链接时能够找到这些符号，从而避免因函数未声明而导致的编译错误

#ifndef __DEFS_H__
#define __DEFS_H__

#include "types.h"

// uart.c
void uartinit();
void uartputc_temp(char c);
void uartputs_temp(char* s);

// kernelvec.S
void kernelvec();
void timervec();	// entry of M mode 

// trap.c 
void trapinithart();
void kerneltrp();
int devintr();

#endif // !__DEFS_H__
