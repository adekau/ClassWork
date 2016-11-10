#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *ThreadPool_thread(void *unused);

// Stores data about a thread in the pool, including the pthread_t, whether it's in use or not, and a unique id.
struct ThreadInPool {
	char 	  thread_id;
	pthread_t thread;
	char 	  in_use;
};

int main () {
	// Get the number of processor cores on the system.
	int num_processors = sysconf(_SC_NPROCESSORS_ONLN);
	// Create number of processor cores + 2 threads.
	int num_threads    = num_processors + 2;

	// Create the Thread Pool.
	struct ThreadInPool ThreadPool[num_threads];

	// Generate the thread pool.
	for(int i = 0; i < num_threads; i++) {
		pthread_t new_pthread = 0;
		struct ThreadInPool *pool_thread = malloc(sizeof(struct ThreadInPool));
		pool_thread->thread_id = i;
		pool_thread->thread = new_pthread;
		pool_thread->in_use = 0;
		ThreadPool[i] = *pool_thread;
		pthread_create(&ThreadPool[i].thread, NULL, ThreadPool_thread, NULL);
	}

	// {DEBUG}: Print the thread pool.
	for(int i = 0; i < num_threads; i++) {
		printf("Thread: %d, in_use: %d \n", ThreadPool[i].thread_id, (int)ThreadPool[i].in_use);
	}

	return 0;
}

void *ThreadPool_thread(void *unused) {
	// {TODO}: Use pipes or sockets to receive a client request?
	while(1) {
		// Infinite loop to prevent thread from dying.
	}
}
