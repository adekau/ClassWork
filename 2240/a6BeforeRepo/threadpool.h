#ifndef __thread_pool_H
#define __thread_pool_H

// A linked-list of requests to handle.
typedef struct _request {
	void 	(*request_handler)(void *);
	void 	*request_arg;
	struct 	_request *next_request;
} request;

typedef struct _threadpool {
	int 		num_threads; 	// The number of threads in the pool
	pthread_t 	*threads;	// Pointer to the threads in the pool.
	int 		queue_size;	// The number of items in the work queue
	request 	*queue_head; 	// A pointer to the queue head
	request 	*queue_tail; 	// A pointer to the queue tail
	pthread_mutex_t request_queue_lock; // Mutex lock to prevent data race on queue
	pthread_cond_t  work_avail;	// Condition that broadcasts if there is work
	pthread_cond_t  no_work;	// Condition that broadcasts if there is no work
	int		deleting;	// Whether or not to pause work.
} threadpool;

// Function signature used for the requests in the request queue.
typedef void (*send_request)(void *);

void 	   *handle_request(void *tp);
void 	   *threadpool_create(int numthreads);
void        threadpool_add_request(void *tp, send_request req, void *arg);
void	    threadpool_delete(void *tp);

#endif
