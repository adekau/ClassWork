#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "threadpool.h"

void request_handler(void *arg);

int main(void) {
	void *mainpool;
	mainpool = threadpool_create(6);
	threadpool_add_request(mainpool, request_handler, NULL);
	printf("BETWEEN?\n");
	threadpool_add_request(mainpool, request_handler, NULL);
	threadpool_delete(mainpool);
}

void request_handler(void *arg) {
	fprintf(stderr, "Hello!!\n");
}
