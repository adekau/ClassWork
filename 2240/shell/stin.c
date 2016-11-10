#include <stdio.h>
#include <unistd.h>

int main (void) {
  int pipes[2];
  pid_t pid;
  pipe(pipes);
  int input;

  pid = fork();

  if(pid == 0) {
    close(pipes[0]);
    dup2(pipes[1], 1);
    execlp("/bin/ls", "ls", (void *)0);
  }
  close(pipes[1]);
  // now read the input file descriptor
  char buf[1000];
  read(pipes[0], buf, 1000);
  printf("Here's what it (input) gave: %s\n", buf);

  // now try reading the outbut file descriptor
  char buf2[1000];
  read(pipes[1], buf2, 1000);
  printf("Here's what it (output) gave: %s\n", buf2);

  // Try writing to output and reading input
  char buf3[1000];
  write(pipes[1], "Hello world!", 12);
  read(pipes[0], buf3, 1000);
  printf("Here's what it (write/read) gave: %s\n", buf3);


 // How I thought it was supposed to work:
 
 /* write(pipes[1], "Misunderstanding", 16);
    dup2(pipes[1], STDIN_FILENO);
    char buf[1000];
    read(STDIN_FILENO, buf, 1000);
    // put the stdout into stdin then read stdin should print "Misunderstanding"
  */
}
