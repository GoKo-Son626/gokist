// 核心头文件，包含了整个 xv6 内核中几乎所有函数、全局变量的外部声明（extern）
// 它的作用是提供一个集中的声明列表，使得不同 C 语言源文件中的函数能够互相调用
// 并确保编译器在链接时能够找到这些符号，从而避免因函数未声明而导致的编译错误

#ifndef __DEFS_H__
#define __DEFS_H__

#include "types.h"

struct cpu;
struct spinlock;
struct buf;

// uart.c
void uartinit();
void uartputc_temp(char c);
void uartputs_temp(char* s);
int uartgetc();
void uartintr();

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

// plic.c
void plicinit();
void plicinithart();
int plic_claim();
void plic_complete(int irq);

// vm.c
void kvminit();
void kvminithart();
pagetable_t kvmmake();
void kvmmap(pagetable_t kpgtbl,uint64 va,uint64 pa,uint64 sz,int perm);
int mappages(pagetable_t pagetable,uint64 va,uint64 size,uint64 pa,int perm);

// virtio_disk.c
void	virtio_disk_init(void);
void	virtio_disk_rw(struct buf *, int);
void	virtio_disk_intr(void);
void	virtio_disk_test();

#endif // !__DEFS_H__
