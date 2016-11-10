#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define READ  0
#define WRITE 1
#define LINEMAX 8192

//Prototypes
char *readLine(void);
int   makeargv(char *s, char *delimiters, char ***argvp);
int   pipe_cmd(char **argv, int prev_stdin, int first, int last);

//Globals
pid_t pid;

int main() {
  printf("Enter a pipe command\n");
  printf("$>");
  int prev_stdin = 0;
  int first = 1;
  char **argv;
  char line[LINEMAX];
  fgets(line, LINEMAX, stdin);
  char * cmd = line;
  char * next = strchr(cmd, '|');
  while(next != NULL) {
    *next = '\0';
    makeargv(cmd, "\t \n", &argv);
    prev_stdin = pipe_cmd(argv, prev_stdin, first, 0);
    cmd = next + 1;
    while(isspace(*cmd)) cmd++;
    next = strchr(cmd, '|');
    first = 0;
  }
  prev_stdin = pipe_cmd(argv, prev_stdin, first, 1);
  /*int prev_stdin = 0;
  char *argv[10];
  argv[0] = "ls"; argv[1] = NULL;
  prev_stdin = pipe_cmd(argv, prev_stdin, 1, 0);
  argv[0] = "./add"; argv[1] = NULL;
  prev_stdin = pipe_cmd(argv, prev_stdin, 0, 0);
  argv[0] = "./add"; argv[1] = NULL;
  prev_stdin = pipe_cmd(argv, prev_stdin, 0, 0);
  argv[0] = "./add"; argv[1] = NULL;
  prev_stdin = pipe_cmd(argv, prev_stdin, 0, 0);
  argv[0] = "grep"; argv[1] = "e"; argv[2] = NULL;
  prev_stdin = pipe_cmd(argv, prev_stdin, 0, 1);*/


}

char *readLine(void) {
  char * line = NULL;
  size_t linecap = 0;
  if(getline(&line, &linecap, stdin) < 0) {
    printf("error"); exit(0);
  } 
  return line;
}

int pipe_cmd(char **argv, int prev_stdin, int first, int last) {
  int status;
  int pipes[2];
  pipe(pipes);
  pid = fork();

  if(pid == 0) {
    if(first == 1 && last == 0 && prev_stdin == 0) {
      close(pipes[READ]); // don't need to read anything on the first command..
      dup2(pipes[WRITE], STDOUT_FILENO); // only ned to write
    } else if (first == 0 && last == 0 && prev_stdin != 0) {
      dup2(prev_stdin, STDIN_FILENO);
      dup2(pipes[WRITE], STDOUT_FILENO);
    } else {
      close(pipes[WRITE]); // don't need to write anything on last command
      dup2(prev_stdin, STDIN_FILENO); // only need to read previous command's output..
    } 
    execvp(argv[0], argv); // exec the process.
  }

  if(prev_stdin != 0) close(prev_stdin); // Close the middle command stdin to return it
   
  close(pipes[WRITE]); // Close the pipe for writing (to prevent commands like more/grep/etc from hanging).

  if(last == 1) close(pipes[READ]); // if it's the last command, don't need to read anymore

  waitpid(pid, &status, 0); // wait for the child to finish execing to prevent zombies
  return pipes[READ]; // return the standard input that the next command will use.
}
