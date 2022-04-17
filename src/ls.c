
#include"../include/ls.h"


void listDirectory(char* command, char path[]){
	printf("List Directory: %s %s\n",path,command);
	
	int qtdNames=0, qtdFolders=0;
	char names[100][100];
	char folders[100][100];

	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			names[i][j] = '\0';
			folders[i][j] = '\0';
		}
	}

	if(!(strcmp(command,"-l"))){
		//	Long Listing
		DIR *dir;
		struct dirent *entry;
		struct stat attribute;
		long int blockFiles=0;

		dir = opendir(path);

		if(dir == NULL){
			perror("List Directory");
			closedir(dir);
			return;
		}

		while((entry = readdir(dir))){
			if(entry->d_name[0] == '.'){
				continue;
			}else{

				int test = lstat(entry->d_name,&attribute);

				if(test == 0){
					
					//	NAME
					printf("%s\t",entry->d_name);
					
					//	DATA
					//	S_IFMT = bitmask for the file type bitfields
					//	d Directory
					if(attribute.st_mode & S_IFDIR){
						printf("d");
					}else{
						printf("-");
					}
					
					//	rwd Owner
  				//	S_IRWXU = mask for file owner permissions
					if(attribute.st_mode & S_IRUSR){
						printf("r");
					}else{
						printf("-");
					}
					if(attribute.st_mode & S_IWUSR){
						printf("w");
					}else{
						printf("-");
					}
					if(attribute.st_mode & S_IXUSR){
						printf("x");
					}else{
						printf("-");
					}

					//	rwd Group
					//	S_IRWXG = mask for group permissions
					if(attribute.st_mode & S_IRGRP){
						printf("r");
					}else{
						printf("-");
					}
					if(attribute.st_mode & S_IWGRP){
						printf("w");
					}else{
						printf("-");
					}
					if(attribute.st_mode & S_IXGRP){
						printf("x");
					}else{
						printf("-");
					}

					//	rwd Others
					//	S_IRWXO = mask for permissions for others (not in group)
					if(attribute.st_mode & S_IROTH){
						printf("r");
					}else{
						printf("-");
					}
					if(attribute.st_mode & S_IWOTH){
						printf("w");
					}else{
						printf("-");
					}
					if(attribute.st_mode & S_IXOTH){
						printf("x");
					}else{
						printf("-");
					}

					printf("\t");

					//	LINK COUNT
					printf("%ld\t",(long)attribute.st_nlink);

					struct group *groups;
					struct passwd *users;

					//	UID
					users = getpwuid((long)attribute.st_uid);
					printf("%s\t",users->pw_name);

					//	GID
					groups = getgrgid((long)attribute.st_gid);
					printf("%s\t",groups->gr_name);

					//	FILE SIZE
					printf("%ld\t",(long)attribute.st_size);

					//	LAST FILE MODIFICATION
					printf("%s",ctime(&attribute.st_mtime));

					// Blocks allocated

					blockFiles += (attribute.st_blocks/2.00);
				}else{
					printf("Nao foi possivel abrir atributos do arquivo %s\n",entry->d_name);

					blockFiles += attribute.st_blocks;

				}

			}
		}
		

		printf("Total: %ld\n",blockFiles);

		//printf("Total Blocks: %ld\n",blockFiles);


		printf("\n");
		closedir(dir);
	}else if(!(strcmp(command,"-R"))){
		//	Recursive Listing
		DIR *dir;
		struct dirent *entry;

		dir = opendir(path);

		if(dir == NULL){
			perror("List Directory");
			closedir(dir);
			return;
		}

		int lenPath = strlen(path);
		int lenFolders[100];
		for(int i=0; i<100; i++){
			for(int j=0; j<lenPath; j++){
				folders[i][j] = path[j];
			}
			folders[i][lenPath] = '/';
			lenFolders[i] = strlen(folders[i]);
	}

		while((entry = readdir(dir))){
			if(entry->d_name[0] == '.'){
				continue;
			}else{
				if(entry->d_type == DT_DIR){
					for(int i=0; i<strlen(entry->d_name); i++){
						folders[qtdFolders][i+lenFolders[qtdFolders]] = entry->d_name[i];
					}
					qtdFolders++;
				}
				for(int i=0; i<strlen(entry->d_name); i++){
					names[qtdNames][i] = entry->d_name[i];
				}
				qtdNames++;
			}
		}


		for(int i=0; i<qtdNames; i++){
			printf("%s\t",names[i]);
		}

		printf("\n\n");
		for(int i=0; i<qtdFolders;i++){
			listDirectory(command, folders[i]);
		}
		closedir(dir);

	}else{
		//	Regular Listing
		DIR *dir;
		struct dirent *entry;

		dir = opendir(path);

		if(dir == NULL){
			perror("List Directory");
			closedir(dir);
			return;
		}

		while((entry = readdir(dir))){
			if(entry->d_name[0] == '.'){
				continue;
			}else{
			printf("%s\t",entry->d_name);
			}
		}
		closedir(dir);
		printf("\n\n");
	}

	return;
}
