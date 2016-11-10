#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#include <unistd.h>
#include "threadpool.h"

void do_work(void *arg);

int main() {
	threadpool mainpool;
	mainpool = threadpool_create(6);
	if(mainpool == NULL) {
		fprintf(stderr, "Thread pool not created successfully.\n");
		return 0;
	}
	int *test;
	for(int i = 0; i < 100; i++) {
		test = (int *)malloc(sizeof(int));
		*test = i;

		threadpool_add_work(mainpool, do_work, test);
	}
	threadpool_delete(mainpool);
	return 0;
}

void do_work(void *arg) {
	int *number = (int *)arg;
	printf("Hello world! %d\n", *number);
}
