# 本Makefile定义了用于构建和运行一个RISC-V架构的操作系统/裸机程序（内核）的自动化规则。
# 它的主要功能包括：
# 1. 编译和链接：将RISC-V汇编和C语言源代码编译成一个可执行的RISC-V ELF内核文件。
# 2. 模拟运行：使用QEMU模拟器加载并运行编译好的内核。
# 3. 清理：提供一个方便的命令来删除编译过程中生成的中间文件和最终的内核文件。

.PHONY: kernel clean qemu
# .PHONY: 声明 'kernel', 'clean', 'qemu' 为伪目标（phony targets）。
# 伪目标不对应任何实际文件，它们总是被执行，即使同名文件存在且目标依赖项已是最新。
# 这可以防止与同名文件冲突，并确保每次执行这些目标时都运行其指定的命令。

CFLAGS = -Wall -Werror -O0 \
# CFLAGS：定义了C编译器的常用标志。
# -Wall: 开启几乎所有常用警告信息。
# -Werror: 将所有警告视为错误，强制开发者修复所有警告。
# -O0: 不进行任何优化，这对于调试非常有用，因为代码不会被重排。
# \: 续行符，表示当前行与下一行是同一逻辑行。
	-fno-omit-frame-pointer -ggdb \
# -fno-omit-frame-pointer: 确保GCC不省略帧指针，这对于调试时查看函数调用栈是必要的。
# -ggdb: 生成GDB调试器所需的调试信息，提供了更丰富的调试符号。
	-MD -mcmodel=medany \
# -MD: 生成`.d`文件，其中包含源文件的依赖信息，用于后续的增量编译。
# -mcmodel=medany: 设置代码模型为“medany”（medium-any），适用于程序代码和数据可以分布在任意地址的场景，常用于裸机或小型OS。
	-ffreestanding -fno-common -nostdlib \
# -ffreestanding: 告知编译器这是一个“独立”环境，它将不链接标准库（如libc）中的任何函数。
# -fno-common: 禁止使用 común 块（common blocks），确保未初始化的全局变量被放入BSS段。
# -nostdlib: 在链接时不链接标准的系统启动文件和库，适用于构建操作系统或引导程序。
	-mno-relax \
# -mno-relax: 禁用链接器的“relax”优化，这在生成裸机代码时可能很重要，以确保指令的精确性。
	-fno-stack-protector -fno-pie -no-pie \
# -fno-stack-protector: 禁用栈保护机制（stack smashing protector），在没有libc支持的裸机环境中通常禁用。
# -fno-pie: 禁用生成位置无关可执行文件（PIE）。
# -no-pie: 链接器选项，同-fno-pie，确保生成非位置无关的可执行文件。
	-z max-page-size=4096 \
# -z max-page-size=4096: 设置生成的可执行文件的最大页大小为4096字节，这与常见的内存管理单元(MMU)页大小匹配。

kernel:
# kernel: 定义了名为 'kernel' 的目标。
# 默认情况下，当运行 'make' 命令时，会尝试构建第一个非`.PHONY`目标或第一个目标，此处通常是`kernel`。
	riscv64-unknown-elf-gcc $(CFLAGS) \
# riscv64-unknown-elf-gcc: 调用RISC-V 64位交叉编译器。
# $(CFLAGS): 展开并使用上面定义的CFLAGS变量中的所有编译标志。
# \: 续行符，命令过长时用于换行。
		kernel/entry.S \
# kernel/entry.S: 指定内核的汇编语言入口点文件。
		kernel/start.c \
# kernel/start.c: 指定内核的C语言启动文件。
		kernel/uart.c \
# kernel/uart.c: 指定内核的C语言UART通信文件。
		kernel/main.c \
# kernel/main.c: 指定内核的主要C语言源文件。
		-T kernel/kernel.ld \
# -T kernel/kernel.ld: 指定链接器脚本文件 'kernel.ld'，该文件定义了程序的内存布局。
		-o kernel.elf \
# -o kernel.elf: 指定输出的可执行文件名为 'kernel.elf'。

qemu: kernel
# qemu: 定义了名为 'qemu' 的目标。
# kernel: 'qemu' 目标依赖于 'kernel' 目标。这意味着在执行 'qemu' 命令之前，
# Makefile会首先确保 'kernel' 目标（即 kernel.elf 文件）已经被成功构建。
	qemu-system-riscv64 -machine virt \
# qemu-system-riscv64: 调用QEMU模拟器，指定模拟RISC-V 64位系统。
# -machine virt: 指定模拟器的机器类型为 'virt'，这是一个常用的虚拟RISC-V平台。
		-bios none \
# -bios none: 告诉QEMU不要加载任何BIOS固件，直接从-kernel指定的映像启动。
		-kernel kernel.elf \
# -kernel kernel.elf: 指定要加载并运行的内核文件为 'kernel.elf'。
		-m 128 \
# -m 128: 为模拟的虚拟机分配128MB的内存。
		-smp 4 \
# -smp 4: 配置模拟的虚拟机使用4个对称多处理器（CPU核心）。
		-nographic \
# -nographic: 在没有图形界面的情况下运行QEMU，所有输出将通过命令行/终端显示。

clean:
# clean: 定义了名为 'clean' 的目标。
	rm -rf	kernel.elf \
# rm -rf: 强制性地递归删除文件和目录。
# kernel.elf: 要删除的编译后的内核可执行文件。
		kernel.d
# kernel.d: 要删除的由-MD选项生成的依赖关系文件。
