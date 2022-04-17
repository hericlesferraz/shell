
#include"../include/cp.h"


int cpComplete(char type,char *copy,char *R,char *paste) {
   
    char nextcopy[10000];
    char nextpaste[10000];
    struct dirent *nextDir;
    int in =  0,i;

    DIR *dir = opendir(copy);
    if (dir == NULL) {
        return 0;
    }
    
	
    while ((nextDir = readdir(dir)) != NULL) {
    	
    if((comparation(nextDir->d_name,R)==0||type == 'U')&& (strcmp(nextDir->d_name, ".") != 0) && (strcmp(nextDir->d_name, "..") != 0 )){
    			
    		strcpy(nextcopy, copy);
                strcat(nextcopy, "/");
                strcat(nextcopy, nextDir->d_name); 
                strcpy(nextpaste, paste);
               
               for(i=0;nextpaste[i]!='\0';i++){}
               
                DIR *dirpaste = opendir(paste);
    		if (dirpaste != NULL) {
                strcat(nextpaste, "/");
                strcat(nextpaste, nextDir->d_name);
		}
		
        if (nextDir->d_type == DT_DIR && (type!='S')) {
		int check;
		if( (check = mkdir(nextpaste, 0777) ) !=  0)
                perror("\ncp: cannot create directory" );
           	 if(type=='T')
           	 in = cpComplete('U',nextcopy,R,nextpaste)+in;
           	 else
                in = cpComplete(type,nextcopy,R,nextpaste)+in;
                
                
        }else if ( nextDir->d_type != DT_DIR  ){
        	copyPaste(nextcopy,nextpaste); 
        	in  = 1;
        	}else {
        	printf("cp: -R não especificado; omitindo o diretório '%s'\n",R);
        	return (-1);
        	}
    }
    }
    closedir(dir);
    return (in);
}

int copyPaste(char *oldArq,char *newArq){
	FILE *CtrlC,*CtrlV;
	CtrlC = fopen(oldArq , "r");
	CtrlV = fopen(newArq , "w");
	int ch;
  	 while ((ch = getc (CtrlC )) != EOF){
       putc (ch, CtrlV);
      	}
      	fclose(CtrlC);
      	fclose(CtrlV);
	}
	
int comparation(char *full,char *unfinished){//retorna zero se igual 
int i ,k,j,l;
char *resource;
resource = malloc(sizeof(*full));
	for(i=0;unfinished[i]!='*'&&unfinished[i]!='\0';i++)
	resource[i]=full[i];

	resource[i]=unfinished[i];
	
	if(full[i]!='\0'&& unfinished[i]!='\0'){
	for(k=i;full[k]!='\0';k++){}
	k++;
	for(j=0;unfinished[i+j]!='\0';j++){}
	for(k=(k-j);full[k]!='\0';k++){
	i++;
	resource[i]=full[k];
	}
	resource[i+1]=full[k];
	}
	if (strcmp (unfinished, resource)==0){
	free(resource);
	return 0;
	}
	free(resource);
	return 1;
}

void cpRedirector(char *command)
{	
	
	char Type='S';
	int i,j=3,id1=0,id2=0,flag=0;
	for (i=0; command[i]!='\0';i++){}
	char resource[i],utilr[i],utilpaste[i],paste[i];
	
	resource[0]=command[3];
	resource[1]=command[4];
	resource[2]='\0';
		if(strcmp (resource,"-R")==0){
		Type = 'T';
		j=j+3;
		}
		for(i=0;command[j]!='\0';i++){
		resource[i]=command[j];
		if(flag!=0)
		utilpaste[i-flag]=command[j];
		if(command[j]=='/')
		id2=i;
		if(command[j]==' '){
		id1=id2;
		flag =i+1;
		}
		if (command[j]=='*'&& Type=='T')
		Type = 'R';
		j++;
		}
		resource[i]='\0';
		utilpaste[i-flag]='\0';
		
		if(id1!=0)
		id1=id1+1;
		
		for(i=id1;resource[i]!=' ';i++){
		utilr[i-id1]=resource[i];
		}
		utilr[i-id1]='\0';
		if(id1!=0)
		resource[id1-1]='\0';
		else{
		resource[0]='.';
		resource[1]='\0';
		}
		if(utilpaste[0]!='.'&& utilpaste[0]!='/'){
		strcpy(paste,"./");
		strcat(paste,utilpaste);
		}else{
		strcpy(paste,utilpaste);
		}
		i=cpComplete(Type,resource,utilr,paste);
		
		if(i==0){
		printf("cp: não foi possível obter estado de '%s': Arquivo ou diretório não encontrado\n",utilr);
		}
		

}
