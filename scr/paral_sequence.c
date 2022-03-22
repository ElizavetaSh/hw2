#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sequence.h"
#include "input.h"

#define Size_memory 13107200

typedef struct params
    {
        char * arr;
        int len;
        char_count result;
    }params;
    

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


char find_repeat_in_sequence(char char_array[], int len, char result) 
{     
        long thread_len;
        long count_thread = sysconf(_SC_NPROCESSORS_CONF);
        long start_index = 0;
        long end_index = 0;

        if (len == 0) {
            fprintf(stderr, "error with len\n");
            return ER_FILE;
        }

        if (char_array == NULL) {
        fprintf(stderr, "error with memory\n");
        return ER_MEMORY;
        }        
            

        if (count_thread < 0) {
            fprintf(stderr, "error with kernels\n");
            return ER_KERNEL;
        }
          
        if (count_thread > len-1) 
            count_thread = len;

      pthread_t* threads = (pthread_t*)malloc(count_thread * sizeof(pthread_t));
        if (threads == NULL) 
        {
            free(threads);
            fprintf(stderr, "error with memmory\n");
            return ER_MEMORY;
        }               

        thread_len = len / count_thread + len % count_thread;   

    params* part_data_thread = (params*)malloc(count_thread * sizeof(params));
        if (part_data_thread == NULL) 
        {
            free(part_data_thread);
            free(threads);
            fprintf(stderr, "error with memmory\n");
            return ER_MEMORY;
        }
    
    for (long i = 0; i < count_thread; ++i) 
    {
        long add_len = 0;
        long size_thread = (i+1)*thread_len - 1;
        
        if (size_thread + 1 < len)
        {
            while (char_array[size_thread] == char_array[size_thread + 1])
            {
                add_len++;
                size_thread++;
            }
        }
        part_data_thread[i].arr = (char*)calloc((thread_len + add_len), sizeof(char));
            if (part_data_thread[i].arr == NULL) 
            {
            free(part_data_thread[i].arr);
            free(part_data_thread);
            free(threads);
            fprintf(stderr, "error with memmory\n");
            return ER_MEMORY;
            }

        
        part_data_thread[i].len = thread_len + add_len;

        for (long j = 0; j < thread_len + add_len ; ++j) {
            if (start_index < len)
            {
            part_data_thread[i].arr[j] = char_array[start_index];
            start_index++;
            }
            else {
                break;
            }
         }

        if (pthread_create(&(threads[i]), NULL, sequencew ,&part_data_thread[i]) != 0) {
            for (long j = 0; j < count_thread; ++j) {
                free(part_data_thread[j].arr);
            }
            free(part_data_thread);
            free(threads);
            fprintf(stderr, "error with kernels\n");
            return ER_KERNEL;
            }
        start_index = end_index;
    }

    int max_count = 0;

    char_count result_ppp;
    result_ppp.element = 0;
    result_ppp.count_char = 0;
    result_ppp.count_repet = 0;
    

    char_count* thread_stuck_buf = (char_count*)malloc(count_thread * sizeof(char_count));
        if (thread_stuck_buf == NULL)
        {
            for (long j = 0; j < count_thread; ++j) {
                free(part_data_thread[j].arr);
            }
            free(part_data_thread);
            free(threads);
            free(thread_stuck_buf);
            return result;
        }

    for (long i = 0; i < count_thread ; ++i) {
        pthread_join(threads[i], NULL);
        thread_stuck_buf[i].element = sequencew(char_array, len, result_ppp).element;
        thread_stuck_buf[i].count_char = sequencew(char_array, len, result_ppp).count_char;
        thread_stuck_buf[i].count_repet = sequencew(char_array, len, result_ppp).count_repet;
    }
    for (long i = 0; i < count_thread ; ++i) {
        if (max_count<thread_stuck_buf[i].count_repet){
            max_count = thread_stuck_buf[i].count_repet;
            result = thread_stuck_buf[i].element;
        }

    }
    for (long j = 0; j < count_thread; ++j) {
                free(part_data_thread[j].arr);
            }
            free(part_data_thread);
            free(threads);
    free(thread_stuck_buf);
    return result;
    
}