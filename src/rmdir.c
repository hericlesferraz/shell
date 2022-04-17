#include "../include/general.h"

int rmDir(char *caminho){
	DIR* folder;
	DIR* teste;
	struct dirent* entry;
	folder = opendir(caminho);
	if(folder == NULL){
		printf("Erro ao abrir o diretorio.\n");
		return 0;
	}
	int i;
	while(entry = readdir(folder)){
		if(entry->d_name[0] == '.')
			continue;
		else{
			char *caminhoCompleto;
			int tamanhoString = strlen(entry->d_name);
			caminhoCompleto = malloc(strlen(caminho) + strlen(entry->d_name) + 1);
			strcpy(caminhoCompleto, caminho);
			strcat(caminhoCompleto, "/");
			strcat(caminhoCompleto, entry->d_name);
			teste = opendir(caminhoCompleto);
			closedir(teste);
			if(teste == NULL){
				remove(caminhoCompleto);
			}else
				rmDir(caminhoCompleto);
		}
	}
	remove(caminho);
	return 1;
}
