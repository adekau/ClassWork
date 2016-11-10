#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "process.h"
#include "scheduler.h"


int main () {
  _process proc_arr[NUM_PROCESSES];

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
