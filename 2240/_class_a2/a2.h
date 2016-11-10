#ifndef A2_H
#define A2_H

// Defines used by both programs
#define NUM_COUNTRIES 300
#define BUFFER_SIZE 1000
#define CODE_SIZE 3

// Typedef struct used by both programs.
typedef struct {
    char    code[4];
    ssize_t offset;
} cDirectory;

#endif
