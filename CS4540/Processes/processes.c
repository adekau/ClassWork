/* Processes Assignment
 * Alex Dekau
 * CS 4540
 * 11/7/2016
 * More information about the assignment and references can be found in the README.txt
 */

#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include "processes.h"

/* Main Function
 * Handles the creation of shared resources for the processes and children processes.
 */
int main (int argc, char **argv) {
	// Create the shared data struct.
	_shared_data *sd = malloc(sizeof(*sd));
	int i = 0, status = 0;
	pid_t fork_results[4], wpid;

	// Create the two semaphores for STDIN and STDOUT.
	// O_CREAT: Create the named semaphore if it doesn't exist.
	// S_IRWXU: Read/write/execute permissions for the owner.
	if ((sd->sem_in = sem_open(C_SEM_IN, O_CREAT, S_IRWXU, 1)) == SEM_FAILED) perror("Create In");
	if ((sd->sem_out = sem_open(C_SEM_OUT, O_CREAT, S_IRWXU, 1)) == SEM_FAILED) perror("Create Out");

	// Need 4 processes. Fork the process 4 times.
	for (; i < 4; i++) {
		fork_results[i] = fork();
		if (fork_results[i] > 0) {
			// PARENT STUFF
		} else if (!fork_results[i]) {
			// CHILD STUFF
			work_handler(sd, i);
			exit(0);
		} else {
			perror("Fork");
		}
	}
	// Handle signal interrupt (CTRL-C) and gracefully quit.
	if (signal(SIGINT, sigint_h) == SIG_ERR) perror("Signal error");

	// Wait for all child processes to finish.
	while ((wpid = wait(&status)) > 0);

	// Threads are finished. Safe to close the semaphore file descriptor.
	if (sem_close(sd->sem_in)) perror("Close In");
	if (sem_close(sd->sem_out)) perror("Close Out");

	// Semaphore file descriptors are closed, unlink them.
	if (sem_unlink(C_SEM_IN)) perror("Unlink In");
	if (sem_unlink(C_SEM_OUT)) perror("Unlink Out");
	
	return EXIT_SUCCESS;
}


/* WORK_HANDLER
 * Function that will be executed by the children processes.
 */
void work_handler (_shared_data *data, int id) {
	_wait_result *waits;
	char *str = malloc(sizeof(*str) * STRLEN);

	while (1) {
		// Depending on the ID of the process, get the two semaphores in a specific order.
		// Two processes get STDIN first, other two get STDOUT first.
		if (id < 2) {
			waits = get_sems(data->sem_in, data->sem_out);
		} else {
			waits = get_sems(data->sem_out, data->sem_in);
		}

		// If one of them fails to get the semaphore. (returns -1).
		if (waits->first || waits->second) {
			// THERE IS A DEADLOCK! Find which semaphore this thread holds and release it.
			if (!waits->first) sem_post(waits->s_first);
			if (!waits->second) sem_post(waits->s_second);
		} else {
			// No Deadlock. Safe to start using STDIN and STDOUT for user interaction.
			printf("Process %d has the two semaphores.\n", id + 1);
			puts("Enter something, or press type Q to quit.");
			// Read input from stdin and store it in the str variable.
			fscanf(stdin, "%s", str);
			if (!strcmp(str, "Q")) {
				// User wants to quit the thread, give up the semaphores and return.
				if (sem_post(data->sem_in)) perror("Post In");
				if (sem_post(data->sem_out)) perror("Post Out");
				exit(EXIT_SUCCESS);
			} else {
				// User does not want to quit, print the input and give up semaphores.
				// Semaphores must be given up here, or else it will self-deadlock in
				// the next iteration of the loop because both semaphores are held and
				// it will never get past the first sem_wait.
				fprintf(stdout, "Process %d: %s\n", id + 1, str);
				if (sem_post(data->sem_in)) perror("Post In");
				if (sem_post(data->sem_out)) perror("Post Out");
			} // END ELSE OF STRCMP
		} // END OF DEADLOCK IF STATEMENT
	} // END OF WHILE LOOP.
}


/* GET_SEMS
 * Get the two semaphores based on the order given.
 * 
 * Breaking deadlocks:
 * Using sem_timedwait here because if there's a deadlock (1 process has
 * stdin and another has stdout) then those processes that hold those two
 * semaphores would infinitely wait on the next sem_wait because both
 * semaphores are taken. Sem_timedwait will cancel the wait if it goes past
 * whatever is defined in a timespec struct. This will allow the breaking of
 * the deadlock later in the code.
 */
_wait_result *get_sems (sem_t *first, sem_t *second) {
	_wait_result *ret = malloc(sizeof(*ret));
	struct timespec *semtw = malloc(sizeof(*semtw));
	semtw->tv_nsec = TIMEDWAIT_DELAY;

	ret->s_first = first;
	ret->s_second = second;

	ret->first  = sem_wait(first);
	ret->second = sem_timedwait(second, semtw);

	return ret;
}


/* SIGINT_H
* Signal handler for SIGINT (CTRL-C). When the user tells the program to stop before
* it finishes, gracefully unlink the semaphores and quit.
*/
void sigint_h (int sig) {
	if (sig == SIGINT) {
		if (sem_unlink(C_SEM_IN)) perror("Unlink In");
		if (sem_unlink(C_SEM_OUT)) perror("Unlink Out");
		exit(EXIT_SUCCESS);
	}
}
