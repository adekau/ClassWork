#include <msp430.h>

int main(void) {
	WDTCTL 	= WDTHOLD | WDTPW;				// Watchdog control disable
	BCSCTL1 = CALBC1_1MHZ;					// Set the processor speed to 1 MHZ
	DCOCTL	= CALDCO_1MHZ; 					// Letter 'O' here, not numeric '0'.
	
	P1DIR = BIT6 | BIT0;						// Select the pin to use
	P1OUT = BIT6;						// Change the output (on(1)/off(0)) of the pins

	for(;;) {
		P1OUT ^= 0b01000001;
		__delay_cycles(25000);
	}
}
