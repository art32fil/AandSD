#include "input.h"

int readLine(char** string, const char* breakers, int read_breakers, FILE* stream){
    int num = 0;
    int size = 0;
    char chr = 0;
    char* tmp;

    *string = calloc(BUFFER_BLOCK, sizeof(char));
    if(!(*string)) return 1;
    size += BUFFER_BLOCK;

    while ((!strchr(breakers, (chr = fgetc(stream)))) && (chr != EOF)){
        if(num + 2 >= size){
            tmp = realloc(*string, (size + BUFFER_BLOCK) * sizeof(char));
            if(!tmp){
               free(*string);
               return 1;
            }
            *string = tmp;
            size += BUFFER_BLOCK;
        }
        (*string)[num] = chr;
        (*string)[num+1] = 0;
        num++;
    }
    if(read_breakers && (chr != EOF)){
       (*string)[num] = chr;
       (*string)[num+1] = 0;
    }
    if (chr == EOF) return -1;
    return 0;
}

