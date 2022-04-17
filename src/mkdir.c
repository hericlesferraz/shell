#include "../include/mkdir.h"

void *separateParams(char *buff)
{
    char *separator = (char *)malloc(sizeof(char ));

    separator = strtok(buff, " ");
    if (strcmp (separator, "mkdir") == 0)
    {
        while(separator != NULL )
        {
            if (separator != NULL)
            {
                separator = strtok( NULL, " " );
            }
            if(separator == NULL) break;
            if( (separator[strlen(separator)]-1) == '\n') 
            {
                separator[strlen(separator)-1] = '\0';
            }
            int check;
            if( (check = mkdir(separator, 0777) ) !=  0) 
            { 
                printf("\nmkdir: cannot create directory '%s': File exists \n", separator);
            }
        }
    }
    else if(strcmp (separator, "mkdir") != 0)
    {
        printf("shell: command not found: %s \n", separator);
    }
    free(separator);

}
