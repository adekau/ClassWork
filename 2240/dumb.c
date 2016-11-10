#include <stdio.h>
#include <stdlib.h>

#define compile_error_or_zero(e) (sizeof(struct { int:-!!(e); } )); 
#define compile_error_on_null(e) ((void *)sizeof(struct{int:-!!(e);}));

int main(void) {
  char * e;
  compile_error_or_zero(0);
  compile_error_on_null(e);
  return 0;
}
