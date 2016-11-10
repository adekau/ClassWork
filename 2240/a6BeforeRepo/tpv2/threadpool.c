// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Implements a thread pool.
// Author: Alex Dekau
// Class: CS2240
// Algorithm Design found at:
//  - https://software.intel.com/en-us/forums/intel-moderncode-for-
//    parallel-architectures/topic/305835
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threadpool.h"

threadpool threadpool_create(int number_of_threads) {
	// Allocate the pool
	_threadpool *pool = malloc(sizeof(_threadpool));
	
	// Check for the number of threads being invalid.
	if(number_of_threads <= 0) {
		fprintf(stderr, "Can't create a thread pool with 0 or less threads.\n");
		return NULL;
	}
	
	// Set the struct members.
	pool -> nthreads_total = number_of_threads;
	pool -> nthreads_created = 0; // The total number of threads created.
	pool -> nthreads = 0;
	pool -> threads = malloc(sizeof(pthread_t) * number_of_threads);
	pool -> queue_size = 0;
	pool -> queue_first = NULL;
	pool -> queue_last = NULL;
	pool -> pool_deleting = 0;
	pool -> no_new_work = 0;

	// Create the mutex
	if(pthread_mutex_init(&(pool -> queue_lock), NULL)) {
		fprintf(stderr, "Couldn't create the mutex lock.\n");
		return NULL;
	}
	// Create the conditions.
	if(pthread_cond_init(&(pool -> work_avail), NULL)) {
		fprintf(stderr, "Couldn't create the work avail condition variable.\n");
		return NULL;
	}
	if(pthread_cond_init(&(pool -> no_work), NULL)) {
		fprintf(stderr, "Couldn't create the no work condition variable.\n");
	}

	// Create the threads.
	for(int i = 0; i < number_of_threads; i++) {
		if(pthread_create(&(pool->threads[i]), NULL, threadpool_work_handler,
				pool)) {
			// Thread not created successfully.
			fprintf(stderr, "Error creating threadpool thread.\n");
			return NULL;
		}else{
			// Thread created successfully.
			pool->nthreads++;
			pool->nthreads_created++;
		}
	}
	
	return (threadpool) pool;
}

void *threadpool_work_handler(threadpool tp) {
	_threadpool *pool = (_threadpool *)tp;
	threadpool_work *work;

	while(1) {
		// Wait until lock is acquired.
		pthread_mutex_lock(&(pool->queue_lock));

		// Lock is acquired, now wait for condition signal
		// that work has been added to the queue.
		while(pool->queue_size == 0) {
			// Check if the pool is in deletion stage
			if(pool->pool_deleting) {
				// Abort current thread.
				// Give up the lock to something else.
				pthread_mutex_unlock(&(pool->queue_lock));
				// Quit thread
				pthread_exit(NULL);
			}
			// Not in deletion stage, wait for available work.
			pthread_cond_wait(&(pool->work_avail), &(pool->queue_lock));

			// Reacquired lock, need to check if pool is
			// in deletion stage again.
			if(pool->pool_deleting) {
				pthread_mutex_unlock(&(pool->queue_lock));
				pthread_exit(NULL);
			}
		}
		
		// Queue should not be empty, but safety check anyway.
		if(pool->queue_size == 0) {
			fprintf(stderr, "Pool is empty when it should not be.\n");
			// Abort thread.
			pool -> nthreads--;
			pthread_mutex_unlock(&(pool->queue_lock));
			pthread_exit(NULL);

		}
		// Now the pool is not empty, so grab the next in queue.
		work = pool->queue_first;
		// Decrement the queue size.
		pool->queue_size -= 1;

		// Check if decrementing the queue reached 0.
		if(pool->queue_size == 0) {
			// Set two queue side pointers to NULL since there's nothing
			// in the queue.
			pool->queue_first = NULL;
			pool->queue_last = NULL;
			// signal that the queue is empty
			if(!pool->pool_deleting){
				pthread_cond_signal(&(pool->no_work));
			}
		}else{
			// There's something in the queue still, so set the next
			// in line to the front of the queue.
			pool->queue_first = work->next;
		}

		// Unlock the mutex.
		pthread_mutex_unlock(&(pool->queue_lock));
		// Do the work routine.
		(work->work_fn)(work->work_arg);
		free(work);
	}
}

void threadpool_add_work(threadpool tp, void (*work_fn)(void *), void * arg) {
	_threadpool *pool = (_threadpool *)tp;
	threadpool_work *work;

	// Check if a thread has been lost.
	if(pool->nthreads < pool->nthreads_total) {
		//fprintf(stderr, "[INFO] A thread has been lost. Attempting to replenish the threadpool.\n");
		// Replenish the thread pool

		// Check for the scenario that the threadpool is in the deletion process.
		if(pool->no_new_work || pool->pool_deleting) {
			return;
		}
		// Allocate some additional memory to accomodate for the new threads.
		int reallocsize = (pool->nthreads_total - pool->nthreads) + pool->nthreads_created;
		pool->threads = realloc(pool->threads, reallocsize * sizeof *(pool->threads));

		for(int i = 0; i < (pool->nthreads_total - pool->nthreads); i++) {
			// Will need to realloc the threads list and add a new thread to the list.
			if(pthread_create(&(pool->threads[(pool->nthreads_created) + i]), NULL, 
					threadpool_work_handler, pool)) {
				fprintf(stderr, "Failed to replenish thread in the pool.\n");
				return;
			}else{
				//fprintf(stderr, "[INFO] Thread replenished successfully.\n");
				pool->nthreads_created++;
				pool->nthreads++;
			}
		}
	}

	// Allocate the work element.
	work = malloc(sizeof(threadpool_work));
	work->work_fn = work_fn;
	work->work_arg = arg;
	work->next = NULL;

	// Acquire the mutex lock to mess with the work queue.
	pthread_mutex_lock(&(pool->queue_lock));
	// Check if pool is accepting work.
	if(pool->no_new_work) {
		free(work);
		return;
	}

	// Now add it to the queue.
	if(pool->queue_size == 0) {
		// If there is no work in the queue already, then make
		// this new work the first and the last in the queue.
		pool->queue_first = work;
		pool->queue_last = work;
		// Signal threads that there is work available.
		pthread_cond_signal(&(pool->work_avail));
	}else{
		// If it's not empty, then set the last one's next pointer
		// to this new one, then set the last one to this one.
		// (creating a linked-list)
		pool->queue_last->next = work;
		pool->queue_last = work;
	}
	// Either way the if statement results in, increment the queue size.
	pool->queue_size += 1;
	// Unlock the mutex, not messing with the queue anymore.
	pthread_mutex_unlock(&(pool->queue_lock));
}

void threadpool_delete(threadpool tp) {
	_threadpool *pool = (_threadpool *)tp;
	
	pthread_mutex_lock(&(pool->queue_lock));
	pool->no_new_work = 1;

	// While the queue is not empty.
	while(pool->queue_size != 0) {
		// Wait for it to be empty.
		pthread_cond_wait(&(pool->no_work), &(pool->queue_lock));		
	}
	// Now the queue is empty, tell threads deletion is happening
	// Will cause the threads to pthread_exit() and release their lock.
	pool->pool_deleting = 1;
	
	// Simulate queue not being empty to trigger the threads to
	// reach the if(pool->pool_deleting) section, causing them to exit.
	pthread_cond_broadcast(&(pool->work_avail));

	// release the lock so the threads can use it.
	pthread_mutex_unlock(&(pool->queue_lock));

	// Join the threads.
	for(int i = 0; i < pool->nthreads; i++) {
		pthread_join(pool->threads[i], NULL);
	}
	// Deallocate the pool resources.
	free(pool->threads);
	pthread_mutex_destroy(&(pool->queue_lock));
	pthread_cond_destroy(&(pool->work_avail));
	pthread_cond_destroy(&(pool->no_work));
	return;
}
