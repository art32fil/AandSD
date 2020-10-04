#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_BLOCK 20
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

int readLine(char** string, const char* breakers, int read_breakers, FILE* stream);

#endif
