#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "threadpool.h"

// {TODO}: Add a destroy method to free the thread pool from memory.


// The handler for threadpool work.
// {TODO}:  Might need to be renamed to be more clear?
void *handle_request(void *tp) {
	threadpool *pool = (threadpool *) tp;
	request *cur_request;
	
	while(1) {
		// Wait for the lock to be available, then grab it and lock it
		pthread_mutex_lock(&(pool->request_queue_lock));
		
		// Wait for there to be work.
		while(pool -> queue_size == 0) {
			if(pool->deleting) {
				pthread_mutex_unlock(&(pool -> request_queue_lock));
				pthread_exit(NULL);
			}
			pthread_mutex_unlock(&(pool->request_queue_lock)); // Give up the lock
			pthread_cond_wait(&(pool->work_avail), &(pool->request_queue_lock));
			if(pool->deleting) {
				pthread_mutex_unlock(&(pool->request_queue_lock));
				pthread_exit(NULL);
			}
		}

		// Get the next in line request to handle.
		cur_request = pool -> queue_head;
		pool->queue_size--;

		if(pool->queue_size == 0) {
			// The pointers to the top and end of the queue
			// do not exit, so set to NULL.
			pool->queue_head = NULL;
			pool->queue_tail = NULL;
		}else{
			// Set the next in line to the next request.
			pool->queue_head = cur_request->next_request;
		}

		if(pool->queue_size == 0 && !pool->deleting) {
			// request queue is now empty, signal the rest of the threads
			// that there is no work.
			pthread_cond_signal(&(pool->no_work));
		}
		pthread_mutex_unlock(&(pool->request_queue_lock));
		// Now call the request handler routine.
		(cur_request -> request_handler)(cur_request -> request_arg);
		free(cur_request);
	}
}


// Function to create the threadpool:
void *threadpool_create(int numthreads) {
	threadpool *pool;
	int i;
	
	// Make sure that the threads is greater than 0.
	if(numthreads <= 0) return NULL;

	pool = (threadpool *) malloc(sizeof(threadpool));
	pool -> threads = (pthread_t *) malloc(sizeof(pthread_t) * numthreads);
	pool -> num_threads = numthreads;
	pool -> queue_size = 0;
	pool -> queue_head = NULL;
	pool -> queue_tail = NULL;
	pool -> deleting = 0;

	// Initialize the conditions and mutex
	if(pthread_mutex_init(&(pool->request_queue_lock), NULL)) {
		fprintf(stderr, "Error initializing mutex.\n");
		return NULL;
	}
	if(pthread_cond_init(&(pool->work_avail), NULL)) {
		fprintf(stderr, "Error initializing condition.\n");
		return NULL;
	}
	if(pthread_cond_init(&(pool->no_work), NULL)) {
		fprintf(stderr, "Error initializing condition.\n");
		return NULL;
	}
	
	for(i = 0; i < pool -> num_threads; i++) {
		if(pthread_create(&(pool->threads[i]), NULL, handle_request, pool)) {
			fprintf(stderr, "Error creating thread.\n");
			return NULL;
		}
	}

	return (void *) pool;
}


void threadpool_delete(void *tp) {
	threadpool *pool = (threadpool *)tp;
	void *joiner;

	// get the lock
	pthread_mutex_lock(&(pool -> request_queue_lock));
	pool->deleting = 1;
	while(pool -> queue_size != 0) {
		// wait for all requests to be completed (wait for no_work cond)
		pthread_cond_wait(&(pool->no_work), &pool->request_queue_lock);
	}

	pthread_cond_broadcast(&(pool->work_avail));
	pthread_mutex_unlock(&(pool->request_queue_lock));

	for(int i = 0; i < pool -> num_threads; i++) {
		pthread_cond_broadcast(&(pool->work_avail));
		pthread_join(pool->threads[i], &joiner);
		//free(pool->threads[i]);
	}
	free(pool->threads);
	pthread_mutex_destroy(&(pool->request_queue_lock));
	pthread_cond_destroy(&(pool->work_avail));
	pthread_cond_destroy(&(pool->no_work));
}

void threadpool_add_request(void *tp, send_request req, void *arg) {
	threadpool * pool = (threadpool *) tp;
	request *cur_request;
	
	// Allocate memory for the request struct
	cur_request = (request *) malloc(sizeof(request));

	cur_request->request_handler = req;
	cur_request->request_arg = arg;
	cur_request->next_request = NULL;

	// Try to get a turn at the lock.
	pthread_mutex_lock(&(pool->request_queue_lock));
	

	// prevent adding more requests if the pool is being deleted
	if(pool -> deleting) {
		free(cur_request);
		return;
	}

	// Now add the request to the request queue in a FIFO manner
	if(pool -> queue_size == 0) {
		pool -> queue_head = cur_request;
		pool -> queue_tail = cur_request;
		pthread_cond_signal(&(pool -> work_avail));
	}else{
		pool -> queue_tail -> next_request = cur_request;
		pool -> queue_tail = cur_request;
	}
	// Pool size increase.
	pool -> queue_size++;
	
	// Release the lock so something else can have a go at it.
	pthread_mutex_unlock(&(pool->request_queue_lock));
}
