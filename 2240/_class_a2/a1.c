#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "a2.h" // includes defines for buffer size, number of countries, and the cdirectory struct.

int getRecords(int fd, char * line); // in getRecords.c
int compare(const void *s1, const void *s2); // at the end of this file

//Main function
int main(int argc, char* argv[]) {
 // This stores the country data retrieved from the AllCountries.dat file.
  struct country {
    char * code;
    char * name;
    int    pop;
    float  lexp;
  };
   
  // Create the two struct arrays.
  cDirectory cDir[NUM_COUNTRIES];
  struct country * countries = malloc(sizeof(struct country) * NUM_COUNTRIES);
  int    fd; // file descriptor
  char * line = malloc(BUFFER_SIZE * sizeof(char)); //Set all the relevant buffering arrays to the right buffer size.
  char * token = malloc(BUFFER_SIZE * sizeof(char));
  char * record = malloc(BUFFER_SIZE * sizeof(char));
  char * leftovers = malloc(BUFFER_SIZE * sizeof(char));
  int    curtok; // The current token in the record (used for pulling off specific values)
  int    numRecords; // The number of records returned from getRecords()
  int    curCountry = 0; // the current country being written to (in the struct array)
  
  fd = open("AllCountries.dat", O_RDONLY);
  // Print an error message if the file can't be opened.
  if(fd < 0) {
    err_sys("Error opening file.\n");
  }

  // Iterator value for the number of records (to split by new line character)
  int i, z, numRecordsTmp;
  numRecords = getRecords(fd, line);
  while(numRecords != 0) { // while it's still reading records.
    record = strtok_r(line, "\n", &leftovers); // Get the first line (token)
    for(i = 0; i < numRecords; i++) {
      curtok = 0; //
      while((token = strtok_r(record, ",", &record))) { // while there are tokens from the record still being gotten.
        if(curtok == 1) {
          countries[curCountry].code = malloc(strlen(token)); //Malloc the exact number of bytes needed. This is to make it variable sized.
	  strcpy(countries[curCountry].code, token); // Copy the string to the char[] to make sure I'm not messing with ptrs
        }else if(curtok == 2) { // The name field
          countries[curCountry].name = malloc(strlen(token));
	  strcpy(countries[curCountry].name, token);
        }else if(curtok == 7) { // The population field
	  countries[curCountry].pop  = atoi(token);
        }else if(curtok == 8) { // The life expectancy field.
	  countries[curCountry].lexp = atof(token);
        }
        curtok++; // add one to the current token.
      }
      curCountry++; // add one to the current country.
      record = strtok_r(NULL, "\n", &leftovers);// Get the next line(token)
    } 
    numRecords = getRecords(fd, line);
  } 

  // Set up the stream 
  FILE * fp = fopen("BinaryCountries.bin", "wb"); // Create a stream instead of a file descriptor
  if(fp < 0) {
    err_sys("Unable to open BinaryCountries.bin");
  }
  int nameLen; // the length of the name field.
  int popToWrite;
  float lexpToWrite;
  fpos_t offset; // Start the offset at 0.

  // Now write the structs to a file.
  for(int i = 0; i < NUM_COUNTRIES; i++) {
    if(countries[i].name != NULL) {
      nameLen     = strlen(countries[i].name);
      popToWrite  = countries[i].pop;   // Store population in a new integer for ease of reference
      lexpToWrite = countries[i].lexp;  // Same as above
      fgetpos(fp, &offset);
  
      fwrite(&nameLen         , sizeof(int)              , 1, fp);
      fwrite(countries[i].code, strlen(countries[i].code), 1, fp);
      fwrite(countries[i].name, strlen(countries[i].name), 1, fp);
      fwrite(&popToWrite      , sizeof(int)              , 1, fp);
      fwrite(&lexpToWrite     , sizeof(float)            , 1, fp);
  
      strcpy(cDir[i].code, countries[i].code);
      cDir[i].offset = offset;
    }
  }
  fclose(fp);
 
  qsort(cDir, NUM_COUNTRIES, sizeof(cDirectory), compare);
  //Set up the file stream
  FILE * countryDir = fopen("CountryDirectory", "wb");
  //Now write the directory file.
  i = -1; // lower bound of the array
  while(cDir[++i].code[0] < 65); //find the first nonnull entry in the directory array.
  z = NUM_COUNTRIES; // upper bound of the array
  while(cDir[--z].code[0] < 65); //find the last nonnull entry in the directory array.
  z = 300 - z; // get the number of null entries instead of the index in the array.
  // Write the struct array starting at the first non null entry to the last non null entry.
  fwrite(&cDir[i], sizeof(cDirectory), NUM_COUNTRIES - (i + z), countryDir); 
  //fwrite(&cDir[0], sizeof(cDirectory), NUM_COUNTRIES, countryDir);

  if(close(fd) < 0) {
    err_sys("Failed to close file.\n");
  }
}

// Compare function is used for quicksort on the directory struct. Used as it's "comparator".
int compare(const void *s1, const void *s2) {
  cDirectory *c1 = (cDirectory *)s1;
  cDirectory *c2 = (cDirectory *)s2;

  int codeCompare = strcmp(c1->code, c2->code);
  return codeCompare;
}
