#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define STRLEN  256
char *SEM_IN, *SEM_OUT;

// pt_handler function
void pt_handler (void *id);
// rand_string function
char *rand_string(int len);
// sigint handler
void sigint_h(int sig);

// Semaphores to use for assignment.
sem_t *sem_in, *sem_out;

int main (int argc, char **argv) {
	if (signal(SIGINT, sigint_h) == SIG_ERR) perror("Signal err");
	// Declare the pthreads and their IDs.
	pthread_t pt1, pt2, pt3, pt4;
	int pt_ids[4] = {1, 2, 3, 4};

	SEM_IN = rand_string(48);
	SEM_OUT = rand_string(48);
	printf("Generated random names for the two semaphores:\nSEM_IN:  %s\nSEM_OUT: %s\n", SEM_IN, SEM_OUT);
	
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

	puts("Threads finished. Unlinking semaphores.");

	// Threads are finished. Safe to close the semaphore file descriptor.
	if (sem_close(sem_in)) perror("Closing In");
	if (sem_close(sem_out)) perror("Closing Out");
	
	// Semaphore file descriptors are closed, unlink them.
	if (sem_unlink(SEM_IN)) perror("Unlinking In");
	if (sem_unlink(SEM_OUT)) perror("Unlinking Out");

	return 0;
}

void sigint_h (int sig) {
	if (sig == SIGINT) {
		if (sem_unlink(SEM_IN)) perror("Unlinking In");
		if (sem_unlink(SEM_OUT)) perror("Unlinking Out");
		exit(1);
	}
}

void pt_handler (void *id) {
	int thread_id = *((int *) id);
	char *str = malloc(sizeof(*str) * STRLEN);
	struct timespec *semtw = malloc(sizeof(*semtw));
	semtw->tv_nsec = 100000000;
	int stdinwait, stdoutwait;

	while (1) {
		if (thread_id < 2) {
			stdinwait = sem_wait(sem_in);
			stdoutwait = sem_timedwait(sem_out, semtw);
		} else {
			stdoutwait = sem_wait(sem_out);
			stdinwait = sem_timedwait(sem_in, semtw);
		}

		if (stdinwait || stdoutwait) {
			// THERE IS A DEADLOCK! Find which semaphore this thread holds and release it.
			if(!stdinwait) sem_post(sem_in);
			if(!stdoutwait) sem_post(sem_out);
		} else {
			printf("Thread %d has the two semaphores.\n", thread_id);
			puts("Enter something, or press type Q to quit.");
			fscanf(stdin, "%s", str);
			if (!strcmp(str, "Q")) {
				if (sem_post(sem_in)) perror("Post In");
				if (sem_post(sem_out)) perror("Post Out");
				return;
			} else {
				fprintf(stdout, "Thread %d: %s\n", thread_id, str);
				if (sem_post(sem_in)) perror("Post In");
				if (sem_post(sem_out)) perror("Post Out");
			} // END ELSE OF STRCMP
		} // END ELSE OF STDINWAIT
	} // END WHILE LOOP

}

// Generate a random string of length "len". 
// Conforms to the POSIX standard for semaphore names
// 	- Start with a '/'
// 	- Null terminator
// 	- <= 251 length.
char *rand_string(int len) {
	static int seed = 0xAFB;
	char *available = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	size_t n = strlen(available);
	srand(time(NULL) * len + ++seed);
	if (len < 1) len = 1;
	if (len > 251) len = 250;
	char *str = malloc(sizeof(*str) * (len + 2));
	if (str) {
		short key = 0;
		int i = 1;
		str[0] = '/';
		for (; i < len; i++) {
			key = rand() % n;
			str[i] = available[key];
		}
		str[len - 1] = '\0';
		return str;
	} else {
		puts("Out of memory");
		exit(1);
	}
}

