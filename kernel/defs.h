#ifndef __DEFS_H__
#define __DEFS_H__

#include "types.h"

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

#endif // !__DEFS_H__
