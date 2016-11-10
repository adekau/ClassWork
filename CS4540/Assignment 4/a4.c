#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

// Maximum string length for user input.
#define STRLEN  256

// Pointers to the names to use for the semaphores.
char *SEM_IN, *SEM_OUT;

// pt_handler function
void pt_handler (void *id);
// rand_string function
char *rand_string(int len);
// sigint handler.
void sigint_h(int sig);

// Semaphores to use for assignment.
sem_t *sem_in, *sem_out;

// Main function
//	- Creates the 4 pthreads.
// 	- Defines their IDs.
// 	- Generates a random string for the named semaphores.
//	- Creates the two semaphores.
//	- Creates the four pthreads.
//	- Waits for all the pthreads to finish.
//	- Closes the semaphore file descriptor.
// 	- Unlinks the semaphore. (Removes from kernel table & /dev/shm).
int main (int argc, char **argv) {
	if (signal(SIGINT, sigint_h) == SIG_ERR) perror("Signal err");
	// Declare the pthreads and their IDs.
	pthread_t pt1, pt2, pt3, pt4;
	int pt_ids[4] = {1, 2, 3, 4};

	SEM_IN = rand_string(48);
	SEM_OUT = rand_string(48);
	printf("Generated random names for the two semaphores:\nSEM_IN:  %s\nSEM_OUT: %s\n", SEM_IN, SEM_OUT);
	
	// Create the two semaphores for STDIN and STDOUT.
	// O_CREAT: Create the named semaphore if it doesn't exist.
	// S_IRWXU: Read/write/execute permissions for the owner.
	if ((sem_in = sem_open(SEM_IN, O_CREAT, S_IRWXU, 1)) == SEM_FAILED) perror("Create In");
	if ((sem_out = sem_open(SEM_OUT, O_CREAT, S_IRWXU, 1)) == SEM_FAILED) perror("Create Out");

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

	return EXIT_SUCCESS;
}

// This is the handler function for the SIGINT (interrupt signal - CTRL+C)
// To not leave semaphores on the system, when it catches this signal it
// unlinks the semaphores opened by this program
void sigint_h (int sig) {
	if (sig == SIGINT) {
		if (sem_unlink(SEM_IN)) perror("Unlinking In");
		if (sem_unlink(SEM_OUT)) perror("Unlinking Out");
		exit(1);
	}
}

// The function that the pthreads are executing.
void pt_handler (void *id) {
	int thread_id = *((int *) id); // Upgrade the void pointer to an int.
	char *str = malloc(sizeof(*str) * STRLEN); // This is for the user input.
	// semtw = Semaphore Timedwait. Used by the sem_timedwait function for declaring
	// how much time it should wait before continuing. Set to 1e8 nanoseconds (1/10th
	// of a second).
	struct timespec *semtw = malloc(sizeof(*semtw));
	semtw->tv_nsec = 100000000;
	// Catch the return values for each of the sem_wait/sem_timedwait functions for
	// stdin and stdout. These will be used for detecting and breaking deadlocks.
	int stdinwait, stdoutwait;

	while (1) {
		// First two threads will attempt to get STDIN, then STDOUT
		if (thread_id < 2) {
			stdinwait = sem_wait(sem_in);
			// Using sem_timedwait here because if there's a deadlock (1 process has
			// stdin and another has stdout) then those processes that hold those two
			// semaphores would infinitely wait on the next sem_wait because both
			// semaphores are taken. Sem_timedwait will cancel the wait if it goes past
			// whatever is defined in a timespec struct. This will allow the breaking of
			// the deadlock later in the code.
			stdoutwait = sem_timedwait(sem_out, semtw);
		// Second two threads will attempt to get STDOUT, then STDIN.
		} else {
			stdoutwait = sem_wait(sem_out);
			stdinwait = sem_timedwait(sem_in, semtw);
		}

		// If one of them failed to acquire the semaphores.(returned -1).
		if (stdinwait || stdoutwait) {
			// THERE IS A DEADLOCK! Find which semaphore this thread holds and release it.
			if(!stdinwait) sem_post(sem_in);
			if(!stdoutwait) sem_post(sem_out);
		// If they both successfully acquired the semaphores. (both returned 0).
		} else {
			printf("Thread %d has the two semaphores.\n", thread_id);
			puts("Enter something, or press type Q to quit.");
			// Read input from stdin and store it in the str variable.
			fscanf(stdin, "%s", str);
			if (!strcmp(str, "Q")) {
				// User wants to quit the thread, give up the semaphores and return.
				if (sem_post(sem_in)) perror("Post In");
				if (sem_post(sem_out)) perror("Post Out");
				return;
			} else {
				// User does not want to quit, print the input and give up semaphores.
				// Semaphores must be given up here, or else it will self-deadlock in
				// the next iteration of the loop because both semaphores are held and
				// it will never get past the first sem_wait.
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
	// Arbitrary seed to use. Does not matter which.
	static int seed = 0xAFB;
	// The characters available to randomly choose from.
	char *available = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	size_t n = strlen(available);
	// Set the seed for the system using a combination of the length of string, and current time.
	srand(time(NULL) * len + ++seed);
	// Length bounds checking..
	if (len < 1) len = 1;
	if (len > 251) len = 250;

	// Allocate memory for the randomized return string. Must be len + 2 since need initial / and null.
	char *str = malloc(sizeof(*str) * (len + 2));
	// Check if memory was allocated correctly.
	if (str) {
		short key = 0;
		int i = 1;
		// POSIX semaphores call for a beginning '/' character on named semaphore names.
		str[0] = '/';
		for (; i < len; i++) {
			key = rand() % n;
			str[i] = available[key];
		}
		// POSIX semaphores call for a null terminator on the end of the named semaphore name.
		str[len - 1] = '\0';
		return str;
	} else {
		puts("Out of memory");
		exit(1);
	}
}

