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

	if(scause == 0x8000000000000001L) {
		w_sip(r_sip() & ~2);
		return 2;
	}

	return 0;
}
