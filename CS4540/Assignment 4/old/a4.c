#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define STRLEN  256
#define SEM_IN  "a4in7"
#define SEM_OUT "a4out7"

// pt_handler function
void pt_handler (void *id);

// Semaphores to use for assignment.
sem_t *sem_in, *sem_out;

int main (int argc, char **argv) {
	// Declare the pthreads and their IDs.
	pthread_t pt1, pt2, pt3, pt4;
	int pt_ids[4] = {1, 2, 3, 4};
	
	// Create the two semaphores for STDIN and STDOUT.
	if ((sem_in = sem_open(SEM_IN, O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) perror("Create In");
	if ((sem_out = sem_open(SEM_OUT, O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) perror("Create Out");

	// Create the four threads. Not bothering with a loop since there's only 4.
	if (pthread_create(&pt1, NULL, (void *) &pt_handler, (void *) &pt_ids[0])) perror("Thread 1");
	if (pthread_create(&pt2, NULL, (void *) &pt_handler, (void *) &pt_ids[1])) perror("Thread 2");
	if (pthread_create(&pt3, NULL, (void *) &pt_handler, (void *) &pt_ids[2])) perror("Thread 3");
	if (pthread_create(&pt4, NULL, (void *) &pt_handler, (void *) &pt_ids[3])) perror("Thread 4");

	// Wait for each thread to finish.
	if (pthread_join(pt1, NULL)) perror("PT1 join");
	if (pthread_join(pt2, NULL)) perror("PT2 join");
	if (pthread_join(pt3, NULL)) perror("PT3 join");
	if (pthread_join(pt4, NULL)) perror("PT4 join");

	// Threads are finished. Safe to close the semaphore file descriptor.
	if (sem_close(sem_in)) perror("Closing In");
	if (sem_close(sem_out)) perror("Closing Out");
	
	// Semaphore file descriptors are closed, unlink them.
	if (sem_unlink(SEM_IN)) perror("Unlinking In");
	if (sem_unlink(SEM_OUT)) perror("Unlinking Out");

	return 0;
}

void pt_handler (void *id) {
	int thread_id = *((int *) id);
	char *str = malloc(sizeof(*str) * STRLEN);
	while (1) {
		if (thread_id < 2) {
			if (sem_wait(sem_in)) perror("Wait In");
			if (sem_trywait(sem_out)) perror("Wait Out");
		} else {
			if (sem_wait(sem_out)) perror("Wait Out");
			if (sem_trywait(sem_in)) perror("Wait In");
			
		}
		printf("Thread %d has the two semaphores.\n", thread_id);
		puts("Enter something, or press type Q to quit.");
		fscanf(stdin, "%s", str);
		if (!strcmp(str, "Q")) {
			if (sem_post(sem_in)) perror("Post In");
			if (sem_post(sem_out)) perror("Post Out");
			return;
		} else {
			fprintf(stdout, "Thread %d: %s\n", thread_id, str);
		}
	}

}
