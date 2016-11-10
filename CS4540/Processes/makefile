# Processes Assignment
# Alex Dekau
# CS 4540
# 11/7/2016
# More information about the assignment and references can be found in the README.txt

OUTPUT = pr
INPUT = processes.o
GCCFLAGS = -pthread -Wall -std=gnu11 -Wpedantic

pr : processes.o
	gcc -o ${OUTPUT} ${INPUT} ${GCCFLAGS}
processes.o : processes.c processes.h
	gcc -c processes.c ${GCCFLAGS}

clean :
	rm ${OUTPUT} ${INPUT}
