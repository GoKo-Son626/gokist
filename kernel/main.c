
void uartinit();
void uartputs_temp(char* s);

void main() {
	uartinit();
	uartputs_temp("string\n");

	while (1)
		;
}
