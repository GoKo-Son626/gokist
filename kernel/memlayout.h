#ifndef __MEMLAYOUT__
#define __MEMLAYOUT__

#define UART0 0x10000000L

// core local interruptor (CLINT), which contains the timer.
#define CLINT 0x2000000L
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 + 8*(hartid))
#define CLINT_MTIME (CLINT + 0xBFF8) // cycles since boot.

#endif // __MEMLAYOUT__


