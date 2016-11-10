#include <msp430.h>

int main(void) {
	WDTCTL 	= WDTHOLD | WDTPW;				// Watchdog control disable
	BCSCTL1 = CALBC1_1MHZ;					// Set the processor speed to 1 MHZ
	DCOCTL	= CALDCO_1MHZ; 					// Letter 'O' here, not numeric '0'.
	
	P1DIR	= 0x1;						// Select the pin to use
	P1OUT	= 0x1;						// Change the output (on(1)/off(0)) of the pins

	for(;;) {						//			
		P1OUT ^= 0x1;					// XOR the on/off output to turn it off if on, and reverse
		__delay_cycles(1000000);			// wait 1 second (1MHZ, so wait 100,000)
	}

	return 0;
}
