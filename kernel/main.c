
void uartinit();
void uartputs_temp(char* s);

void main() {
	uartinit();
	uartputs_temp("Hello world!\n");

	while (1)
		;
}
