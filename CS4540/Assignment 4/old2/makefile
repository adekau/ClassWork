OUTPUT = a4
INPUT = a4.o
GCCFLAGS = -pthread

a4 : a4.o
	gcc -o ${OUTPUT} ${INPUT} ${GCCFLAGS}
a4.o : a4.c
	gcc -c a4.c ${GCCFLAGS}

clean :
	rm ${OUTPUT} ${INPUT}
