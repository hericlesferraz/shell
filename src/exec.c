#include "../include/exec.h"

void *execDefault(char *name){
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
	if ( sem_init((sem_t *)&PWD_area_ptr->mutex,1,1) != 0 )
        {
                printf("sem_init falhou\n");
                exit(-1);
        }

	
    pid_t pid;
    int z=0,k=0,space=0,Narg=0;
    char *prog = malloc(sizeof(*prog));
    char *copy = malloc(sizeof(*copy));
    strcpy(copy, name);
    strcpy(prog, name);
    
    for(i=0;name[i]!='\0';i++){
    if(name[i]==' '){
    if(space==0){
    prog[i]='\0';
    k=i;
    }
    space++;
    }
   	if(name[i]=='/'&& space==0)
   		 z=i+1;
    }
    char resource[space][i]; 
    char *args[space+2]; 
   
    for(i=z;name[i]!='\0'&& name[i]!=' ';i++)
    name[i-z]=name[i];

    name[i-z]='\0';
    
    args[Narg]=name;
    i=k;
    while(copy[i]!='\0'&&k!=0){
    k++;
    for(i=k;copy[i]!='\0'&& copy[i]!=' ';i++){
    resource[Narg][i-k]=copy[i];
    }
    resource[Narg][i-k]='\0';
    Narg++;
    args[Narg] =resource[Narg-1];
    k=i;
    }
    args[space+1]=NULL;  
    
    if(z==0){
    strcpy(prog,"/usr/bin/");
    strcat(prog,name);
    }
      
     pid=fork();
     
     if ( pid == 0 )
   {
   	sem_wait((sem_t*)&PWD_area_ptr->mutex);
   	PWD_area_ptr->PIDexec= getpid();
   	sem_post((sem_t*)&PWD_area_ptr->mutex);
	execv (prog, args);
	printf("shell: command not found:%s.", copy);
	exit(0);
   }
   else
   if (pid > 0 )
   {//script pai espera terminar
	wait(&z);
	sem_wait((sem_t*)&PWD_area_ptr->mutex);
   	PWD_area_ptr->PIDexec= 0;
   	sem_post((sem_t*)&PWD_area_ptr->mutex);
  	return;
   }
}
