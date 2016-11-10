#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  typedef struct {
    char * name;
    char * code;
    int    pop;
    float  lexp;
  } Country;

  Country usa;
  FILE * fp;
  char * usaName = "United States of America";
  char * usaCode = "USA";
  int    usaPop  = 318000000;
  float  usaLexp = 77.1;
  
  usa.name = malloc(strlen(usaName) + 1); 
  strcpy(usa.name, usaName);
  usa.name[strlen(usa.name) + 1] = '\0';

  usa.code = malloc(strlen(usaCode) + 1);
  strcpy(usa.code, usaCode);
  usa.code[strlen(usa.code) + 1] = '\0';

  usa.pop = usaPop;
  usa.lexp = usaLexp;

  printf("%lu\n", strlen(usa.code));

  fp = fopen("Test2.bin", "w");
  fwrite(usa.name , strlen(usa.name) + 1, 1, fp);
  fwrite(usa.code , strlen(usa.code) + 1, 1, fp);
  fwrite(&usa.pop , sizeof(int)         , 1, fp);
  fwrite(&usa.lexp, sizeof(float)       , 1, fp);
  fclose(fp);

  
  return 0;
}
