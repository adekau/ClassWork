// Alex Dekau
// Assignment 2
// Program 1 (reads the actual file and returns a buffer)
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include "a2.h" // includes defines for buffer size, number of countries, and the cdirectory struct.

// This function reads in one entire buffer (BUFFER_SIZE) to memory then breaks cuts off
// any fragments with a null character and returns the number of records (countries) 
// the buffer contains.
int getRecords(int fd, char * line) {
  int len; // The number of bytes read in from the file.
  int i = 0; //The position in the buffer
  int z = 0; //Secondary position in the buffer (to not erase i)
  int numRecords = 0; // The number of records in the buffer.

  len = read(fd, line, BUFFER_SIZE); // Read in bytes up to BUFFER_SIZE
  if(len < 0) { // Error reading, print error.
    err_sys("Failed to read countries file.\n");
  }
  // Get the last character in the buffer.
  i = len - 1;
  while(line[i--] != '\n'); // Set i to the last new line character in the array.
  line[i] = '\0'; // Replace that new line with a null (chops off the rest).

  // Set the current position in the file to where the last whole record ended.
  lseek(fd, -(len-i)+1, SEEK_CUR); 

  // Find all of the new line characters, if it finds one, add 1 to numrecords.
  while(line[z++] != '\0') {
    if(line[z] == '\n') {
      numRecords++;
    } 
  }
  numRecords++;
  
  // Len will be 1 if it reached the end of file.
  if(len == 1) {
    return 0; // No records found.
  }else{ 
    return numRecords; 
  }
}
