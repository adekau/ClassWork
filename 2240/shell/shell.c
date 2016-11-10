#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "apue.h"

#define PIPE_READ  0
#define PIPE_WRITE 0

// Prototypes
void    shell_loop(void);
char *  shell_readLine();
int     shell_exec(char ** args);
int     makeargv(char * s, char * delimiters, char *** argvp);

// Globals
char user[100];
int numargs;

// Main function
int main() {
  // Main shell loop
  getlogin_r(user, 100); 
  char * msg = "Alex Dekau's shell for CS2240.\n";
  write(STDOUT_FILENO, msg, strlen(msg));
  shell_loop();
}

void shell_loop(void) {
  char *  line;
  char ** args;
  int     status;

  do {
    printf("%s $> ", user);
    line = shell_readLine();
    //printf("%s\n", line);
    numargs = makeargv(line, "\t \n", &args);
    //printf("Numargs: %d\n", numargs);
    status = shell_exec(args);

    free(line);
    free(args);
  } while (status);
}

char * shell_readLine() {
  char * line = NULL;
  size_t linecap = 0;
  if((getline(&line, &linecap, stdin)) < 0) {
    err_sys("Get line error.");
  }
  return line;
}

int shell_exec(char ** args) {
  // test for if the user typed "exit".
  if(numargs <= 2 && numargs > 0 && (strcmp(args[0], "exit") == 0)) {
    exit(0);
  }
  
  pid_t pid;
  pid_t wpid;
  int   status;

  pid = fork();

  if(pid == 0) { // child process
    if(execvp(args[0], args) == -1) {
      err_sys("Error executing command.");
    }
  } else if(pid < 0) {
    err_sys("Error forking.");
  } else { // parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}
