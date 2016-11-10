/* Processes Assignment
 * Alex Dekau
 * CS 4540
 * 11/7/2016
 * More information about the assignment and references can be found in the README.txt
 */

#ifndef __PROCESSES_H
#define __PROCESSES_H
#define STRLEN  256
#define C_SEM_IN  "processes_in"
#define C_SEM_OUT "processes_out"
#define TIMEDWAIT_DELAY 100000000

typedef struct {
	sem_t *sem_in;
	sem_t *sem_out;
} _shared_data;

typedef struct {
	sem_t *s_first;
	sem_t *s_second;
	int first;
	int second;
} _wait_result;

void work_handler(_shared_data *data, int id);
void sigint_h(int sig);
_wait_result *get_sems(sem_t *first, sem_t *second);

#endif
