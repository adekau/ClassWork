#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>
#include <libemb/shell/shell.h>

int shell_cmd_help(shell_cmd_args *args);
int shell_cmd_start(shell_cmd_args *args);

char allowCount	 = 0b00000000;
char restartGame = 1;
short hasPrime   = 0;
short hasDiv10   = 0;
short hasPwr2	 = 0;
short attempts	 = 0;
char step 	 = 0;
char stepCount   = 0;
short count  	 = 1;
// const
const char ISPRIME    = 0b00000001;
const char ISDIV2     = 0b00000010;
const char ISPOWR2    = 0b00000100;
const short POWERS[10]  = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
const short PRIMES[168]  = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
const char P2NUMBER[] = {0b01111110, 0b00001100, 0b10110110, 0b10011110,0b11001100,0b11011010, 0b11111010, 0b00001110, 0b11111110, 0b11001110};

shell_cmds my_shell_cmds = {
  .count = 2,
  .cmds  = {
    {
      .cmd  = "help",
      .desc = "list available commands",
      .func = shell_cmd_help
    },
    {
      .cmd  = "start",
      .desc = "Start the game.",
      .func = shell_cmd_start
    }
  }
};

/******
 *
 *    CALLBACK HANDLERS
 *
 ******/
int shell_cmd_help(shell_cmd_args *args)
{
  int k;

  for(k = 0; k < my_shell_cmds.count; k++) {
    cio_printf("%s: %s\n\r", my_shell_cmds.cmds[k].cmd, my_shell_cmds.cmds[k].desc);
  }

  return 0;
}

int shell_cmd_start(shell_cmd_args *args)
{
  int k;

  cio_print((char *)"Started game.\n\r");

  allowCount = 1;
  count = 1;
  hasPrime = 0;
  hasPwr2 = 0;
  hasDiv10 = 0;
  attempts = 0;
  restartGame = 0;
  return 0;
}

int shell_process(char *cmd_line)
{
  return shell_process_cmds(&my_shell_cmds, cmd_line);
}

int main(void) { 
	WDTCTL 	= WDTHOLD | WDTPW;
	BCSCTL1	= CALBC1_1MHZ;
	DCOCTL 	= CALDCO_1MHZ;
	BCSCTL3	= LFXT1S_2;
	P1DIR 	= BIT0 | BIT4 | BIT5 | BIT6 | BIT7;
	P1OUT	= 0b00000000;
	P2DIR	= 0b11111110;
	P2OUT   = 0b00000000;
	P2SEL 	= 0;
	P2SEL2	= 0;
	serial_init(9600);
	_BIS_SR(GIE);
	// Timer 0
	TA0CTL	 = TASSEL_2 | MC_1 | ID_0;
	TA0CCTL0 = CCIE;
	TA0CCR0  = 1000;
	// Timer 1
	TA1CTL	 = TASSEL_2 | MC_1 | ID_3;
	TA1CCTL0 = CCIE;
	TA1CCR0  = 60000;
	// Pushbutton interrupt
	P1REN	 = BIT3;
	P1OUT   |= BIT3;
	P1IE    |= BIT3;
	P1IES   |= BIT3;
	P1IFG   &= ~BIT3;
	
	cio_printf("Type a command. Type 'help' for available commands.\n\r");
	//Program loop
	for (;;) {
	  if(!allowCount) {
	    int j = 0;                              // Char array counter
	    char cmd_line[90] = {0};                // Init empty array

	    cio_print((char *) "$ ");               // Display prompt
	    char c = cio_getc();                    // Wait for a character
	    while(c != '\r') {                      // until return sent then ...
	      if(c == 0x08) {                       //  was it the delete key?
	        if(j != 0) {                        //  cursor NOT at start?
	          cmd_line[--j] = 0;                //  delete key logic
	          cio_printc(0x08); cio_printc(' '); cio_printc(0x08);
	        }
	      } else {                              // otherwise ...
	        cmd_line[j++] = c; cio_printc(c);   //  echo received char
	      }
	      c = cio_getc();                       // Wait for another
	    }

	    cio_print((char *) "\n\n\r");           // Delimit command result

	    switch(shell_process(cmd_line))         // Execute specified shell command
	    {                                       // and handle any errors
	      case SHELL_PROCESS_ERR_CMD_UNKN:
	        cio_print((char *) "ERROR, unknown command given\n\r");
	        break;
	      case SHELL_PROCESS_ERR_ARGS_LEN:
	        cio_print((char *) "ERROR, an arguement is too lengthy\n\r");
	        break;
	      case SHELL_PROCESS_ERR_ARGS_MAX:
	        cio_print((char *) "ERROR, too many arguements given\n\r");
	        break;
	      default:
	        break;
	    }

	    cio_print((char *) "\n");               // Delimit Result
	    }else{
		break;
		count++;
		if(count > 999) count = 1;
		__delay_cycles(300000);
 	    }
	  }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void) {
	P2OUT = 0;
	if(step == 0) {
		P1OUT = BIT3 | BIT5 | BIT7;
		P2OUT = 0b00000000 | P2NUMBER[count % 10];
	}else if(step == 1){
		P1OUT = BIT5 | BIT6 | BIT3;
		P2OUT = 0b00000000 | P2NUMBER[(count / 10) % 10];
	}else if(step == 2){
		P1OUT = BIT3 | BIT7 | BIT6;
		P2OUT = 0b00000000 | P2NUMBER[count / 100];
	}
	step++;
	if(step > 2) step = 0;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer0_A1 (void) {
	/*if(allowCount == 1) {
		count++;
		if(count > 999) count = 1;	
	}*/
}

#pragma vector=PORT1_VECTOR
__interrupt void Port1_1(void) {
	if(restartGame == 1) {
		count = 0; 
		allowCount = 1;
		attempts = 0;
		restartGame = 0;
	}
	P1OUT |= BIT5 | BIT6 | BIT7;
	allowCount ^= BIT0;
	short isPrime = 0;
	short isPwr2  = 0;
	short isDiv10 = 0;

	// first check if it's prime
	int i;
	for(i = 0; i < 168; i++) {
		if(PRIMES[i] == count) {
			isPrime = 1;
		}
	}
	// next check if it's a power of 2
	for(i = 0; i < 10; i++) {
		if(POWERS[i] == count) {
			isPwr2 = 1;
		}
	}
	// next check if it's divisible by 10
	if((count % 10) == 0) {
		isDiv10 = 1;
	}

	// Win condition checking. Only allow 1 per PB press.
	short alreadySetOne = 0; // used to keep track if one has already been set.

	if(isPrime && !hasPrime && !alreadySetOne && !allowCount && attempts < 3) {
		hasPrime = 1;
		alreadySetOne = 1;
		P1OUT |= BIT0;
		allowCount = 1;
		attempts++;
	}
	if(isPwr2 && !hasPwr2 && !alreadySetOne && !allowCount && attempts < 3 ) {
		hasPwr2 = 1;
		alreadySetOne = 1;
		P1OUT |= BIT4;
		allowCount = 1;
		attempts++;
	}
	if(isDiv10 && !hasDiv10 && !alreadySetOne && !allowCount && attempts < 3) {
		hasDiv10 = 1;
		alreadySetOne = 1;
		P1OUT |= BIT0 | BIT4;
		allowCount = 1;
		attempts++;
	}
	if(!isPrime && !isPwr2 && !isDiv10 && !alreadySetOne && !allowCount && attempts < 3) {
		attempts++;
		allowCount = 1;
	}
	if(isPrime && hasPrime && !alreadySetOne && !allowCount && attempts < 3) {
		attempts++;
		allowCount = 1;
	}
	if(isPwr2 && hasPwr2 && !alreadySetOne && !allowCount && attempts < 3) {
		attempts++;
		allowCount = 1;
	}
	if(isDiv10 && hasDiv10 && !alreadySetOne && !allowCount && attempts < 3) {
		attempts++;
		allowCount = 1;
	}
	if((hasPrime && hasPwr2 && hasDiv10) && attempts >= 2) {
		count = 200;
		allowCount = 0;
		attempts = 0;
		hasPrime = 0; hasPwr2 = 0; hasDiv10 = 0;
		restartGame = 1;		
	}
	if((!hasPrime || !hasPwr2 || !hasDiv10) && attempts == 3) {
		count = 404;
		allowCount = 0;
		attempts = 0;
		hasPrime = 0; hasPwr2 = 0; hasDiv10 = 0;
		restartGame = 1;
	}

	while(!(BIT3 & P1IN)) {
		__delay_cycles(32000);
	}
	P1IFG &= ~BIT3;
}
