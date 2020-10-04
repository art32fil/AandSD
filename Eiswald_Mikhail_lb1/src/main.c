#include "input.h"
#include "business.h"

int main(){
	char* string = NULL;
	char* ptr;
	FILE* f = fopen(INPUT_FILE, "r");
	FILE* out = fopen(OUTPUT_FILE, "w");
	if(!out){
		puts("Cannot create output file. Exiting.");
		return 0;
	}
	char tmp = 0;
	int text;
        if(!f){
           printf("Failed to open file \"%s\". Expecting input from console...\n", INPUT_FILE);
	   puts("Enter a line to analyze. Enter EOF (i.e. Ctrl+D) to exit.");
           fprintf(out,"Failed to open file \"%s\". Expecting input from console...\n", INPUT_FILE);
	   fputs("Enter a line to analyze. Enter EOF (i.e. Ctrl+D) to exit.\n",out);
        }
	int result;
	do{
		result = readLine(&string, "\n", 0, (f ? f : stdin));
        	if(result > 0){
                	puts("Failed to read text. Exiting...");
                	fputs("Failed to read text. Exiting...\n", out);
			if(string) free(string);
                	exit(0);
        	}
		if(result == EOF){
			if(string) free(string);
			string = NULL;
			break;
		}
		printf("Checking line \"%s\"\n", string);
		fprintf(out,"Checking line \"%s\"\n", string);
		if(!strlen(string)){
			puts(RED"Error: empty input"NORMAL);
			fputs("Error: empty input\n", out);
		}
		else{
			ptr = string;
			text = isText((const char**)(&ptr), tmp, 0, out);
			if(text){
				puts("OK:");
				fputs("OK:\n", out);
				printf("%s\n\n", string);
				fprintf(out, "%s\n\n", string);
			}
			else{
				for(char* p = string; p < ptr; ++p){
					putchar(*p);
					putc(*p, out);
				}
				printf(RED);
				putchar(*ptr);
				if(*ptr) putc(*ptr, out);
				printf(NORMAL);
				puts("");
				putc('\n', out);
				for(int i = 0; i < (int)(ptr - string); ++i){ 
					putchar(' ');
					putc(' ', out);
				}
				puts("^");
				fputs("^\n", out);
			}
		}
		free(string);
		string = NULL;
	}while(result == 0);
	if(f) fclose(f);
	if(out) fclose(out);
	return 0;
}
