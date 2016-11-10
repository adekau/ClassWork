#include <msp430.h>

int main(void) {
	WDTCTL 	= WDTHOLD | WDTPW;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL	= CALDCO_1MHZ;

	// Going to need to redo these numbers because can't use P1.1,1.2,1.3 because they're used by UART,etc. look at manual.
	int number[10] 	= {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b1100111};
	int cathode[4]	= {0x0, BIT0, BIT1, BIT2};

	P1DIR = 0b01111111;
	P2DIR = 0b00000111;

	// Enable Cathode 1
	P2OUT = cathode[1];
	
	// Set Cathode to 5;
	P1OUT = number[1];
}
