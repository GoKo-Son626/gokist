# Makefile功能和作用说明：
# ------------------------------------------------------------------------------------------------
# 本Makefile定义了用于构建、运行和调试一个RISC-V架构的操作系统/裸机程序（内核）的自动化规则。
# 它的主要功能包括：
# 1. 编译和链接：将RISC-V汇编和C语言源代码编译成一个可执行的RISC-V ELF内核文件。
# 2. 模拟运行：使用QEMU模拟器加载并运行编译好的内核。
# 3. 调试：提供与QEMU集成的GDB调试环境，方便对内核进行源代码级别的调试。
# 4. 清理：提供一个方便的命令来删除编译过程中生成的中间文件和最终的内核文件。
#
# 其目的是为了简化RISC-V嵌入式或操作系统开发的构建流程，提高开发效率，确保编译环境的一致性。
# ------------------------------------------------------------------------------------------------

.PHONY: kernel clean qemu gdb
# .PHONY: 声明 'kernel', 'clean', 'qemu', 'gdb' 为伪目标（phony targets）。
# 伪目标不对应任何实际文件，它们总是被执行，即使同名文件存在且目标依赖项已是最新。
# 这可以防止与同名文件冲突，并确保每次执行这些目标时都运行其指定的命令。

K=kernel
U=user

OBJS= \
      $(K)/entry.o \
      $(K)/start.o \
      $(K)/uart.o \
      $(K)/main.o \
      $(K)/kernelvec.o \
      $(K)/trap.o \
      $(K)/kalloc.o \
      $(K)/string.o \
      $(K)/printf.o \
      $(K)/proc.o \
      $(K)/spinlock.o \
      $(K)/vm.o \
      $(K)/plic.o

TOOLPREFIX = riscv64-unknown-elf-
CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)as
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump

QEMU = qemu-system-riscv64

CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2
CFLAGS += -MD
CFLAGS += -mcmodel=medany
# CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
CFLAGS += -fno-common -nostdlib
CFLAGS += -fno-builtin-strncpy -fno-builtin-strncmp -fno-builtin-strlen -fno-builtin-memset
CFLAGS += -fno-builtin-memmove -fno-builtin-memcmp -fno-builtin-log -fno-builtin-bzero
CFLAGS += -fno-builtin-strchr -fno-builtin-exit -fno-builtin-malloc -fno-builtin-putc
CFLAGS += -fno-builtin-free
CFLAGS += -fno-builtin-memcpy -Wno-main
CFLAGS += -fno-builtin-printf -fno-builtin-fprintf -fno-builtin-vprintf
CFLAGS += -I.
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)

LDFLAGS = -z max-page-size=4096

$K/kernel: $(OBJS) $K/kernel.ld
	$(LD) $(LDFLAGS) -T $K/kernel.ld -o $K/kernel $(OBJS) 
	$(OBJDUMP) -S $K/kernel > $K/kernel.asm
	$(OBJDUMP) -t $K/kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $K/kernel.sym

CPUS := 1

QEMUOPTS = -machine virt \
	-bios none \
	-kernel $(K)/kernel \
	-m 128 \
	-smp $(CPUS) \
	-nographic

qemu: $(K)/kernel
	@echo "*** Build success ***"
	$(QEMU) $(QEMUOPTS)

gdb: $(K)/kernel
	@echo "*** Build success ***"
	$(QEMU) $(QEMUOPTS) -s -S & \
		gdb-multiarch -q -x gdbinit

qemu-gdb: $(K)/kernel
	@echo "*** Build gdb success ***"
	$(QEMU) $(QEMUOPTS) -s -S

qemu-debug:
	gdb-multiarch -q -x gdbinit

clean:
	rm -rf kernel/kernel
	rm -rf kernel.d
	rm -rf */*.d
	rm -rf */*.o */*.asm */*.sym
