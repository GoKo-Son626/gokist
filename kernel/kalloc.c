#include "param.h"
#include "types.h"
#include "riscv.h"
#include "memlayout.h"
#include "defs.h"

/* *
 * 1page
 * 1page
 * 1page
 * 1page
 * 1page
 * 1page
 * 1page
 *           -> end tag
 * kernel
 *           -> 0x80000000
 * I/O
 * devices
 *           -> 0x0
 * */

extern char end[]; //kernel.ld中定义的地址，内核镜像的结束地址

struct run{
	struct run* next;
};

struct{
	struct run* freelist;
}kmem;

// 空闲地址的初始化
void kinit()
{
	freerange(end, (void*)PHYSTOP);
}

// 针对一个物理内存的地址范围进行初始化
void freerange(void* pa_start,void* pa_end)
{
	char *p;
	p = (char*)PGROUNDUP((uint64)pa_start);
	for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
		kfree(p);
}

// 将内存地址放置到上述链表中
void kfree(void *pa)
{
	struct run *r;

	if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
		panic("kfree");

	// Fill with junk to catch dangling refs.
	// ?????
	memset(pa, 1, PGSIZE);

	r = (struct run*)pa;

	// acquire(&kmem.lock);
	r->next = kmem.freelist;// 第一次为0, 因为全局变量，
				// 所以同理freelist为0就证明地址耗尽了
	kmem.freelist = r;
	// release(&kmem.lock);
}

// 分配物理地址
void* kalloc()
{
	struct run *r;

	// 从freelist头部拿出一页
	// acquire(&kmem.lock);
	r = kmem.freelist;
	if(r)
		kmem.freelist = r->next;
	// release(&kmem.lock);

	if(r)
		memset((char*)r, 5, PGSIZE); // fill with junk
	return (void*)r;
}

// 测试
void kmemtest()
{
    uint64* p1 = (uint64*)kalloc();
    if(p1 != 0 )
    {
        *p1 = 0x123456;
        printf("p1=%p\n",p1);
    }
    uint64* p2 = (uint64*)kalloc();
    if(p2 != 0 )
    {
        *p2 = 0x11223344;
        printf("p2=%p\n",p2);
    }

    // 释放顺序
    kfree(p2);
    kfree(p1);
    uint64* p3 = (uint64*)kalloc();

    if(p3 != 0 )
    {
        *p3 = 0x11223344;
        printf("p3=%p\n",p3);
    }
}
