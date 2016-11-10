#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef SHELL_H
#define SHELL_H

// Prototypes
char *getUserInput(void);
void  setRedirectCommandType(char * cmd, unsigned int i);
void  processCommands(unsigned int i);
int   pipe_cmd(char **argv, int prev_stdin, int first, int last);
int   makeargv(char * s, char * delimiters, char ***argvp);
void  execCommand(char * cmd);
int   redirect(int redirect_type, int prev_stdin, char ** argv, char * filename);

//Typedefs
typedef struct {
  char   commandType;
  char * cmd;
} command;

// Defines
#define LINEMAX 				8192
#define CWDMAX					1024
#define MAXCOMMANDS				100
#define CMDTYPE_REDIRECT_IN  	0
#define CMDTYPE_REDIRECT_OUT 	1
#define CMDTYPE_REDIRECT_BOTH	2
#define CMDTYPE_PIPE         	3
#define CMDTYPE_SINGLE_CMD		4
#define REDIRECT_STDOUT			0
#define REDIRECT_STDIN			1
#define READ 					0
#define WRITE					1

#endif
