#pragma once
#ifndef SHELL_H
#define SHELL_H

void *chooseCommand(char *buff);

#include "general.h"

#include "../src/mkdir.c"
#include "../src/pwd.c"
#include "../src/cd.c"
#include "../src/ls.c"
#include "../src/rmdir.c"
#include "../src/exec.c"
#include "../src/stop.c"
#include "../src/cp.c"
#include "../src/re_direct.c"
#include "../src/pipe.c"


//#include "../src/rmdir.c"*/

#endif
