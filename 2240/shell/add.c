#include <stdio.h>
#include <unistd.h>

int main(void) {
  char buf[1000];
  read(STDIN_FILENO, buf, 1000);
  printf("Input recieved: %s\n", buf);
  return 0;
}
