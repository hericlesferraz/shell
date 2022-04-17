#ifndef PIPE_H
#define PIPE_H

#include "general.h"
#define DELIMITER " \t\r\n\a"
#define MAXARGNUM 32

char **splitline(char *buffer);
int pipeCommand(char *buffer);

#endif
