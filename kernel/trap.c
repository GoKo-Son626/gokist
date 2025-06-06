#include "types.h"
#include "riscv.h"
#include "defs.h"


// void kernelvec();
// extern int devintr();
// trapinithart(void);


// void
// trapinit(void)
// {
// 	initlock(&ticklock, "time");
// }

#include <sys/types.h>
void
trapinithard(void)
{
  w_stvec((uint64)kernelvec);
}


// interrupts and exceptions from kernel code go here via kernelvec,
// on whatever the current kernel stack is.
void 
kerneltrap()
{
  int which_dev = 0;

}



