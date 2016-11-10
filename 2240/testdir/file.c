#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
  int newfd = open("NewFile", O_CREAT, 0744);
  newfd = dup2(newfd, 1);
  lseek(2,1000,SEEK_CUR);
  write(2, "OUT", 3);
  close(newfd);
}
