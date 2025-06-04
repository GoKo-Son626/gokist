#include "memlayout.h"

#define Reg(reg) ((volatile unsigned char*)(UART0 + reg))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

// the UART control registers.
// some have different meanings for
// read vs write.
// see http://byterunner.com/16550.html
#define RHR 0                 // receive holding register (for input bytes)
#define THR 0                 // transmit holding register (for output bytes)
#define IER 1                 // interrupt enable register
#define IER_RX_ENABLE (1<<0)
#define IER_TX_ENABLE (1<<1)
#define FCR 2                 // FIFO control register
#define FCR_FIFO_ENABLE (1<<0)
#define FCR_FIFO_CLEAR (3<<1) // clear the content of the two FIFOs
#define ISR 2                 // interrupt status register
#define LCR 3                 // line control register
#define LCR_EIGHT_BITS (3<<0)
#define LCR_BAUD_LATCH (1<<7) // special mode to set baud rate
#define LSR 5                 // line status register
#define LSR_RX_READY (1<<0)   // input is waiting to be read from RHR
#define LSR_TX_IDLE (1<<5)    // THR can accept another character to send

void uartinit()
{
// 1. close the interrupt
	WriteReg(IER, 0);
// 2. set the baud rate
	WriteReg(LCR, LCR_BAUD_LATCH);
	// LSB for baud rate of 38.4K.
	WriteReg(0, 0x03);
	// MSB for baud rate of 38.4K.
	WriteReg(1, 0x00);
// 3. set the bit width
	// leave set-baud mode,
	// and set word length to 8 bits, no parity.
	WriteReg(LCR, LCR_EIGHT_BITS);
// 4. clear the input and output queue
	// reset and enable FIFOs.
	WriteReg(FCR, FCR_FIFO_ENABLE | FCR_FIFO_CLEAR);
	// enable transmit and receive interrupts.
	WriteReg(IER, IER_TX_ENABLE | IER_RX_ENABLE);

	// initlock(&uart_tx_lock, "uart");
}

 void uartputc_temp(char c)
 {
	WriteReg(THR, c);
}

void uartputs_temp(char* s)
{
	while (*s) {
		uartputc_temp(*(s++));
	}
}
