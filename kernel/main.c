#include "types.h"
#include "riscv.h"
#include "defs.h"

void main() {
	uartinit();
	uartputs_temp("Hello world!\n");
	trapinithart();
	uartputs_temp("Hello world @\n");

	// enable interrupts and exceptions in S mode
	w_sstatus(r_sstatus() | SSTATUS_SIE);


	while (1)
		;
}
