#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <string.h>

// Defines for values that should be "big enough"
#define MAX_FILES 	50
#define RECORD_MAX_SIZE 1024
#define MAX_RECORDS	512 // If the program says to make this bigger, increase this.

// The "Record". Stores information about each line in a file.
typedef struct Record {
	char * username;
	char * password;
	char * blood;
	char * domain_name;
	int index;
} Record;

// An array of strings of size MAX_FILES that are the file paths to be 
// opened in each thread. There should be NO race condition because 
// once the threads get to it, all data is already written to it. Threads
// treat it as READ ONLY.
char **files;

// An int array of size MAX_FILES used to store the number of records in each
// file.
int  *tNumRecords;

// Comparator function used for qsort. Compares the index value of a Record.
int recordComparator(void * a, void * b) {
	Record *ar = (Record*)a;
	Record *br = (Record*)b;
	return ar->index - br->index;
}

// The thread handling function. Only argument is it's "thread id" which it 
// will use as it's unique accessor for any global read-only array it needs
// to access.
void *handle_record(int thread_num) {
	//printf("Thread %i using file %s\n", thread_num, files[thread_num]); 
	char *filePath = files[thread_num]; // Get path to open.
	FILE *fp = fopen(filePath, "r"); // Open the unique file.
	char * line = NULL; // To be used for getline.
	size_t len = 0;     // also to be used for getline.
	int recordCount = 0;// Counter for keeping track of record count.
	// The record array for this thread. Will be returned to the
	// main method once thread_join()ed.
	Record *trecords = malloc(sizeof(Record) * MAX_RECORDS);

	// Main loop of the thread. It will read a line until it returns
	// -1 (EOF) then tokenize by a comma and put it into the struct
	// array created above.
	while(getline(&line, &len, fp) != -1) {
		if(recordCount == MAX_RECORDS) {
			// Prints a message to the user if there are more
			// records than space available in the array.
			printf("Need to increase the size of MAX_RECORDS at the top of the source file..\n");
			exit(0); // Quit the program to prevent problems.
		}
		char *uname, *pw, *bt, *domain, *ind, *savePtr;
		int indx;
		// Tokenize the line received by commas.
		uname = strtok_r(line, ",", &savePtr);
		pw = strtok_r(NULL, ",", &savePtr);
		bt = strtok_r(NULL, ",", &savePtr);
		domain = strtok_r(NULL, ",", &savePtr);
		ind = strtok_r(NULL, ",", &savePtr);
		indx = atoi(ind);
		// Allocate neccessary space on the heap for the
		// strings in the records.
		trecords[recordCount].username = malloc(sizeof(char) * strlen(uname));
		trecords[recordCount].password = malloc(sizeof(char) * strlen(pw));
		trecords[recordCount].blood    = malloc(sizeof(char) * strlen(bt));
		trecords[recordCount].domain_name = malloc(sizeof(char) * strlen(domain));
		// Copy the temporary variables into the struct array.
		strcpy(trecords[recordCount].username, uname);
		strcpy(trecords[recordCount].password, pw);
		strcpy(trecords[recordCount].blood, bt);
		strcpy(trecords[recordCount].domain_name, domain);
		trecords[recordCount++].index = indx;
	}
	// Save the record count to the tNumRecords array.
	// This will not lead to a race condition due to each thread having a 
	// UNIQUE spot in this array based on the unique thread ID given by
	// pthread_create()
	tNumRecords[thread_num] = recordCount;
	// Give the records to the main function for combining.
	return (void *)trecords;
}

int main() {
	// Create "big enough" arrays based on MAX_FILES macro.
	pthread_t pt[MAX_FILES]; // Stores the threads that were created for joining.
	tNumRecords = malloc(sizeof(int) * MAX_FILES);
	files = malloc(sizeof(char *) * MAX_FILES); // stores filenames for threads.

	char *dirName = "./data"; // Location of the files.
	DIR  *dir;
	struct dirent *dp;
	int fcount = 0;
	dir = opendir(dirName);
	char filePath[100]; // Needs to be sufficiently large to strcat to.
	strcpy(filePath, "./data/"); // Can't directly assign value to char array.

	// Loop through all "directories" inside the data folder until there are no more.
	while((dp = readdir(dir)) != NULL) {
		// Make sure it's not . or ..
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) continue;
		// If it's NOT a directory
		if(dp -> d_type != DT_DIR) {
			// Create the filepath by taking ./data/ and appending the name.
			strcat(filePath, dp->d_name);
			// Duplicate the string into the files array and increment fcount.
			files[fcount++] = strdup(filePath);
			// Reset filePath for the next entry.
			strcpy(filePath, "./data/");
		}
	}

	//Create the threads and pass the thread ID to the thread.
	for(int i = 0; i < fcount; i++) {
		pthread_create(&pt[i], NULL, (void*)handle_record, i);
	}

	// Keep track of the total number of records across all files to 
	// dynamically allocate the final struct to the heap.
	int totalRecordCount = 0;
	// Create an array of the record arrays returned from the pthreads.
	Record **records = malloc(sizeof(Record *) * fcount);
	for(int i = 0; i < fcount; i++) {
		pthread_join(pt[i], (void *)&records[i]);
		totalRecordCount += tNumRecords[i];
	}
	free(files); // don't need files or tNumRecords arrays in memory anymore.
	free(tNumRecords);

	Record *allRecords = malloc(sizeof(Record) * totalRecordCount);
	
	// Copy all the individual arrays returned from the threads into one large 
	// sortable array by copying the memory of each array one after another
	// into the records array of the exact needed size.
	memcpy(&allRecords[0], &records[0][0], sizeof(Record) * tNumRecords[0]);
	int curPos = tNumRecords[0];
	for(int i = 1; i < fcount; i++) {
		memcpy(&allRecords[curPos], &records[i][0], sizeof(Record) * tNumRecords[i]);
		curPos += tNumRecords[i];
	}
	// Should not need the original array anymore.
	free(records);
	
	//Now qsort the array:
	qsort(&allRecords[0], totalRecordCount, sizeof(Record), 
		(void *)recordComparator);

	FILE * output = fopen("./sorted.yay", "wb");
	for(int i = 0; i < totalRecordCount; i++) {
		char * uname  = allRecords[i].username;
		char * pw     = allRecords[i].password;
		char * bt     = allRecords[i].blood;
		char * domain = allRecords[i].domain_name;
		int indx      = allRecords[i].index;
		fprintf(output, "%s,%s,%s,%s,%d\n", uname, pw, bt, domain, indx);
	}
	free(allRecords); // Not being used anymore.
}
