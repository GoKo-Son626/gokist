// 核心头文件，包含了整个 xv6 内核中几乎所有函数、全局变量的外部声明（extern）
// 它的作用是提供一个集中的声明列表，使得不同 C 语言源文件中的函数能够互相调用
// 并确保编译器在链接时能够找到这些符号，从而避免因函数未声明而导致的编译错误

#ifndef __DEFS_H__
#define __DEFS_H__

#include "types.h"

struct cpu;
struct spinlock;

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

// kalloc.c
void kinit();
void freerange(void* pa_start,void* pa_end);
void kfree(void* pa);
void* kalloc();
void kmemtest();

// string.c
void* memset(void *dst, int c, uint n);
int memcmp(const void *v1, const void *v2, uint n);
void* memmove(void *dst, const void *src, uint n);
void* memcpy(void *dst, const void *src, uint n);
int strncmp(const char *p, const char *q, uint n);
char* strncpy(char *s, const char *t, int n);
char* safestrcpy(char *s, const char *t, int n);
int strlen(const char *s);

// printf.c
int printf(char *fmt, ...);
void panic(char *s);

// proc.c
int cpuid();
struct cpu* mycpu();

// spinlock.c
void initlock(struct spinlock* lk,char* name);
void acquire(struct spinlock* lk);
void release(struct spinlock* lk);
int holding(struct spinlock* lk);
void push_off();
void pop_off(void);


#endif // !__DEFS_H__
