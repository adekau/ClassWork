#include <stdio.h>
#include <stdlib.h>

// framework for test question if 
// i can force past errors

int func(int);
int main()
{int *A = malloc(5*(sizeof(int)));
	printf("Array at %x\n",A);
	
	A[0]= 0x804b018;// location 0x804boo8
	A[1]= 0x804b014;// location 0x804booC, 4 bytes more
	A[2]= 0x804b010;// location 0x804bo10, 4 bytes more
	A[3]= 0x804b00C;// yada 
	A[4]= 0x804b008;// yada 

printf( "Returned %x\n",  func(*A));
	exit(0);
}

