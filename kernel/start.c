#include "types.h"
#include "riscv.h"

void main();
char stack0[4096*8];

void start()
{
	// set that jump to S mode when mret
	unsigned long x = r_mstatus();
	x &= ~MSTATUS_MPP_MASK;	// clean the mode of former
	x |= MSTATUS_MPP_S;	// set the mode of former to 'S'
	w_mstatus(x);

	// set M Exception Program Counter to main, for mret.
	w_mepc((uint64)main);

	// disable paging for now.
	w_satp(0);

	// delegate all interrupts and exceptions to supervisor mode.
	w_medeleg(0xffff);	// interrupts
	w_mideleg(0xffff);	// exceptions
	w_sie(r_sie() | SIE_SEIE | SIE_STIE | SIE_SSIE);	//enable interrupts

	// configure Physical Memory Protection to give supervisor mode
	// access to all of physical memory.
	w_pmpaddr0(0x3fffffffffffffull);
	w_pmpcfg0(0xf);

	// ask for clock interrupts
	// timerinit();

	// keep each CPU's hardid in its tp register.
	int id = r_mhartid();
	w_tp(id);

	// switch to supervisor mode and jump to main().
	asm volatile("mret");
}
