#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>
#include <libemb/shell/shell.h>

/******
 *
 *    PROTOTYPES
 *
 ******/
int shell_cmd_help(shell_cmd_args *args);
int shell_cmd_argt(shell_cmd_args *args);

/******
 *
 *    SHELL COMMANDS STRUCT
 *
 ******/
shell_cmds my_shell_cmds = {
  .count = 2,
  .cmds  = {
    {
      .cmd  = "help",
      .desc = "list available commands",
      .func = shell_cmd_help
    },
    {
      .cmd  = "args",
      .desc = "print back given arguments",
      .func = shell_cmd_argt
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

int shell_cmd_argt(shell_cmd_args *args)
{
  int k;

  cio_print((char *)"args given:\n\r");

  for(k = 0; k < args->count; k++) {
    cio_printf(" - %s\n\r", args->args[k].val);
  }

  return 0;
}

int shell_process(char *cmd_line)
{
  return shell_process_cmds(&my_shell_cmds, cmd_line);
}

/******
 *
 *    INITIALIZATION
 *
 ******/
int main(void)
{
  /* CLOCKS *********************************/
  WDTCTL   = WDTPW | WDTHOLD;               // Disable Watchdog
  BCSCTL1  = CALBC1_1MHZ;                   // Run @ 1MHz
  DCOCTL   = CALDCO_1MHZ;
  BCSCTL3  = LFXT1S_2;                      // Source VLO for ACLK
  P2SEL   &= ~(BIT6 | BIT7);                // P2.6 and P2.7 as Outputs

  serial_init(9600);                        // Initialize Serial Comms
  _BIS_SR(GIE);                             // Enable Interrupts
  cio_printf("Waiting for command. 1 for help, 2 for argt\n");
  char command = cio_getc();
  cio_printf("Debug: command: %i\n", (int) command);
  char *cmd_line = 0;
  switch(command) {
	case 49:
	  cmd_line = "help";
	break;
	case 50:
	  cmd_line = "help"; 
	break;
	default:
	//
	break;
  }	
  int s = shell_process(cmd_line);
  cio_printf("Debug: s: %i\n", s);
/******
 *
 *    PROGRAM LOOP
 *
 ******/
  for (;;) {
		
  }

  return 0;
}

/******
 *
 *    INTERRUPTS
 *
 ******/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
	
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer0_A1_ISR (void)
{
	
}

#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR (void)
{
	
}

