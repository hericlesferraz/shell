#include "../include/cd.h"


int hasPrefix(char const *, char const *);
int cd(char *pth);

#define BUFFERSIZE 10000

void mountPath(char *buff, char * command)
{
    char *dir;
    if(hasPrefix(buff,"cd") == 0)
    {
        dir = strchr(buff,' ');
        if(dir) {
            char *tempCommand = dir + 1;
            dir = tempCommand;
            char *pathConstruct = strchr(dir, '\n');
            if(pathConstruct) {
                *pathConstruct = '\0';
            }
            cd(dir);
        }
    }
}

int hasPrefix(char const *p, char const *q)
{
    int i = 0;
    for(i = 0;q[i];i++)
    {
        if(p[i] != q[i])
            return -1;
    }
    return 0;
}

int cd(char *pth){
    char path[BUFFERSIZE];
    strcpy(path,pth);
    
    //Caso seja apenas "cd "
    if((strlen(pth)==0) || (strcmp(pth,"0")==0) ||( strcmp(pth,"\0")== 0))
    {
        chdir(getenv("HOME"));
    }

    char cwd[BUFFERSIZE];
    if(pth[0] != '/')
    {
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,path);
        if( opendir(cwd) ==  0) 
        { 
            printf("cd: no such file or directory: %s \n", pth);
            
        }

        else
        {
            chdir(cwd);
        }

    }
    return 0;
}
