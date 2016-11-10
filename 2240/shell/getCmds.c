#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
  int i;
  char line[1000];
  fgets(line, 1000, stdin);
  char * cmd = line;
  char * next = strchr(cmd, '|');
  while(next != NULL) {
    *next = '\0';
    printf("command %d: %s\n", ++i, cmd);
    cmd = next + 1;
    while(isspace(*cmd)) cmd++;
    next = strchr(cmd, '|');
  }
  printf("command %d: %s\n", ++i, cmd);
}
