#include <msp430.h>

void main(void){
    WDTCTL    = WDTPW + WDTHOLD;           // Disable Watchdog
    BCSCTL1   = CALBC1_1MHZ;               // Run @ 1MHz
    DCOCTL    = CALDCO_1MHZ;

    P1DIR = BIT2;
    P1SEL = BIT2;
    
    int period = 4000;

    TA0CTL   = TASSEL_2 | MC_1 | ID_0;
    TA0CCTL1 = OUTMOD_7;
    TA0CCR0  = period;
    TA0CCR1  = 2000; // Red

    char ud=0;
    while(1){
       __delay_cycles(1000);
        
        if (TA0CCR1 >= period){
            ud = 1;
            __delay_cycles(2000);
        }
        if (TA0CCR1 <= 5){
            ud = 0;
        }

        if (ud==0){
            TA0CCR1 += 5;
        } else {
            TA0CCR1 -= 5;
        }
    }
}
