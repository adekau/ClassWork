// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// General purpose thread pool
// Author: Alex Dekau
// Class: CS2240
// Algorithm Design found at: 
//  - https://software.intel.com/en-us/forums/intel-moderncode-for-
//    parallel-architectures/topic/305835
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#ifndef __threadpool_h
#define __threadpool_h

typedef struct _threadpool_work {
	void (*work_fn)(void *);
	void *work_arg;
	struct _threadpool_work *next;
} threadpool_work;

typedef struct __threadpool {
	// Threads
	// Current # of threads in the pool.
	int 			nthreads; 
	// The number of threads that there should be.
	int			nthreads_total;
	// The total number of threads created during the pool's life
	// span. Used for the index of the threads array during 
	// the thread replenish process.
	int			nthreads_created;
	// Array of threads.
	pthread_t 		*threads;
	// Now for the work queue
	int 			queue_size;
	// Pointer to the next thread in line.
	threadpool_work 	*queue_first;
	// Pointer to the last thread in line.
	threadpool_work 	*queue_last;
	// Mutex lock to prevent race conditions on queue access.
	pthread_mutex_t		queue_lock;
	// Condition to signal the threads that work is available.
	pthread_cond_t		work_avail;
	// Condition to signal the threads that there is no work.
	pthread_cond_t		no_work;
	// Used for disallowing new work being added
	// when the thread queue is being emptied and
	// deallocated.
	int			no_new_work;
	int 			pool_deleting;
	
	
} _threadpool;

// Easier to pass void * around and de-reference later
// for threadpool functions
typedef void 	*threadpool;

// Function prototypes for thread pooling
threadpool 	threadpool_create(int number_of_threads);
void		threadpool_add_work(threadpool tp, 
			void (*work_fn)(void *), 
			void * arg);
void 		threadpool_delete(threadpool tp);
void		*threadpool_work_handler(threadpool tp);

#endif
