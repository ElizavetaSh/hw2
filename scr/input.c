#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "input.h"

int defin_fsize(const char filename[]) 
{
    struct stat filestat;
    if (filename == 0) 
    {
        fprintf(stderr, "Error with file1\n");
        return 0;
    }
    FILE *file = fopen(filename, "r");
        if (file == NULL) 
        {
            fprintf(stderr, "Error with file2\n");
            return 0;
        }

    fclose(file);
    
    stat(filename, &filestat);
    return (filestat.st_size);
}

char *charsequence_from_file(int size, const char filename[]) 
{
        char *charsequence = (char *)malloc(size * sizeof(char));
            if (charsequence == NULL) 
            {
                fprintf(stderr, "error with malloc\n");
                return NULL;
            }
        FILE *file_with_charsequence = fopen(filename, "r");
        if (file_with_charsequence == NULL) 
        {
            free(charsequence);
            fprintf(stderr, "error with file10\n");
            return NULL;
        }
        char *buf = (char *)calloc(100, sizeof(char));
        if (buf == NULL) 
        {
            fclose(file_with_charsequence);
            free(charsequence);
            fprintf(stderr, "error with memory");
            return NULL;
        }
        int i = 0;
        while (fgets(buf, 100, file_with_charsequence) != NULL) 
        {
            size_t j = 0;
            while (j < strlen(buf) && buf[j] != '\n') 
		
            {		
                		charsequence[i] = buf[j];
                		i++;
                		j++;
                        if (j == size) {
                            break;
                        }
            }
        }
        free(buf);
        fclose(file_with_charsequence);
        return charsequence;
}
   