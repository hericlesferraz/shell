#include "../include/stop.h"

void StopProcess(int  p){
    int PIDe =0;
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
	sem_wait((sem_t*)&PWD_area_ptr->mutex);
   	PIDe = PWD_area_ptr->PIDexec;
   	if(PIDe!=0)
	kill(PIDe,SIGINT);
	sem_post((sem_t*)&PWD_area_ptr->mutex);
	return;
}
