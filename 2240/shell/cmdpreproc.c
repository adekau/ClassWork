#include "shell.h"
#include "apue.h"

command commands[MAXCOMMANDS];

int main(void) {
  unsigned int i;
  char * cmdline;
  char * next; // pointer to '|' characters.

  //Main loop.
  while(1) {
    cmdline = getUserInput();
    while(isspace(*cmdline)) cmdline++; // remove spaces in the beginning
    
    i = 0;
    // Now separate commands
    next = strchr(cmdline, '|');
    if(next == NULL) { 
      // Just run a command.

      command single;
      char *redirFindRight = strchr(cmdline, '>');
      char *redirFindLeft  = strchr(cmdline, '<');

      if(redirFindRight == NULL && redirFindLeft == NULL) {
        single.commandType = CMDTYPE_SINGLE_CMD;
      }else if(redirFindRight != NULL && redirFindLeft == NULL) {
        single.commandType = CMDTYPE_REDIRECT_OUT;
      }else if(redirFindRight == NULL && redirFindLeft != NULL) {
        single.commandType = CMDTYPE_REDIRECT_IN;
      }else {
        single.commandType = CMDTYPE_REDIRECT_BOTH;
      }
      single.cmd         = cmdline;
      commands[i++] = single;
    }else{ // If there is a pipe symbol.
      while(next != NULL) {
        *next = '\0';
        setRedirectCommandType(cmdline, i);
        commands[i++].cmd = cmdline;
        
        cmdline = next + 1;
        while(isspace(*cmdline)) cmdline++;
        next = strchr(cmdline, '|');
      }
      setRedirectCommandType(cmdline, i);
      commands[i++].cmd = cmdline;
    }
    processCommands(i);
  }
}

/*
      setRedirectCommandType
        char * cmdline   the command to be inspected
        unsigned int i   the current position in the commands array
        -
        this function searches a command for a > or a < symbol and sets the
        command type to the correct command type.
*/
void setRedirectCommandType(char * cmdline, unsigned int i) {
  //placeholder function
  char *redirFindRight = strchr(cmdline, '>');
  char *redirFindLeft  = strchr(cmdline, '<');

  if(redirFindRight == NULL && redirFindLeft == NULL) {
    commands[i].commandType = CMDTYPE_PIPE;
  }else if(redirFindRight != NULL && redirFindLeft == NULL) {
    commands[i].commandType = CMDTYPE_REDIRECT_OUT;
  }else if(redirFindRight == NULL && redirFindLeft != NULL) {
    commands[i].commandType = CMDTYPE_REDIRECT_IN;
  }else {
    commands[i].commandType = CMDTYPE_REDIRECT_BOTH;
  }
}

/*
      processCommands
        unsigned int i   the current position in the commands array
        -
        this function iterates through the commands array and executes
        the command in the correct fashion according to the command type.
*/
void processCommands(unsigned int i) {
  int prev_stdin = 0;
  int first = 1;
  int last  = 0;
  char * filename;
  char ** argv;
  int z;
  for(z = 0; z < i; z++) {
    switch(commands[z].commandType) {
      // HANDLE SINGLE COMMANDS
      case CMDTYPE_SINGLE_CMD:
        execCommand(commands[z].cmd);
        break;
      // HANDLE PIPES
      case CMDTYPE_PIPE:
        makeargv(commands[z].cmd, "\t \n", &argv);
        if(z == (i - 1)) last = 1;
        prev_stdin = pipe_cmd(argv, prev_stdin, first, last);
        first = 0;
        break;
      // HANDLE < > PIPES
      case CMDTYPE_REDIRECT_BOTH:
        printf("Not handling this right now.\n");
        break;
      // HANDLE INPUT REDIRECTS
      case CMDTYPE_REDIRECT_IN:
        filename = strchr(commands[z].cmd, '<');
        *filename = '\0';
        filename++;
        while(isspace(*filename)) filename++;
        if(filename[strlen(filename) - 1] == 10) {
        filename[strlen(filename) - 1] = '\0';
        }
        makeargv(commands[z].cmd, "\t \n", &argv);
        if(z == (i - 1)) last = 1;
        prev_stdin = redirect(REDIRECT_STDIN, prev_stdin, argv, filename);
        first = 0;
        break;
      // HANDLE OUTPUT REDIRECTS.
      case CMDTYPE_REDIRECT_OUT:
        filename = strchr(commands[z].cmd, '>');
        *filename = '\0';
        filename++;
        while(isspace(*filename)) filename++;
        if(filename[strlen(filename) - 1] == 10) {
        filename[strlen(filename) - 1] = '\0';
        }
        makeargv(commands[z].cmd, "\t \n", &argv);
        if(z == (i - 1)) last = 1;
        prev_stdin = redirect(REDIRECT_STDOUT, prev_stdin, argv, filename);
        first = 0;
        break;
      default:
        printf("Default.. how??\n");
        break;
    }
  }
}

