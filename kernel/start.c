char stack0[4096*8];

void uartputc_temp(char c);

void start() {
	uartputc_temp('w');
	while (1)
		;
}
