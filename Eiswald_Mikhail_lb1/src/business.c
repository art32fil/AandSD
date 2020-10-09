#include "business.h"
#include "output.h"

int isText(const char** ptr, char expected, int depth, FILE* out){
	int result;
	depthtab(depth+1, out);
	printf("isText() processing \"%s\"\n", *ptr);
	fprintf(out, "isText() processing \"%s\"\n", *ptr);
	if(!strlen(*ptr)){
		depthtab(depth+1, out);
		printf("isText() finished\n");
		fprintf(out, "isText() finished\n");
		if(!(expected)) return true;
		error(UNEXPECTED_EOL, out);
		return false; // unexpected end of input
	}
	if(**ptr == expected) {
		expected = 0;
		depthtab(depth+1, out);
		printf("isText() finished\n");
		fprintf(out, "isText() finished\n");
		return true;
	}
	if(isElement(ptr, depth+1, out)){
		++(*ptr);
		result = isText(ptr, expected, depth+1, out);
		depthtab(depth+1, out);
                printf("isText() finished\n");
                fprintf(out,"isText() finished\n");
		return result;
	}
        depthtab(depth+1, out);
        printf("isText() finished\n");
        fprintf(out,"isText() finished\n");
	return false;
}


int isElement(const char** ptr, int depth, FILE* out){
	int result;
	char tmp;
	depthtab(depth+1, out);
	printf("isElement() processing \'%c\'\n", **ptr);
	fprintf(out,"isElement() processing \'%c\'\n", **ptr);
	switch(**ptr){
	case('A'):
	case('B'):
                depthtab(depth+1, out);
                printf("isElement() finished\n");
		fprintf(out,"isElement() finished\n");
		return true;
	case('('):
		tmp = ')';
		break;
	case('{'):
		tmp = '}';
		break;
	case('['):
		tmp = ']';
		break;
	case(']'):
	case(')'):
	case('}'):
                depthtab(depth+1, out);
                printf("isElement() finished\n");
                fprintf(out,"isElement() finished\n");
		error(EXTRA_BRACKET, out);
		return false; // extra closing bracket
	default:
                depthtab(depth+1, out);
                fprintf(out,"isElement() finished\n");
                printf("isElement() finished\n");
		error(ILLEGAL_SYMBOL, out);
		return false; // inappropriate symbol
	}
	++(*ptr);
	if(**ptr == tmp){
		depthtab(depth+1, out);
		printf("isElement() finished\n");
		fprintf(out,"isElement() finished\n");
		error(EMPTY_BRACKETS, out);
		return false; // empty brackets
	}
	result = isText(ptr, tmp, depth+1, out);
	depthtab(depth+1, out);
	printf("isElement() finished\n");
	fprintf(out, "isElement() finished\n");
        return result;
	
}

