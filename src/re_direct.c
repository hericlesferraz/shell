#include "../include/general.h"

void outputCases(char *firstCommandCase, char *outputFile);

pid_t  pid;

int inputOutput(char *buff)
{
    int i = 0;
	for(i=0;buff[i]!='\0';i++){}
    char *tokenCommand = (char *)malloc(sizeof(tokenCommand));
    char *tokenTemporary = (char *)malloc(sizeof(char)*i);
    char **args = malloc(80 * sizeof(char *));
    char *nameOutput = malloc(80 * sizeof(char *));;   
    char *cp;
    char *prog = (char *)malloc(sizeof(char)*i);
    strcpy(prog,buff);
    strcpy(tokenTemporary,buff);
    
    args[i] = NULL; 
    i = 0;
    for(;;) 
    {
        tokenCommand = strtok((i == 0) ? tokenTemporary : NULL, " \t\n");
        if (tokenCommand == NULL)
            break;
        args[i++] = tokenCommand;
        cp = args[i++];

    }
    
    int count = 0;
    int countPipe = 0;
    int response = 0;
    bool firstLoop = false;

    for(int count = 0; count < i; count++)
    {   
        if(!firstLoop)
        {
            if (strcmp (args[count], ">") == 0)
            {
                //printf("tem o > : ");
                response = 1;
                firstLoop = true;
            }
            else if (strcmp (args[count], ">>") == 0)
            {
                //printf("tem o >> :");
                response = 2;
                firstLoop = true;

            }        
            else if (strcmp (args[count], "<") == 0)
            {
                //printf("tem o < :");
                response = -1;
                firstLoop = true;
            }
            else
            {
                response = 0;
            }
        }
        strcpy(nameOutput, args[count]);
        count++; 
    }

    if(response != 0)
    {
        int response_pid = 0;
        response_pid = fork(); 
        if (response_pid < 0) 
        {     /* fork a child process           */
            printf("*** ERROR: forking child process failed\n");
            exit(1);
        }
        else if (response_pid == 0) 
        {   
            int redirect_fd = 0;

            if(response == 1) // Caso >
            {
                redirect_fd = open(nameOutput, O_CREAT | O_TRUNC | O_WRONLY, 0777);
                i =0;
                if(redirect_fd == -1)   printf("error /n");
                dup2(redirect_fd, STDOUT_FILENO); 
                close(redirect_fd);
                outputCases(args[0],nameOutput);
                signal(SIGINT, SIG_DFL);
                exit(0);
            }

            else if(response == 2) // Caso >>
            {
                redirect_fd = open(nameOutput, O_WRONLY|O_APPEND|O_CREAT, 0777);
                i =0;
                if(redirect_fd == -1)   printf("error /n");
                dup2(redirect_fd, STDOUT_FILENO);
                close(redirect_fd);
                outputCases(args[0],nameOutput);
                signal(SIGINT, SIG_DFL);
                exit(0);
            }

            else if(response == -1) // Caso <
            {
                char readArchive;
                FILE *output;
                 for(i=0;prog[i]!='\0'&& prog[i]!='<';i++){}
                if(prog[i]=='<')
                prog[i]='\0';
                else
                i=0;
                
                if( (output=fopen(nameOutput,"r"))==NULL ) {
                    printf("shell: no such file or directory: %s\n\n", nameOutput);                    
                    exit(1);
                }

                 while( 1 ) {
                if(i!=0)
                 prog = realloc(prog, (i+1) * sizeof(char));
                    readArchive = fgetc(output);
                    if( feof(output) ){
                    if(i!=0){
                    prog[i] = '\0';
                    strcpy(buff,prog);
                    response = 0;
                    }
                    free(prog);
                        break;
                    }
                    if(i==0)
                    putchar(readArchive);
			else{
                    prog[i] = readArchive;
                     i++;
                     }
                    
                }
                fclose(output);
            }
        }
        else{
    	int z;
    	wait(&z);
    	}
    }
         
    return (response);
}

void outputCases(char *firstCommandCase, char *outputFile)
{
    int commandCase = 0;

    if (strcmp (firstCommandCase, "cd") == 0)
    {
        commandCase = 1;
    }
    
    else if (strcmp (firstCommandCase, "cp") == 0)
    {
        commandCase = 2;
    }
    
    else if (strcmp (firstCommandCase, "ls") == 0)
    {
        commandCase = 3;
    }
    
    else if (strcmp (firstCommandCase, "mkdir") == 0)
    {
        commandCase = 4;
    }
    
    else if (strcmp (firstCommandCase, "pwd") == 0)
    {
        commandCase = 5;
    }
    
    else if (strcmp (firstCommandCase, "rmdir") == 0)
    {
        commandCase = 6;
    }

    else if (strcmp (firstCommandCase, "<") == 0)
    {
        commandCase = 7;
    }

    else
    {
        printf("shell: command not found: %s", firstCommandCase);
    }

    switch (commandCase)
    {
        case (3):
            listDirectory("", ".");
        break;

        case (5):
            readDirectory(1);
        break;

        case (7):
            //readDirectory(1);
        break;

        default:
            printf("Fora dos casos /n");
            break;
    }
}