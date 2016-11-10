#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P2DIR = BIT0;
	P2SEL |= BIT0;
	TA0CCR0 = 120;
	TA0CCTL1 = OUTMOD_4;
	TA0CTL = TASSEL_2 | MC_1 | ID_1;
	int i = 120;
	int inc = 1;
  	while (i < 1200) {
		i += inc;
		TA0CCR0 = i;
		__delay_cycles(2000);
		if(i == 1099) {
			inc = -1;
		}
		if(i == 120) {
			inc = 1;
		}
	}
	LPM1;
}
