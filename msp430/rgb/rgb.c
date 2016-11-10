#include <msp430.h>

void rgb(char RED, char GREEN, char BLUE){
	P1OUT = RED << 1 | GREEN << 2 | BLUE << 3;
}

int main(void) {
	WDTCTL	= WDTHOLD | WDTPW;
	BCSCTL1	= CALBC1_1MHZ;
	DCOCTL	= CALDCO_1MHZ;

	P1DIR	= 0b00001110;
	P1OUT	= 0b00001110;
	
	int red 	= 0;
	int blue 	= 0;
	int green 	= 0;
	for(;;) {
		rgb(red++, blue++, green++);
		__delay_cycles(1000000);
	}

	return 0;

}
