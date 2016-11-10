#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "opts.h"

/* -Constants-----------------------------------------------------------------------
 * --------------------------------------------------------------------------------*/
const int cpu_times[NUM_PROCESSES] = {17,10,22,5,30,11,29,5,17,6,18,7,23};
const int io_times[NUM_PROCESSES] = {5,19,7,26,5,19,7,22,10,21,8,29,3};
const int iterations[NUM_PROCESSES] = {10,14,22,17,11,30,28,20,11,12,16,14,13};

/* -process_init--------------------------------------------------------------------
 * Creates a new process and assigns values based on hard set values.
 * -PARAMS:
 *   name: Name of the process.
 *   cur : Integer pointer for keeping track of the next process number to make.
 * --------------------------------------------------------------------------------*/
_process *process_init (char *name, int *cur) {
  _process *ret = malloc(sizeof(*ret));
  strncpy(ret->name, name, 50);
  ret->start_priority = ret->priority = *cur / 3;
  ret->cpu_cycles = cpu_times[*cur];
  ret->io_cycles = io_times[*cur];
  ret->iterations = iterations[*cur];
  ret->start_iter = iterations[*cur];
  ret->state = STATE_READY;
  ret->cpu_time = cpu_times[*cur];
  ret->io_time_left = io_times[*cur];
  ret->ready_time = 0;
  ret->cpu_total = 0;
  ret->io_total = 0;
  ret->ready_total = 0;
  ret->ready_smallest = 32767;
  ret->ready_biggest = 0;

  ++*cur;
  return (_process *) ret;
}
