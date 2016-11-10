Alex Dekau
CS4540
10/13/2016

How to run:
1. bash$ make
2. bash$ ./sim

Clean the directory from compiled files:
bash$ make clean

Program was compiled and tested on the CS VPS. (login.cs.wmich.edu).

+-My Scheduling Algorithm:------------------------------------------------------------------------------------------------+
| I did not use an algorithm online, I'm using my own algorithm that attempts to emulate what was described in lecture.   |
| Processes are put into a process list, and the first thing the scheduler does is request the highest priority process   |
| from this list. It does this by sorting the list in descending order by priority. Then it grabs the first index of the  |
| list and sets it's state property to STATE_RUNNING (1). In the while loop of the scheduler, each iteration it loops     |
| through the entire process list and branches with a switch statement to other functions to handle each of the possible  |
| states (ready, running, waiting). 											  |
| After each process enters the running state, a function called age_iter_step() runs which goes through each process	  |
| in STATE_READY and increments their priority by 1. If it reaches PRIORITY_MAX (15) then it resets to the process'	  |
| start priority.													  |
| 															  |
| Running:														  |
| The cpu_time starts at cpu_cycles and decrements by 1 each loop through this function. Once the number reaches 0 the	  |
| scheduler knows that this process is done with cpu and the process moves to STATE_WAITING. It also resets the iter-	  |
| ative properties of the process.											  |
| 															  |
| Waiting:														  |
| The io_time starts at the io_cycls and decrements by 1 each loop through this function. Once the number reaches 0 the	  |
| scheduler knows that the process is done waiting for IO and determines if the process is ready to terminate by checking |
| the iterations property of the process and either decrementing it if it's > 1 or terminating the process otherwise. If  |
| the process is not ready to terminate, the process returns to STATE_READY (0).					  |
| 															  |
| Ready:														  |
| The statistic properties increase with this part of the scheduler. While it's waiting, no processing takes place.	  |
+-------------------------------------------------------------------------------------------------------------------------+

References:
I did not search for algorithms for the scheduling or other parts of this assignment. All ideas with regard to that came 
from the specification website and from lectures.

Here are websites that I used with specific questions on C:
http://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc
http://stackoverflow.com/questions/22924468/sleep-function-in-c11
http://stackoverflow.com/questions/883659/hardcode-byte-array-in-c
