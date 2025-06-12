// 内核的启动大脑，它负责将一个个独立的模块
// （如内存管理、进程管理、文件系统）组织起来并进行初始化
// 最终让操作系统从一个裸机程序变成一个能运行用户进程的多任务系统

#include "types.h"
#include "riscv.h"
#include "defs.h"

void main() {
	uartinit();
	uartputs_temp("Hello world! \n");
	trapinithart();
	uartputs_temp("trapinithart() \n");
	kinit();
	kmemtest();
	uartputs_temp("kinit() \n");
	// enable interrupts and exceptions in S mode
	w_sstatus(r_sstatus() | SSTATUS_SIE);

	while (1)
		;
}
