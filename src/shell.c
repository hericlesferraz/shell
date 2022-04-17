#include "../include/shell.h"

void header()
{
    printf("\33[H\33[2J");
    printf("\t\	SHELL 12/2020\n");
    printf("\t\Hericles Felipe Ferraz - 11811EMT022\n\t\Luiz da Silva Moura - 11611EMT028\n\t\Marcus Vinicius Miata - 11811BCC017\n\t\Pedro Henrique Rabis Diniz - 11811BCC024\n");
    printf("\t\--------------------------------------------");

    return;
}

int main()
{
    char *userCommand = (char *)malloc(sizeof(char )+8);

    int i;
	key_t key=1234;
	struct PWD_area *PWD_area_ptr;
	void *PWD_memory = (void *)0;
	int shmid;

	shmid = shmget(key,MEM_SZ,0666|IPC_CREAT);
	if ( shmid == -1 )
	{
		printf("shmget falhou\n");
		exit(-1);
	}
	PWD_memory = shmat(shmid,(void*)0,0);
	
	if (PWD_memory == (void *) -1 )
	{
		printf("shmat falhou\n");
		exit(-1);
	}
	
	PWD_area_ptr = (struct PWD_area *) PWD_memory;
	PWD_area_ptr->PIDexec=0;
	signal(SIGINT, StopProcess);
    readDirectory(0);
    header();
   
    while(1)
    {
        bool flagCommand = 0;     
        while(!flagCommand) 
        {
            printf(BLUE "\n%s:", getenv("USERNAME"), GREEN);
            printf(GREEN "%s",PWD_area_ptr->PWD, NORMAL_COLOR);
            printf(NORMAL_COLOR"\n$ ", NORMAL_COLOR); 
        
            gets(userCommand);
            if((strlen(userCommand)==0) || (strcmp(userCommand,"0")==0)) 
            {
                flagCommand = false;
            }
            else
            {
                break;
            }
        }    

        pipeCommand(userCommand);
        if(inputOutput(userCommand) == 0)
        {
            chooseCommand(userCommand);
        }
    }
}

void *chooseCommand(char *buff)
{	
    int i = 0,space;
    for(i = 0; buff[i] != '\0'; i++)
    {
        if(buff[i] == ' '&& space==0)
        space=i;
    }

    if(space==0)
        space = i;
    
    char *auxCommand[i];
    strcpy(auxCommand,buff);
    char *separeCommand = (char *)malloc(sizeof(char) * space);

    separeCommand = strtok(buff, " "); 
    char *tempCommand[i];
    strcpy(tempCommand,auxCommand);
    
    char matCommand[10][i];
    int cont=0;

    char *pch = strtok(tempCommand, " ");
    while(pch!=NULL)
    {
        strcpy(matCommand[cont++],pch); 
        pch = strtok(NULL, " ");
    }


    if (strcmp (separeCommand, "mkdir") == 0)
    {
        separateParams(auxCommand);
    }

    else if (strcmp (separeCommand, "pwd") == 0)
    {
        readDirectory(1);
    }

    else if (strcmp (separeCommand, "clear") == 0)
    {
        header();
    }

    else if (strcmp (separeCommand, "cd") == 0)
    {
        mountPath(auxCommand,"cd");
        readDirectory(0);
    }

    else if (strcmp (separeCommand, "ls") == 0)
    {
        int numDir=0,numCommand=0;
        char** lsCommand = (char**)malloc(sizeof(matCommand));
        char** lsPath = (char**)malloc(sizeof(matCommand));

        for(int i=0; i<10; i++){
            lsPath[i] = (char*)malloc(sizeof(matCommand[i]));
            lsCommand[i] = (char*)malloc(sizeof(matCommand[i]));
        }

        for(int i=0; i<cont; i++){
            if(matCommand[i][0] == '-'){
                lsCommand[numCommand++] = matCommand[i];
            }else if(matCommand[i][0] == '/'){
                for(int j=0; j<strlen(matCommand[i])-1; j++){
                    lsPath[numDir][j] = matCommand[i][j+1];
                }
                numDir++;
            }
        }

        if(numDir == 0){
            if(numCommand == 0){
                listDirectory("",".");
            }else{
                for(int i=0; i<numCommand; i++){
                    listDirectory(lsCommand[i],".");
                }
            }
        }else{
            if(numCommand == 0){
                for(int i=0; i<numDir; i++){
                    listDirectory("",lsPath[i]);
                }
            }else{
                for(int i=0; i<numDir; i++){
                    for(int j=0; j<numCommand; j++){
                        listDirectory(lsCommand[j],lsPath[i]);
                    }
                }
            }
        }
    }
    
    else if (strcmp (separeCommand, "cp") == 0)
    {
        cpRedirector(auxCommand);
    }

    else if (strcmp (separeCommand, "rmdir") == 0)
    {
        for(int i=1; i<cont; i++){
            rmDir(matCommand[i]);
        }
    }

    else if (strcmp (separeCommand, "exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }

    else
    {
        execDefault(auxCommand);
    } 
}
