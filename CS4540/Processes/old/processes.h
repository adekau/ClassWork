#ifndef __PROCESSES_H
#define __PROCESSES_H
#define ORDER_STDIN_FIRST  0
#define ORDER_STDOUT_FIRST 0
#define STRLEN	256

typedef struct {
	sem_t *sem_in;
	sem_t *sem_out;
	char  *SEM_IN;
	char  *SEM_OUT;
	struct timespec *semtw;
} _shared_data;

typedef struct {
	int in;
	int out;
} _wait_result;

void work_handler(_shared_data *data, int id);
char *rand_string(int len);
void sigint_h(int sig);
_wait_result *get_two_semaphores(_shared_data *data, char order);

#endif
