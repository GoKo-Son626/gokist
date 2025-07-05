// 内核的启动大脑，它负责将一个个独立的模块
// （如内存管理、进程管理、文件系统）组织起来并进行初始化
// 最终让操作系统从一个裸机程序变成一个能运行用户进程的多任务系统

#include "types.h"
#include "riscv.h"
#include "defs.h"

const char *goko_full_logo =
"\n"
" _   _             _      _        _____	\n"
"| | | |    ___    | |    | |     //     \\\\      \n"
"| |_| |  // _ \\\\  | |    | |    ||	 ||	\n"
"|  _  | || ___ // | |___ | |___ ||       ||	\n"
"|_| |_|  \\\\____   |_____||_____| \\\\_____//	\n"
"						\n";

void main() {
	uartinit();
	printf("%s", goko_full_logo);
	printf("timerinit()******************************** \n");

	trapinithart();
	printf("trapinit()******************************** \n");

	kinit();
	kmemtest();
	printf("kinit()******************************** \n");

	kvminit();
	kvminithart();
	printf("kvminit()********************************\n");

	plicinit();
	plicinithart();
	printf("plicinit()********************************\n");

	virtio_disk_init();
	printf("virtio_disk_init()********************************\n");

	// enable interrupts and exceptions in S mode
	w_sstatus(r_sstatus() | SSTATUS_SIE);


	while (1)
		;
}
