#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "processes.h"

int main (int argc, char **argv) {
	_shared_data *sd = malloc(sizeof(*sd));
	sd->semtw = malloc(sizeof(*(sd->semtw)));
	sd->semtw->tv_nsec = 100000000;
	int i = 0, status = 0;
	pid_t fork_results[4], wpid;

	sd->SEM_IN = rand_string(24);
	sd->SEM_OUT = rand_string(24);
	printf("Generated random names for the two semaphores:\nSEM_IN:  %s\nSEM_OUT: %s\n", sd->SEM_IN, sd->SEM_OUT);

	// Create the two semaphores for STDIN and STDOUT.
	// O_CREAT: Create the named semaphore if it doesn't exist.
	// S_IRWXU: Read/write/execute permissions for the owner.
	if ((sd->sem_in = sem_open(sd->SEM_IN, O_CREAT, S_IRWXU, 1)) == SEM_FAILED) perror("Create In");
	if ((sd->sem_out = sem_open(sd->SEM_OUT, O_CREAT, S_IRWXU, 1)) == SEM_FAILED) perror("Create Out");

	// Need 4 processes. Fork the process 4 times.
	for (; i < 4; i++) {
		fork_results[i] = fork();
		if (fork_results[i] > 0) {
			// PARENT STUFF
			// Don't need to do anything here.
		} else if (!fork_results[i]) {
			// CHILD STUFF
			// Send it to the work_handler.

			//work_handler(sd, i);
			printf("%i\n", i);
			exit(0);
		} else {
			perror("Fork");
		}
	}

	// Wait for all child processes to finish.
	while ((wpid = wait(&status)) > 0);

	// Threads are finished. Safe to close the semaphore file descriptor.
	if (sem_close(sd->sem_in)) perror("Close In");
	if (sem_close(sd->sem_out)) perror("Close Out");

	// Semaphore file descriptors are closed, unlink them.
	if (sem_unlink(sd->SEM_IN)) perror("Unlink In");
	if (sem_unlink(sd->SEM_OUT)) perror("Unlink Out");
}


/* WORK_HANDLER
 */
void work_handler (_shared_data *data, int id) {
	_wait_result *waits;

	while (1) {
		if (id < 2) {
			waits = get_two_semaphores(data, ORDER_STDIN_FIRST);
		} else {
			waits = get_two_semaphores(data, ORDER_STDOUT_FIRST);
		}

		if (waits->in || waits->out) {
			// THERE IS A DEADLOCK! Find which semaphore this thread holds and release it.
			if (!waits->in) sem_post(data->sem_in);
			if (!waits->out) sem_post(data->sem_out);
		} else {
			// No Deadlock
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

		}
	}
}


/* GET_TWO_SEMAPHORES
 */
_wait_result *get_two_semaphores (_shared_data *data, char order) {
	_wait_result *ret = malloc(sizeof(*ret));

	if (order == ORDER_STDIN_FIRST) {
		ret->in = sem_wait(data->sem_in);
		//ret->out = sem_wait(data->sem_out);
		ret->out = sem_timedwait(data->sem_out, data->semtw);
	} else {
		ret->out = sem_wait(data->sem_out);
		//ret->in = sem_wait(data->sem_in);
		ret->in = sem_timedwait(data->sem_in, data->semtw);
	}

	return ret;
}



/* RAND_STRING
 */
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

