#ifndef CP_H
#define CP_H

#include "general.h"

int comparation(char *full,char *unfinished);
int copyPaste(char *oldArq,char *newArq);
int cpComplete(char type,char *copy,char *R,char *paste);
void cpRedirector(char *command);

#endif
