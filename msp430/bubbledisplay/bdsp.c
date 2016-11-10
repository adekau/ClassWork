#include <msp430.h>

int main(void) {
	WDTCTL	= WDTHOLD | WDTPW;
	BCSCTL1	= CALBC1_1MHZ;
	DCOCTL	= CALDCO_1MHZ;

	P1DIR = BIT0 | BIT1 | BIT2;
	P1OUT = BIT0 | BIT1 | BIT2;

	return 0;
}
