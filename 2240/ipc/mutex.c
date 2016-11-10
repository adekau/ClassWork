#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

int counter = 0;

void *fn(void *arg);

int main(){
	pthread_mutex_init(&lock, NULL);

	pthread_t tid[2];
	for(int i = 0; i < 2; i ++) {
		pthread_create(&(tid[i]), NULL, fn, i);
	}
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	printf("%d\n", counter);
	return 0;
}

void *fn(void *arg) {
	pthread_mutex_lock(&lock);
	for(int i = 0; i < 500; i++) {	
		counter += 1;
	}
	pthread_mutex_unlock(&lock);
	return NULL;
}
