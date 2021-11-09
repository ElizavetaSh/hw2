#include <stdbool.h>
#include <stdlib.h>

#define ER_FILE 87
#define ER_MEMORY 88
#define ER_KERNEL 89


typedef struct char_count
    {
        char element;
        int count_char;
        int count_repet;
    }char_count;

void fill_buff_char(char arr_in[], char arr_out[], int len);
void fill_buff_struct(char_count* arr_in, char_count* arr_out, int len);
char_count sequencew(char arr[], int len, char_count result);
char find_repeat_in_sequence(char char_array[], int len, char result);
