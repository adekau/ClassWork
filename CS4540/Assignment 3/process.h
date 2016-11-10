#ifndef __PROCESS_H
#define __PROCESS_H

#define NUM_PROCESSES 48
#define STATE_READY   0
#define STATE_RUNNING 1
#define STATE_WAITING 2
#define STATE_KILLED  -1

// Main structure for a process  
typedef struct {
  char name[50]; 	// Name of the process  
  short state;		// Current state of the process. (running,ready,wait)
  short start_priority;	// The static priority. Immutable.  
  short priority;	// The current priority. Mutable.  
  short cpu_cycles;	// total cycles to spend in cpu.  
  short io_cycles;	// total cycles to spend in io.  
  short iterations;	// number of times to go shorto cpu/io  
  short start_iter;	// number of iterations when created.
  short cpu_time;	// time spent in cpu for current control of processor.  
  short io_time_left;	// Time left waiting for current I/O.  
  short ready_time;	// Time waiting in ready queue (current)  
  short cpu_total;	// Total cycles spent in CPU.  
  short io_total;	// Total cycles spent in IO.  
  short ready_total;	// Total time spent in ready queue.  
  short ready_smallest;	// Smallest amnt of time in ready queue.  
  short ready_biggest;	// Biggest amnt of time in ready queue.  
} _process;

_process *process_init (char *name, int *cur);

#endif
