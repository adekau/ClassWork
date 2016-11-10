Alex Dekau
Assignment 4
CS4540
10/30/2016

How to run:
	make
	./a4

Comments:
	The assignment specification says to give up semaphores using sem_close(), however,
	sem_close completely closes the semaphore for the current process. Instead, I used
	sem_post which is the function, according to the man pages, that is intended to
	release a semaphore.
	
	The assignment specification also says to release the two semaphores if the user
	inputs Q, but does not mention doing so otherwise. Not doing so otherwise results in
	a single-thread deadlock because the current thread holds both semaphores and when it
	attempts move to the next loop iteration, it will never get past the first sem_wait()
	because it currently owns both of those semaphores. My program releases both of the
	semaphores regardless of the user entering Q or something else.

References:
	[1] http://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
	    For help making a function to randomly generate a string for the semaphore names.

	[2] http://pubs.opengroup.org/onlinepubs/7908799/xsh/time.h.html
	    For help with the sem_timedwait function and how to correctly define the timespec
	    struct.

	[3] http://stackoverflow.com/questions/3295884/malloc-and-scanf
	    Help with getting user input. Couldn't remember if scanf allocates memory or not.
