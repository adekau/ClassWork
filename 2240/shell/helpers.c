#include "shell.h"
#include "apue.h"

pid_t pid;

char *getUserInput(void) {
  char * user = malloc(100);
  getlogin_r(user, 100); 
  write(STDOUT_FILENO, user, strlen(user));
  write(STDOUT_FILENO, " $>", 3);
  free(user);
  char * line = malloc(LINEMAX);
  fgets(line, LINEMAX, stdin);
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

void execCommand(char * cmd) {
  char ** argv;
  int status;
  makeargv(cmd, "\t \n", &argv);
  pid = fork();
  if(pid == 0) {
    if(execvp(argv[0], argv) == -1) {
      err_sys("Error executing command ");
    } 
  }else if(pid < 0) {
    err_sys("Error creating child process ");
  } else {
    waitpid(pid, &status, 0); // wait for the child to finish execing to prevent zombies.
  }
}

int redirect(int redirect_type, int prev_stdin, char ** argv, char * filename) {
  int returnfd;
  int status;
  fflush(0);
  int fd0;
  pid = fork();
  if(pid < 0) err_sys("Error creating child process.");
  if(pid == 0) {
  	if(redirect_type == REDIRECT_STDOUT) {
  	  fd0 = creat(filename, 0644);
  	  dup2(prev_stdin, STDIN_FILENO);
  	  dup2(fd0, STDOUT_FILENO);
  	  close(fd0);
  	} else {
  	  int fd1 = open(filename, O_RDONLY);
  	  dup2(fd1, STDIN_FILENO);
  	  close(fd1);
  	}

  	if(execvp(argv[0], argv) == -1) err_sys("Error executing command ");
  }
  close(fd0);
  returnfd = open(filename, O_RDONLY);
  waitpid(pid, &status, 0);
  return returnfd;
}






