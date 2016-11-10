#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <fcntl.h>

int getRecords(int fd, char * line);

int main(int argc, char* argv[]) {
  struct country {
    char   code[4];
    char   name[50];
    long   pop;
    double lexp;
  };

  struct country countries[239];

  int    fd;
  char * line = malloc(1000 * sizeof(char));
  char * token = malloc(1000 * sizeof(char));
  char * record = malloc(1000 * sizeof(char));
  char * leftovers = malloc(1000 * sizeof(char));
  int    curtok;
  int    numRecords;
  char   codeToSearch[4];
  int    curCountry = 0;
  
  if(argc != 2) {
    write(STDOUT_FILENO, "Usage: ", 7);
    write(STDOUT_FILENO, argv[0], strlen(argv[0]));
    write(STDOUT_FILENO, " [country code OR all]\n", 23); 
  }else{
    if(strlen(argv[1]) != 3) {
      write(STDOUT_FILENO, "Country code must be 3 characters long.\n", 40);
      return 0;
    }else{
      strcpy(codeToSearch, argv[1]);
    }
  }

  fd = open("AllCountries.dat", O_RDONLY);

  if(fd < 0) {
    err_sys("Error opening file.\n");
  }

  int i;
  while((numRecords = getRecords(fd, line)) != 0) {
    record = strtok_r(line, "\n", &leftovers);
    for(i = 0; i < numRecords; i++) {
      curtok = 0;
      while((token = strtok_r(record, ",", &record))) {
        if(curtok == 1) {
	  strcpy(countries[curCountry].code, token);
        }else if(curtok == 2) {
	  strcpy(countries[curCountry].name, token);
        }else if(curtok == 7) {
	  countries[curCountry].pop  = atoi(token);
        }else if(curtok == 8) {
	  countries[curCountry].lexp = atof(token);
        }
        curtok++;
      }
    curCountry++;
    record = strtok_r(NULL, "\n", &leftovers);
    } 
  } 

  if(strncmp("all", codeToSearch, 3) == 0) {
    for(i = 0; i < 239; i++) {
      printf("Code: %s, Name: %s, Population: %ld, Life Expectancy: %.2f\n", countries[i].code, countries[i].name, countries[i].pop, countries[i].lexp);

    }
  }else{
    for(i = 0; i < 239; i++) {
      if(strncmp(countries[i].code, codeToSearch, 3) == 0) {
        printf("Code: %s, Name: %s, Population: %ld, Life Expectancy: %.2f\n", countries[i].code, countries[i].name, countries[i].pop, countries[i].lexp);
        break;
      }else{
        if(i == 238 && argc == 2) write(STDOUT_FILENO, "Country not found.\n", 19);
      }
    }
  }

  if(close(fd) < 0) {
    err_sys("Failed to close file.\n");
  }
}
