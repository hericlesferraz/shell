#include "../include/pwd.h"
struct PWD_area{
	char PWD[PWD_SZ];
	int PIDexec;
	sem_t mutex;
	
};
int readDirectory(bool outputCase) {
    long nameDir;
    char *bufferDir;
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
	
	for(i=0;i<PWD_SZ;i++)
		PWD_area_ptr->PWD[i]=0;
	
    nameDir = pathconf(".", _PC_PATH_MAX);
    assert(nameDir != -1);
    bufferDir = malloc(nameDir * sizeof(*bufferDir));
    assert(bufferDir);
    
    if (getcwd(bufferDir, nameDir) == NULL) 
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    } 
    
    else 
    {
    	strcpy(PWD_area_ptr->PWD,bufferDir);
		if(outputCase)
        	printf("%s \n", bufferDir);
    }

    free(bufferDir);
    return EXIT_SUCCESS;
}
