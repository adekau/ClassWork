#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>

int getRecords(int fd, char * line) {
  int len;
  int i = 0;
  int z = 0;
  int numRecords = 0;

  len = read(fd, line, 1000);
  if(len < 0) {
    err_sys("Failed to read countries file.\n");
  }

  i = len - 1;
  while(line[i--] != '\n');
  line[i] = '\0';

  lseek(fd, -(len-i)+1, SEEK_CUR);

  while(line[z++] != '\0') {
    if(line[z] == '\n') {
      numRecords++;
    } 
  }
  numRecords++;

  if(len == 1) {
    return 0;
  }else{ 
    return numRecords; 
  }
}
