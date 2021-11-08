#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>
#include "sequence.h"

#define Size_memory 13107200


void fill_buff_struct(char_count* arr_in, char_count* arr_out, int len)
{
    for (int i = 0; i < len; i++){
    arr_out[i].element = arr_in[i].element;
    arr_out[i].count_char = arr_in[i].count_char;
    arr_out[i].count_repet = arr_in[i].count_repet;
    }

}

void fill_buff_char(char* arr_in, char* arr_out, int len)
{
    for (int i = 0; i < len; i++){
    arr_out[i]= arr_in[i];
    }

}

char_count sequencew(char arr[], int len, char_count result)
{   
    
    int len_buff = 4;
    int index_count = 0;
    int count_need = 0;

    result.element = 0;
    result.count_char = 0;
    result.count_repet = 0;

    if (arr == NULL) return result;
    if (len > Size_memory-1 |len < 1) return result;    

    char* char_array = (char*)malloc(Size_memory* sizeof(char));
    if (char_array == NULL) 
        {
        free(char_array);
        return result;
        }
    
    fill_buff_char(arr, char_array, len);

    char_count* stuck_buf = (char_count*)malloc(len_buff * sizeof(char_count));
    if (stuck_buf == NULL) 
        {
        free(stuck_buf);
        return result;
        }
       
    for (char last = *char_array, *f = char_array, *l = char_array;;)
    {
        count_need = 0;
        
        stuck_buf[index_count].element = *l;
        while (*l == last)
        {
            count_need++;            
            l++;
        }
    stuck_buf[index_count].count_char = count_need;
    index_count++;

    if (index_count > len_buff - 1)
    {
        len_buff = 10 * len_buff;
        char_count* stuck_buf_new = (char_count*)malloc(len_buff * sizeof(char_count));
        if (stuck_buf_new == NULL)
        {
            free(stuck_buf_new);
            return result;
        }
        fill_buff_struct(stuck_buf, stuck_buf_new, index_count);
        free(stuck_buf);
        stuck_buf = stuck_buf_new;

    }
    last = *++f = *l;

        if (*l == 0)
        {
            *f = 0;
            break;
        }
    
    }
    int count_value;
    int max = 0;
    for (int i=0; i<index_count; i++){
        count_value= 0;
        for (int j=0; j<index_count; j++)
        {                      
            if (stuck_buf[i].count_char == stuck_buf[j].count_char)
                count_value++;
            
        }
    stuck_buf[i].count_repet = count_value;

    if (max < stuck_buf[i].count_repet)
        {
        max = stuck_buf[i].count_repet;
        fill_buff_struct(&stuck_buf[i], &result, 1);
        }
    }

    free(stuck_buf);
    free(char_array);

    return result;
}

char find_repeat_in_sequence(char char_array[], int len, char result){
    char_count result_ppp;
    result_ppp.element = 0;
    result_ppp.count_char = 0;
    result_ppp.count_repet = 0;

    if (len == 0) {
            fprintf(stderr, "error  with file\n");
            return ER_FILE;
        }

    if (char_array == NULL) {
            fprintf(stderr, "error with file\n");
            return ER_MEMORY;
        }

    result = sequencew(char_array, len, result_ppp).element;

    return result;
}