#define DIV_INTERVAL	300
#define STEP_INTERVAL	5
#define LOWER_LIMIT	10
#define UPPER_LIMIT	1020
#define DOWN		0
#define UP		1

#include <msp430.h>

int main(void) {
	WDTCTL 	 = WDTPW | WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;	// Set the processor speed to 1 MHZ
	DCOCTL	= CALDCO_1MHZ; 
	P1DIR   |= BIT2;
	P1SEL   |= BIT2;
	TA0CCR0  = 1024-1;
	TA0CCTL1 = OUTMOD_7;
	TA0CCR1  = 10;
	TA0CTL   = TASSEL_2 | MC_1 | TAIE;
	TA0CCR1 &= ~CCIFG;

	__bis_SR_register(LPM0_bits + GIE);
}

#pragma vector=TIMERA0_VECTOR;
void __interrupt Timer0(void) {
	static int direction = DOWN;
	static int divider   = 0;

	if(divider == DIV_INTERVAL) {
		if(TA0CCR1 > LOWER_LIMIT && direction == DOWN) {
			TA0CCR1 -= STEP_INTERVAL;
		}else if(TA0CCR1 < UPPER_LIMIT && direction == UP) {
			TA0CCR1 += STEP_INTERVAL;
		}

		if(TA0CCR1 == LOWER_LIMIT) {
			direction = UP;
		}
		if(TA0CCR1 == UPPER_LIMIT) {
			direction = DOWN;
		}
		divider = 0;
	}else{
		divider++;
	}
}
