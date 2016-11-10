#include <msp430.h>

int main(void) {
	WDTCTL 	= WDTHOLD | WDTPW;				// Watchdog control disable
	BCSCTL1 = CALBC1_1MHZ;					// Set the processor speed to 1 MHZ
	DCOCTL	= CALDCO_1MHZ; 					// Letter 'O' here, not numeric '0'.

	P1REN = BIT3;
	P1DIR = BIT6 | BIT0;					// Select the pin to use
	P1OUT |= BIT3;						// Change the output (on(1)/off(0)) of the pins
	P1IE  |= BIT3;
	P1IES |= BIT3;
	P1IFG &= ~BIT3;
	P1OUT ^= BIT0;

	_BIS_SR(LPM4_bits | GIE);

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	//P1OUT ^= ~BIT6;
	//P1OUT |= ~BIT0;
	P1OUT ^= 0b01000001;
	while(!(BIT3 & P1IN)) {}
	__delay_cycles(32000);
	P1IFG &= ~BIT3;
}
