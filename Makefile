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

CFLAGS = -Wall -Werror -O0 \
         -fno-omit-frame-pointer -ggdb \
         -MD -mcmodel=medany \
         -ffreestanding -fno-common -nostdlib \
         -mno-relax \
         -fno-stack-protector -fno-pie -no-pie \
         -z max-page-size=4096
# CFLAGS：定义了C编译器的常用标志。
# -Wall: 开启几乎所有常用警告信息。
# -Werror: 将所有警告视为错误，强制开发者修复所有警告。
# -O0: 不进行任何优化，这对于调试非常有用，因为代码不会被重排。
# -fno-omit-frame-pointer: 确保GCC不省略帧指针，这对于调试时查看函数调用栈是必要的。
# -ggdb: 生成GDB调试器所需的调试信息，提供了更丰富的调试符号。
# -MD: 生成`.d`文件，其中包含源文件的依赖信息，用于后续的增量编译。
# -mcmodel=medany: 设置代码模型为“medany”（medium-any），适用于程序代码和数据可以分布在任意地址的场景，常用于裸机或小型OS。
# -ffreestanding: 告知编译器这是一个“独立”环境，它将不链接标准库（如libc）中的任何函数。
# -fno-common: 禁止使用 común 块（common blocks），确保未初始化的全局变量被放入BSS段。
# -nostdlib: 在链接时不链接标准的系统启动文件和库，适用于构建操作系统或引导程序。
# -mno-relax: 禁用链接器的“relax”优化，这在生成裸机代码时可能很重要，以确保指令的精确性。
# -fno-stack-protector: 禁用栈保护机制（stack smashing protector），在没有libc支持的裸机环境中通常禁用。
# -fno-pie: 禁用生成位置无关可执行文件（PIE）。
# -no-pie: 链接器选项，同-fno-pie，确保生成非位置无关的可执行文件。
# -z max-page-size=4096: 设置生成的可执行文件的最大页大小为4096字节，这与常见的内存管理单元(MMU)页大小匹配。

QEMU = qemu-system-riscv64 -machine virt \
       -bios none \
       -kernel kernel.elf \
       -m 128 \
       -smp 1 \
       -nographic
# QEMU: 定义了QEMU模拟器的基础命令和常用参数。
# qemu-system-riscv64: 调用QEMU模拟器，指定模拟RISC-V 64位系统。
# -machine virt: 指定模拟器的机器类型为 'virt'，这是一个常用的虚拟RISC-V平台。
# -bios none: 告诉QEMU不要加载任何BIOS固件，直接从-kernel指定的映像启动。
# -kernel kernel.elf: 指定要加载并运行的内核文件为 'kernel.elf'。
# -m 128: 为模拟的虚拟机分配128MB的内存。
# -smp 4: 配置模拟的虚拟机使用4个对称多处理器（CPU核心）。
# -nographic: 在没有图形界面的情况下运行QEMU，所有输出将通过命令行/终端显示。

kernel:
# kernel: 定义了名为 'kernel' 的目标。
# 默认情况下，当运行 'make' 命令时，会尝试构建第一个非`.PHONY`目标或第一个目标，此处通常是`kernel`。
	riscv64-unknown-elf-gcc $(CFLAGS) \
		kernel/entry.S \
		kernel/start.c \
		kernel/uart.c \
		kernel/main.c \
		-T kernel/kernel.ld \
		-o kernel.elf
# riscv64-unknown-elf-gcc: 调用RISC-V 64位交叉编译器。
# $(CFLAGS): 展开并使用上面定义的CFLAGS变量中的所有编译标志。
# kernel/entry.S: 指定内核的汇编语言入口点文件。
# kernel/start.c: 指定内核的C语言启动文件。
# kernel/uart.c: 指定内核的C语言UART通信文件。
# kernel/main.c: 指定内核的主要C语言源文件。
# -T kernel/kernel.ld: 指定链接器脚本文件 'kernel.ld'，该文件定义了程序的内存布局。
# -o kernel.elf: 指定输出的可执行文件名为 'kernel.elf'。

qemu: kernel
# qemu: 定义了名为 'qemu' 的目标。
# kernel: 'qemu' 目标依赖于 'kernel' 目标。这意味着在执行 'qemu' 命令之前，
# Makefile会首先确保 'kernel' 目标（即 kernel.elf 文件）已经被成功构建。
	$(QEMU)
# $(QEMU): 展开并执行上面定义的QEMU变量中的所有命令和参数，启动模拟器。

gdb: kernel
# gdb: 定义了名为 'gdb' 的目标。
# kernel: 'gdb' 目标依赖于 'kernel' 目标，确保在调试前内核已编译。
	$(QEMU) -s -S &
# $(QEMU): 展开并执行QEMU变量中的基础命令和参数。
# -s: 启动GDB服务器，在默认的1234端口等待GDB客户端连接。
# -S: 在启动时冻结CPU，等待GDB连接并发出“continue”命令。
# &: 将QEMU命令放入后台运行，这样make命令可以继续执行GDB命令。
	gdb-multiarch -q -x gdbinit
# gdb-multiarch: 启动GDB调试器，支持多架构调试（用于RISC-V）。
# -q: 静默模式，不打印GDB的启动信息。
# -x gdbinit: 从 'gdbinit' 文件中读取并执行GDB命令，通常包含连接QEMU的命令和符号加载等。

clean:
# clean: 定义了名为 'clean' 的目标。
	rm -rf	kernel.elf \
		kernel.d
# rm -rf: 强制性地递归删除文件和目录。
# kernel.elf: 要删除的编译后的内核可执行文件。
# kernel.d: 要删除的由-MD选项生成的依赖关系文件。
