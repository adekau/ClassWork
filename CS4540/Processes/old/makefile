OUTPUT = pr
INPUT = processes.o
GCCFLAGS = -Wall -std=gnu11

pr : processes.o
	gcc -o ${OUTPUT} ${INPUT} ${GCCFLAGS}
processes.o : processes.c processes.h
	gcc -c processes.c ${GCCFLAGS}

clean :
	rm ${OUTPUT} ${INPUT}
