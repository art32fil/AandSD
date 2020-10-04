#ifndef OUTPUT_H
#define OUTPUT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define UNEXPECTED_EOL 0
#define EXTRA_BRACKET 1
#define ILLEGAL_SYMBOL 2
#define EMPTY_BRACKETS 3

#define NORMAL "\033[0m"
#define RED "\033[0;31m"

void depthtab(int, FILE*);
void error(int, FILE*);

#endif
