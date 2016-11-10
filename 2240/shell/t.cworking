#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ  0
#define WRITE 1

int main() {
  int pipes[2];
  int status;
  pid_t pid;
  pipe(pipes);

  pid = fork();

  if(pid == 0) {
    dup2(pipes[WRITE], STDOUT_FILENO);
    execlp("/bin/ls", "ls", (void *)0);
  }
  waitpid(pid, &status, 0);

  pid = fork();
  
  if(pid == 0) {
    dup2(pipes[READ], STDIN_FILENO);
    dup2(pipes[WRITE], STDOUT_FILENO);
    execlp("./add", "add", 0);
  }
  waitpid(pid, &status, 0);

  pid = fork();
  
  if(pid == 0) {
    dup2(pipes[READ], STDIN_FILENO);
    dup2(pipes[WRITE], STDOUT_FILENO);
    execlp("./add", "add", 0);
  }
  waitpid(pid, &status, 0);

  pid = fork();

  if(pid == 0) {
    close(pipes[WRITE]);
    dup2(pipes[READ], STDIN_FILENO);
    char *argv[10];
    argv[0] = "grep"; argv[1] = "a"; argv[2] = NULL;
    execvp("grep", argv);
  }

  close(pipes[READ]);
  close(pipes[WRITE]);

  waitpid(pid, &status, 0);
  printf("Done!\n");
  return 0;
}
