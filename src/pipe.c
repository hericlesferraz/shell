#include "../include/pipe.h"

int pipeCommand(char *buffer)
{
	int i, commandCounter=0, pipeCount=0, status;
	pid_t pid;
	char **args;
	for (i = 0; buffer[i]!='\0'; i++) 
    {
		if(i>0)
		{
			if(buffer[i]=='|' && buffer[i+1]!='|' && buffer[i-1]!='|')
			{
				pipeCount++;
				//printf("pipeCount \n", pipeCount);
			}
		}
	}
	if(pipeCount == 0)
	{
		//printf("sem pipes \n");
		return 0;
	}
	int* pipefds=(int*)malloc((2*pipeCount)*sizeof(int));
	char* token=(char*)malloc((128)*sizeof(char));
	
	token=strtok_r(buffer,"|",&buffer);
	for( i = 0; i < pipeCount; i++ ){	
    		if( pipe(pipefds+i*2) < 0 )
			{
				perror("pipe creation failed");
				return 3;
			}
	}
	do{
	    pid = fork();
	    if(pid == 0)
		{
			//Processo Filho
	        if(commandCounter!=0 )
			{
	           	if( dup2(pipefds[(commandCounter-1)*2], 0) < 0)
				{
					printf("Erro no Processo Filho \n");
					exit(1);
				}
        	}
        	if(commandCounter!= pipeCount){
            		if(dup2(pipefds[commandCounter*2+1], 1) < 0 )
					{
						printf("Erro no Processo Filho \n");
						exit(1);}
       	 	}
            for( i = 0; i < 2*pipeCount; i++ ){close(pipefds[i]);}
	        args=splitline(token);
            //chooseCommand(line);
            execvp(args[0],args);
            exit(1);
 	    } 
	    else if( pid < 0 )
		{
			perror("fork() failed");
			return 3;
		}
		else if(pid > 0)
		{
			//int i;
			if ((status&255) == 0) 
				exit(0);//
				//wait(&status);	
			//else
		}
		
		commandCounter++;
	}

	while(commandCounter<pipeCount+1 &&(token=strtok_r(NULL,"|",&buffer)));
	for( i = 0; i < 2*pipeCount; i++ ){close(pipefds[i]);}
	free(pipefds);
	return 1;
}

char **splitline(char *buffer)
{
  printf("split");
  int bufsize = MAXARGNUM, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "dynamic memory allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(buffer, DELIMITER);
  while (token != NULL) 
  {
    if(token[0] =='*'||token[strlen(token)-1] =='*')
	{
		DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if (d) 
		{
			while ((dir = readdir(d)) != NULL) 
			{
				if(dir->d_name[0]!='.')
				{
					if(strlen(token) == 1 || (token[0] == '*' && (!strncmp(token+1,(dir->d_name+strlen(dir->d_name)-strlen(token)+1),strlen(token)-1)))||(token[strlen(token)-1]=='*'&&(!strncmp(token,dir->d_name,strlen(token)-1)))){
					tokens[position] = dir->d_name;
					position++;
					}
				}
			}
			closedir(d);
		}
	}
    else{tokens[position] = token;
    position++;}

    if (position >= bufsize) {
      bufsize += MAXARGNUM;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
    	if (!tokens) 
		{
			free(tokens_backup);
			exit(EXIT_FAILURE);
        }
    }
    token = strtok(NULL, DELIMITER);
}
tokens[position] = NULL;
return tokens;
}