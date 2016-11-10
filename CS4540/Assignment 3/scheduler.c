#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "scheduler.h"
#include "process.h"

/* -Constants-----------------------------------------------------------------------
 * --------------------------------------------------------------------------------*/

/* -scheduler_init------------------------------------------------------------------
 * Allocates memory for a scheduler struct and presets variables based on constants.
 * --------------------------------------------------------------------------------*/
_scheduler *scheduler_init (_process *proc_arr) {
  _scheduler *scheduler = malloc(sizeof(*scheduler));
  scheduler->proc_arr = proc_arr;
  // Set up wait list for I/O.
  _process *wait = malloc(sizeof(*wait) * NUM_PROCESSES);
  scheduler->wait_list = wait;
  scheduler->wait_cur_pos = 0;
  scheduler->n = NUM_PROCESSES;
  scheduler->created = 0;
  return (_scheduler *)scheduler;
}


/* -scheduler_begin-----------------------------------------------------------------
 * The main loop of the scheduler. Keeps track of iterators defined in the scheduler
 * struct. When these iterators hit 0, it calls a function related to that iterator.
 * --------------------------------------------------------------------------------*/
void scheduler_begin (_scheduler *scheduler) {
  // VARIABLES
  int i, j; 			// For Loop Variables
  //_process *running = NULL; 	// For storing the current running process.
				// for in case it's needed.
  _process *cur_proc = NULL;    // For statistics loop when processes finish.

  // Check for there being a process at the top of the queue.
  if (!execute_next_process(scheduler)) {
    fprintf(stderr, "Error. No process in the priority queue.");
  }

  // Main scheduling loop. Loop through each process and branch off depending on state.
  while(scheduler->n > 0) {

    for (j = 0; j < NUM_PROCESSES; j++) {
      short state = scheduler->proc_arr[j].state;

      switch (state) {
	case STATE_READY:
	  proc_ready_step(scheduler, &(scheduler->proc_arr[j]));
   	  break;
	case STATE_RUNNING:
	  proc_running_step(scheduler, &(scheduler->proc_arr[j]));
	  break;
	case STATE_WAITING:
	  proc_waiting_step(scheduler, &(scheduler->proc_arr[j]));
	  break;
	default:
	  break;
      }

    }

    // Slow the program down by sleeping for SLEEP_TIME (scheduler.h) nanoseconds.
    usleep((useconds_t) SLEEP_TIME);
  }

  // All processes have finished. Time to show some statistics.
  printf("\n\nProcesses have finished. Statistics:");
  printf("\n---------------------------------------\n\n");
  for (i = 0; i < NUM_PROCESSES; i++) {
    cur_proc = &(scheduler->proc_arr[i]);
    printf("%d: %s: --------------------\n", i, cur_proc->name);
    printf("CPU Total: %d\nIO Total: %d\nReady Total: %d\n",
      cur_proc->cpu_total, cur_proc->io_total, cur_proc->ready_total);
    printf("Ready Biggest: %d\nReady Smallest: %d\nReady Average: %f\n",
      cur_proc->ready_biggest, cur_proc->ready_smallest,
      ((float)cur_proc->ready_total / (float)cur_proc->start_iter));
  }
}


/* -scheduler_age_step-------------------------------------------------------------
 * Loops through each member of the process list and increments their priorities by 1.
 * --------------------------------------------------------------------------------*/
void scheduler_age_step (_scheduler *scheduler) {
  _process *proc = scheduler->proc_arr;
  int i;
  short priority = 0;
  short state = 0;
  //printf("%s\n", "Running age step on everything...");

  for (i = 0; i < NUM_PROCESSES; i++) {
    priority = proc[i].priority;
    state = proc[i].state;
    if (state == STATE_READY) {
      if (priority >= 15) {
        proc[i].priority = proc[i].start_priority;
      } else {
        ++proc[i].priority;
      }
    }
  }
}


/* -execute_next_process------------------------------------------------------------
 * Takes the next process from the priority queue and sets its state to running.
 * -PARAMS:
 *   scheduler: The scheduler which contains the runtime iterators and process list.
 *   running: A _process pointer to be set.
 * --------------------------------------------------------------------------------*/
int execute_next_process (_scheduler *scheduler) {
  int i;
  // Sort the queue first.
  sort(scheduler->proc_arr, NUM_PROCESSES);

  for (i = 0; i < NUM_PROCESSES; i++) {
    if (scheduler->proc_arr[i].state == STATE_READY) {
      _process *running = &(scheduler->proc_arr[i]);
      running->state = STATE_RUNNING;
      scheduler_age_step(scheduler);
      printf("%s is now running.\n", running->name);
      return 1;
    } else {
      continue;
    }
  }

  return 0;
}


/* -proc_running_step---------------------------------------------------------------
 * Deals with a running process. Handles movement of a running process to other
 * states. Also increments any informative values.
 * --------------------------------------------------------------------------------*/
void proc_running_step(_scheduler *scheduler, _process *running) {
  // Check for smallest/biggest ready_time.
  if (running->ready_time > running->ready_biggest) {
    running->ready_biggest = running->ready_time;
  }

  if (running->ready_time < running->ready_smallest) {
    running->ready_smallest = running->ready_time;
  }

  // Check if the cpu_time (down-counting) is not 0. If it is, decrement. If not,
  // Then the process is ready to be kicked out of the cpu and go to waiting.
  if (running->cpu_time > 0) {
    --running->cpu_time;
    ++running->cpu_total;
  } else {
    // Kick the process out of CPU and into wait.
    scheduler->wait_list[scheduler->wait_cur_pos++] = *running;
    running->state = STATE_WAITING;
    running->priority = -1;
    running->cpu_time = running->cpu_cycles;
    running->ready_time = 0;
    printf("%s is now waiting on I/O.\n", running->name);

    
    execute_next_process(scheduler);
  }
}


/* -proc_waiting_step---------------------------------------------------------------
 * Deals with a process waiting for I/O. Handles movement of a waiting process to
 * the ready state.
 * --------------------------------------------------------------------------------*/
void proc_waiting_step(_scheduler *scheduler, _process *waiting) {
  int i;
  if (waiting->io_time_left > 0) {
    --waiting->io_time_left;
    ++waiting->io_total;
  } else {
    for (i = 0; i < scheduler->wait_cur_pos; i++) {
      if (waiting == &(scheduler->wait_list[i])) {
	--scheduler->wait_cur_pos;
      }
    }
    waiting->state = STATE_READY;
    printf("%s finished and going to ready. %d iterations left. %d cpu cycles total, %d io cycles total.\n",
	waiting->name, waiting->iterations, waiting->cpu_total, waiting->io_total);
    waiting->priority = waiting->start_priority;
    waiting->io_time_left = waiting->io_cycles;

    // Check whether the process can continue or needs to get killed (finished).
    if (waiting->iterations > 1) {
      waiting->iterations--;
    } else {
      // Out of iterations. Delete the process.
      waiting->state = STATE_KILLED;
      waiting->priority = -2;
      --scheduler->n;
      printf("%s has finished and has been terminated. %d processes left\n",
	 waiting->name, scheduler->n);
    }

    if (scheduler->n == 1) {
      execute_next_process(scheduler);
    }
  }
}


/* -proc_ready_step-----------------------------------------------------------------
 * Deals with a process in the ready priority queue. Handles statistic gathering
 * with regards to how long the process has been in the ready queue, etc.
 * --------------------------------------------------------------------------------*/
void proc_ready_step(_scheduler *scheduler, _process *ready) {
  ++ready->ready_time;
  ++ready->ready_total;
}
