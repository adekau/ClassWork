#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ  0
#define WRITE 1

int exec_cmd(char ** args, int input, int first, int last);

int main(void) {
  char * args = malloc(10);
  int input = 0;
  args[0] = 'l';
  args[1] = 's';
  args[2] = '\0';
  input = exec_cmd(&args, input, 1, 0);
  args[0] = 'a';
  args[1] = 'd';
  args[2] = 'd';
  args[3] = '\0';
  input = exec_cmd(&args, input, 0, 1);
  return 0;
}

int exec_cmd(char ** args, int input, int first, int last) {
  int fd[2];
  pid_t pid;
  pipe(fd);
  pid = fork();

  if(pid < 0) {
    //failed
    printf("Failed on fork");
  } else if (pid == 0) { // child
    if(first && !last && !input) {
      dup2(fd[WRITE], STDOUT_FILENO);
    } else if (!first && !last && input != 0) {
      dup2(input, STDIN_FILENO);
      dup2(fd[WRITE], STDOUT_FILENO);
    } else {
      dup2(input, STDIN_FILENO);
    }

    if((execvp(args[0], args)) == -1) {
      _exit(EXIT_FAILURE);
    }
  } else { // parent
    // do nothing with parent
  }

  if(input != 0) {
    close(input);
  }

  close(fd[WRITE]);
  if(last)
    close(fd[READ]);

  return fd[READ];
  
}
