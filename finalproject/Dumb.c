// A program to demo gdb on msp430
#include <msp430.h>

int Glob=0xFACE; // a global .. where does it live?  
int main()
{int i=-1;
     do
     {
     if (i > Glob) 
     i++;
     else
     i=func(i);
     }
     while  (i < 0);
}
int func(int K)
{ return K + (K & 0xf);}
