#include "types.h"
#include "riscv.h"
#include "param.h"
#include "proc.h"
#include "defs.h"

struct cpu cpus[NCPU];

int cpuid()
{
	int id = r_tp(); //RISCV未提供直接读取当前CPU编号的函数
	return id;
}

struct cpu* mycpu()
{
	int id = cpuid();
	struct cpu* c = &cpus[id];
	return c;
}

