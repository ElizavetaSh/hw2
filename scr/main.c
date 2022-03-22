#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "sequence.h"
#include "input.h"

#define EXIT_SUCCESS 0
#define EXIT_NOSUCCESS -1000
#define TIME_CONST 1000000000

int main(int argc, const char **argv) {
struct timespec start, finish;


if (argv[1] == 0) {
    printf("error with file\n");
}

int len = defin_fsize(argv[1]);
    if (len == 0) 
    {
        fprintf(stderr, "error with len\n");
        return EXIT_NOSUCCESS;
    }

char *file_values = charsequence_from_file(len, argv[1]);
    if (file_values == NULL) 
    {
        fprintf(stderr, "error with file");
        return EXIT_NOSUCCESS;
    }

clock_gettime(CLOCK_REALTIME, &start);

char result = 0;
result = find_repeat_in_sequence(file_values, len, result);
free(file_values);

clock_gettime(CLOCK_REALTIME, &finish);

size_t spent_time = TIME_CONST*(finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec);
printf("Spent time: %lu ns \n", spent_time);
return EXIT_SUCCESS;
}