#pragma once
#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>    
#include <sys/stat.h>  
#include <sys/types.h> 
#include <dirent.h>
#include <assert.h>
#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <signal.h>
#include <fcntl.h>
#include <ncurses.h>
#include <sys/wait.h>
#include <ncurses.h>


#include<time.h>
#include<sys/sysmacros.h>
#include<stdint.h>
#include<pwd.h>
#include<grp.h>


#define MEM_SZ 4096
#define PWD_SZ MEM_SZ-sizeof(sem_t)-sizeof(int)

#define MAX 12
#define MAX_DIR_NAME 256

#define NORMAL_COLOR	"\x1B[0m"
#define GREEN		"\x1B[32m"
#define BLUE		"\x1B[34m"
#define RED		"\x1b[31m" 
#define GRAY     	"\e[0;37m"


#endif
