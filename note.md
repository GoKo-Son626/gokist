riscv: trap: exception and interrupt
  exception(同步): syscall, /0, ISA...
  interrupt(异步): out-devices, disk, UART...: CPU停下处理中断
  diff: mcause的execption位决定
    1:interrupt
    2:exception

