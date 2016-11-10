#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 0

// prototypes
int makeargv(char * s, char * delimiters, char *** argvp);
int run(char * cmd, int input, int first, int last);
int command(int input, int first, int last);

//global
char ** argv;
pid_t pid;

int main() {
  int input = 0;
  char * cmd = "ls -lt";
  input = run(cmd, input, 1, 0);  
  char * cmd2 = "grep a";
  input = run(cmd2, input, 0, 1);

  for(int i = 0; i < 2; i++) {
    wait(NULL);
  }
}

int run(char * cmd, int input, int first, int last) {
  makeargv(cmd, "\t \n", &argv);
  if(argv[0] != NULL) {
    return command(input, first, last);
  }
  return 0;
}

int command(int input, int first, int last) {
  int pipes[2];
  pipe(pipes);

  pid = fork();

  if(pid == 0) {
    if(first == 1 && last == 0 && input == 0) { // pipe on right
      dup2(pipes[WRITE], STDOUT_FILENO);
    } else if (first == 0 && last == 0 && input != 0) { // pipes on both sides
      dup2(input, STDIN_FILENO);
      dup2(pipes[WRITE], STDOUT_FILENO);
    } else { // pipe on left
      dup2(input, STDIN_FILENO);
    }
    
    if(execvp(argv[0], argv) == -1) {
      exit(EXIT_FAILURE);
    }
  }

  if(input != 0)
    close(input);

  close(pipes[WRITE]);

  if(last == 1) {
    close(pipes[READ]);
  }

  return pipes[READ];
}

