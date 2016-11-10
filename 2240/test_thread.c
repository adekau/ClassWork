#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>

#define MAX_FILES 50

char *filelist[MAX_FILES];

void *handle_file(int tnum) {
	printf("I am thread %i\n", tnum);
	FILE * f = fopen(filelist[tnum], "r");
	char * line = NULL;
	size_t len = 0;
	getline(&line, &len, f);
	printf("%s\n", line); 
	return NULL;
}

int main() {
	pthread_t *threads = malloc(sizeof(pthread_t) * 50);

    	char * dir;
    	DIR *ptr;  
    	struct dirent *ent;
    	int n=0;
    	dir = "./data";
	
    	ptr = opendir(dir);
    	while((ent = readdir(ptr)) != NULL){ 
    		if(ent -> d_type != DT_DIR){ 
			filelist[n] = ent -> d_name;
                	n++;
            	}       
        }
	for(int i = 0; i < n; i++) {
		pthread_create(&threads[i], NULL, handle_file, i);
	}
	for(int i = 0; i < n; i++) {
		pthread_join(&threads[i], NULL);
	}
}
