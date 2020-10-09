#include "output.h"

void depthtab(int depth, FILE* out){
	for(int i = 0; i < depth; ++i){
		printf(".");
		putc('.', out);
	}
}


void error(int index, FILE* out){
	char errors[][100] = {"unexpected end of input",
			 "extra closing bracket",
			 "illegal symbol",
			"empty brackets"};
	printf(RED"Error: %s:\n"NORMAL, errors[index]);
	fprintf(out, "Error: %s:\n", errors[index]);
}
