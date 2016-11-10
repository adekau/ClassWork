#include <stdio.h> // Program will fail an execlp then modify
#include <stdlib.h> // the path on the fly so it will succeed.
#include "apue.h"

extern char **environ;

int main() {
	int j = 0;
	/*while(environ[j] != NULL) {
	 	printf("%s\n", environ[j++]);
	}*/
	char * temp_env;
	temp_env = getenv("PATH");
	printf("Current PATH = %s\n", temp_env);
}
