#include <stdio.h>
#include <unistd.h>

int main(void) {
  pid_t pid;

  pid = fork();
  if(pid == 0) {
    printf("Child process:\n");
    execl("/bin/ls","ls", 0); 
  }else{
    printf("Parent Process:\n");
    execl("ls","ls", 0);
  }
}
