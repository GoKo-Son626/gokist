// 实现了 xv6 内核统一的中断和异常处理机制
// 它负责捕获所有来自 CPU 的陷阱事件
// （包括系统调用、时钟中断和硬件异常）
// 并调度到相应的处理函数。

#include "types.h"
#include "riscv.h"
#include "defs.h"

// void trapinithart();
// void kerneltrp();
// int devintr();

// set stvec
void
trapinithart(void)
{
  w_stvec((uint64)kernelvec);
}

// interrupts and exceptions from kernel code go here via kernelvec,
// on whatever the current kernel stack is.
void 
kerneltrap()
{
	int which_dev = 0;

	which_dev = devintr();
	if (which_dev == 0) {
		uartputs_temp("panic: interrupts not handle\n");
		while (1) {
		}
	}

	if (which_dev == 2) {
		uartputs_temp("timer interrupts ...\n");
	}
}

int devintr()
{
	uint64 scause = r_scause();

	// 旧版本
	// 1...1 64位 
	// if(scause == 0x8000000000000001L) {
		// w_sip(r_sip() & ~2);
	// 
	// 新版本
	// 1..101 64位
	if(scause == 0x8000000000000005L) {
		w_stimecmp(r_time() + 1000000 * 10 * 2);
		return 2;
	}

	return 0;
}
