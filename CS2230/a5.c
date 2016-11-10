#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

unsigned short int Status();

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	short int count,retval;
	count = 0;

	serial_init(9600);
	while (1) {
		count+=5000;
		cio_printf("%i\n\r", count);
		retval = Status();
		cio_printf("%x\n\r", retval & 0x0003);
		__delay_cycles(500000);
	}	

	return 0;
}

