#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "process.h"

// Constants.
#define SLEEP_TIME 0

// Main Scheduler struct.
typedef struct {
  _process *wait_list;	// The wait list (for io).
  _process *proc_arr;	// The list of all processes.
  int wait_cur_pos;	// Cursor position in wait_list.
  int n; 		// Number of active processes.
  int created;		// Number of processes created.
} _scheduler;


// Function definitions.
_scheduler *scheduler_init(_process *proc_arr);
void scheduler_begin(_scheduler *scheduler);
void scheduler_age_step(_scheduler *scheduler);
int  execute_next_process (_scheduler *scheduler);
void proc_running_step(_scheduler *scheduler, _process *running);
void proc_waiting_step(_scheduler *scheduler, _process *waiting);
void proc_ready_step  (_scheduler *scheduler, _process *ready);
void sort(_process *proc_arr, int len);

#endif
