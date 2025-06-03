.section .text		# define the code snippet

.global _entry		# define the entry
_entry:
	la sp,stack0	# point the sp to the start address of whole stack space
	li a0,1024*4	# set stack address
	csrr a1,mhartid	# read hartid of now to a1
	addi a1,a1,1	# avoid hartid 0
	mul a0,a0,a1	# a0=(1024*4) * (hartid+1)
	add sp,sp,a0	# sp=stack0+a0

	call start	# call start function

spin:
	j spin
/*
物理地址（PA）
↑ 高地址
│
│   +---------------------------+
│   |    用户栈（user stack）   |（每个进程分配，4KB）
│   +---------------------------+
│   |   用户代码/数据（user）   |
│   +---------------------------+
│   |         空闲内存          |（用于分配页框）
│   +---------------------------+
│   |      内核页表内存区      |（用于页表的页框）
│   +---------------------------+
│   |       trapframe 区域     |（每个进程保存陷入前寄存器）
│   +---------------------------+
│   |     struct proc（PCB）    |
│   +---------------------------+
│   |   内核栈（kernel stack）  |（每个进程一页）
│   +---------------------------+
│   |        内核代码区         |
│   |       text + rodata       |
│   +---------------------------+
│   |        内核数据段         |（data+bss）
│   +---------------------------+
│   |     trampoline page       |（跳陷页，用户转内核）
│   +---------------------------+
│   |     页表页：trampoline    |
│   +---------------------------+
│   |   UART / PLIC / CLINT     |（外设映射，0x10000000 起）
│   +---------------------------+
│   |     Boot ROM (maskrom)    |（通常不可写）
│   +---------------------------+
│
↓ 低地址（0x00000000）
*/
