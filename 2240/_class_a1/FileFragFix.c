// An example of picking off the last 'fragment'of a read from 
// a file with line delimited records using a fixed size buffer
// lseek() is used to back up the file pointer and reread the fragment
// from the first read
#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include "apue.h" // Stevens' error handling
#define BUFFSIZE 200 // To make debugging easier. You use 1000
#define FALSE 0
#define TRUE -42

int main(int argc, char *argv[])
{ char Buffer[BUFFSIZE+1], ch;  
    int fd, ReadCount, Ndx ;

	fd =  open("AllCountries.dat",O_RDONLY);
	if (fd < 0) err_sys("Failed to open Countries File\n");
// First read 
     ReadCount = read(fd,Buffer,BUFFSIZE); // Fill the buffer 
     printf("\n%u is ReadCount\n and here's the data\n",ReadCount); 
     write(STDOUT_FILENO,Buffer,ReadCount); // And look at the data
     Ndx=ReadCount-1; // subscript of last character read 
     while (Buffer[Ndx--] != '\n'); // Find last /n
     					// N.B. no loop body
     printf("\n %u is last eol \n",Ndx);  
     write(STDOUT_FILENO,Buffer,Ndx+1);// output up to last \n
     write(STDOUT_FILENO,"\nTHAT WAS THE FIRST NO FRAG BUFFER\n",36);
     write(STDOUT_FILENO,"\n AND HERE IS LAST FRAGMENT \n",32);
     write(STDOUT_FILENO,&Buffer[Ndx+1],ReadCount-Ndx);
     lseek(fd,-(ReadCount-Ndx)+1,SEEK_CUR); // back up file pointer
          // Fill the buffer again -- Check that arithmetic above
     ReadCount = read(fd,Buffer,BUFFSIZE); 
	 printf("\n\n %u is 2nd ReadCount\n",ReadCount);
     write(STDOUT_FILENO,Buffer,ReadCount); // Let's see the data 
     Ndx = ReadCount-1; // reread fragment
     write(STDOUT_FILENO,Buffer,Ndx); // The fragment from first 
     						// buffer read is now at beginning
}
