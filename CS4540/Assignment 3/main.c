#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.h"
#include "scheduler.h"


int main () {
  _process proc_arr[NUM_PROCESSES];
  _process *test;
  int a = 0;
  char pname[50];
  int i;

  for (i = 0; i < NUM_PROCESSES; i++) {
    sprintf(pname, "Process%d", i + 1);
    test = process_init(pname, &a);
    proc_arr[i] = *test;
    usleep((useconds_t)100);  	// Do not create all processes at once. 
				// let the algorithm run a few times.
  }


  // Now create scheduler
  _scheduler *cpu = scheduler_init(proc_arr);
  scheduler_begin(cpu);
}

/* -sort----------------------------------------------------------------------------
 * Uses the bubble sort algorithm to sort a process list.
 * -PARAMS:
 *   proc_arr: The process list.
 *   len     : The length of the process list (number of processes).
 * --------------------------------------------------------------------------------*/
void sort (_process *proc_arr, int len) {
  int i, j;
  for (j = 0; j < len - 1; j++) {
    for (i = 0; i < len - 1; i++) {
      if (proc_arr[i].priority < proc_arr[i+1].priority) {
        _process tmp = proc_arr[i];
        proc_arr[i] = proc_arr[i+1];
        proc_arr[i+1] = tmp;
      }
    }
  }
}
