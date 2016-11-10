GCCPARAMS = -std=gnu11 -Wpedantic -Wall
OBJECTS = main.o process.o scheduler.o
NAME = sim

${NAME} : ${OBJECTS}
	gcc ${OBJECTS} -o ${NAME}

debug : ${OBJECTS}
	gcc -g ${OBJECTS} -o ${NAME}

main.o : main.c 
	gcc -c main.c ${GCCPARAMS}

process.o : process.c process.h
	gcc -c process.c ${GCCPARAMS}

#lib3.o: lib3.c lib3.h 
#	gcc -c lib3.c ${GCCPARAMS}

scheduler.o : scheduler.c scheduler.h
	gcc -c scheduler.c ${GCCPARAMS}

clean :
	rm *.o ${NAME}
