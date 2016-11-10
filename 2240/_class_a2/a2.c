// Alex Dekau
// Assignment 2
// Program 2 (reads the binary files)
#include "apue.h"
#include "a2.h" // a2.h contains defines for buffer size and number of countries and the struct.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stores the directory file in memory in alphabetic order to be binary searched.

char *readCode();
int   findCountry(cDirectory cdir[], char * ctf, int countries);


int main() {
  FILE * fpr;  //Used for reading the directory (CountryDirectory)
  FILE * fp;   //Used for reading the BinaryCountries.bin
  int    nameLen; // Used for storing the length of the variable "name" field.
  char * countryCode; // Used for storing the requested country's code.
  char * countryName; // Used for storing the requested country's name.
  int    countryPop;  // Used for storing the requested country's population.
  float  countryLexp; // Used for storing the requested country's life expectancy.
  char * code; // Used for storing the code to search for using binary search.
  int index; // The return from the binary search function that stores where in memory the country is in the struct.
  int offset; // Stores the file offset (BinaryCountries.bin) to seek to.

  // Try to open the CountryDirectory, display an error if it is not possible.
  if((fpr = fopen("CountryDirectory", "rb")) == NULL) {
    err_sys("Error opening CountryDirectory");
  }

  // Allocate plenty of space for all the directory data.
  cDirectory * cDir = malloc(sizeof(cDirectory) * NUM_COUNTRIES);

  // Read in all the records from the directory file.
  fread(cDir, sizeof(cDirectory), NUM_COUNTRIES, fpr); 
  fclose(fpr); //Close the file, no longer needed.

  // Try to open the BinaryCountries.bin file, display an error if it is not possible.
  if((fp = fopen("BinaryCountries.bin","rb")) == NULL) {
    err_sys("Error opening BinaryCountries.bin");
  }
  
  // Get a 3 letter code from the user.
  code = readCode();
  // Keep asking for a 3 letter code from the user until they type "ext"
  while(strcmp(code, "ext") != 0){
    // Binary search for the country specified.
    index = findCountry(cDir, code, NUM_COUNTRIES); 
    // Now get the info
    if(index != -1) {
      // Get the offset based on the index returned from the binary search.
      offset = cDir[index].offset;
      if((fseek(fp, offset, SEEK_SET)) < 0) { // Seek to it.
        err_sys("Failed to seek in BinaryCountries.bin");
      } 
      // The way I handle the variable length name is by storing an integer at the front of
      // the record that can be read right away so calculations can be done on how long the
      // record is exactly.
      if((fread(&nameLen, sizeof(int), 1, fp)) == 0) {
        err_sys("Failed to read name length.");
      } 
      // Allocate the memory needed for the code.
      countryCode = malloc(3); 
      // Allocate the amount of memory needed as stated by the BinaryCountries file.
      countryName = malloc(nameLen);
      // Move to the OFFSET plus the size of an int (to get to the code).
      offset += sizeof(int);
      if((fseek(fp, offset, SEEK_SET)) < 0) {
        err_sys("Failed to seek in BinaryCountries.bin");
      }
      if((fread(countryCode, CODE_SIZE, 1, fp)) == 0) { // Read in the code.
        err_sys("Failed to read country code.");
      }
      offset += CODE_SIZE; // Move past the code.
      if((fseek(fp, offset, SEEK_SET)) < 0) { // Now seek to that location.
        err_sys("Failed to seek in BinaryCountries.bin");
      }
      if((fread(countryName, nameLen, 1, fp)) == 0){ // Read in the variable long name.
        err_sys("Failed to read country name.");
      }
      offset += nameLen; // Seek past the name using the variable length specified by the file.
      if((fseek(fp, offset, SEEK_SET)) < 0) {
        err_sys("Failed to seek in BinaryCountries.bin");
      }
      if((fread(&countryPop, sizeof(int), 1, fp)) == 0) { // Now get the population
        err_sys("Failed to read country population.");
      }
      offset += sizeof(int); // Population is an int, so seek past it with the size of an int.
      if((fseek(fp, offset, SEEK_SET)) < 0) {
	err_sys("Failed to seek in BinaryCountries.bin");
      } 
      if((fread(&countryLexp, sizeof(float), 1, fp)) == 0) { // Now grab the last piece, the life expectancy.
        err_sys("Failed to read country life expectancy.");
      }
      // Now present the findings to the user.
      printf("Code: %s, name: %s, pop: %d, lexp: %f\n\n", countryCode, countryName, countryPop, countryLexp); 
    }else{
      // Tell the user if the country can't be located.
      printf("Country %s not found.\n\n", code);
    }
    code = readCode();
  }

  fclose(fp);
  return 0;
}

// This function asks the user to enter a 3 letter code to try to find.
char *readCode() {
  printf("Enter a 3-letter country code, or \"ext\" to quit:\n>");
  char * line = malloc(CODE_SIZE + 1), *linep = line; // Will return the line pointer.
  int lenmax = CODE_SIZE + 1; // The maximum allowed characters to be input (+1 to allow for new line char)
  int c; // The character to be read.

  if(line == NULL) { // NULL Case
    return NULL;
  }
  for(;;) { // Infinite loop to keep asking for a character
    c = fgetc(stdin); // Read the character from standard input
    if(c == EOF) { // If it's the end of file, leave the loop.
      break;
    }
    if(--lenmax == 0) { // If it's at the max length, leave the loop.
      break;
    }
    if((*line++ = c) == '\n') { // If they press enter, leave the loop.
      break;
    }
  }
  *line = '\0'; // Add the null character (for the string library strcmp)
  return linep;
}

// This function uses binary search on the country directory structure by comparing codes.
int findCountry(cDirectory cdir[], char ctf[], int countries) {
  int mid, result; // Result is the result of strcmp, determines if a code is less than or greater than.
  int high = countries - 1; // Set the high to the user specified countries.
  int low = 0; 
  mid = (low + high) / 2; // Get the middle index.
  while(low <= high) { 
    result = strcmp(cdir[mid].code, ctf);

    if(result < 0){ 
      low = mid + 1;
    }else if(result > 0) {
      high = mid - 1;
    }else{
      return mid;
    }
    mid = (low + high) / 2;
  }
  return -1; // Will use -1 as the return value for "not found"
}
