#ifndef BUSINESS_H
#define BUSINESS_H

#include <string.h>
#include <stdio.h>

#include "output.h"

#define false 0
#define true 1

int isText(const char** ptr, char expected, int, FILE*);
int isElement(const char** ptr, int, FILE*);

#endif // BUSINESS_H
