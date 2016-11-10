#include <stdio.h>
#include <stdlib.h>

//Framework -- the bold text varies.

int func(int);
int main(){
int *A = malloc(5*(sizeof(int)));
A[0] = 0x804b018;
A[1] = 0x804b014;
A[2] = 0x804b010;
A[3] = 0x804b00C;
A[4] = 0x804b008;

printf( "Returned %x\n", func(&A[3]));
}

int func(int **Q)
{
  return (*Q);
}
