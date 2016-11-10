#include <stdio.h>

#include "threadpool.h"

void dispatch_to_me(void *arg) {
	int *number = (int *)arg;
	printf("hello world! %d\n", *number);
}

int main() {
	threadpool pool = create_threadpool(6);
	for(int i = 0; i < 15; i++) {
		dispatch(pool, dispatch_to_me, &i);
	}
	destroy_threadpool(pool);
	
}
