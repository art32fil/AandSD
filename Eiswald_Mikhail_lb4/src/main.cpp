#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>

#include <iostream>
#include <fstream>
#include <string>

#include "sort.h"

#define OUTFILE "output.txt"
#define NUMBER_CHARS "+-"

int main(){
	int* buffer = nullptr;
	int index;
	const char* source;
	int elem;
	int sort_result;

	std::ofstream out(OUTFILE);
	if(!out.is_open()){
		std::cout << "Failed to create output file. Exiting...\n";
		return 0;
	}
	std::string str;
	std::cout << "Specify input file name: ";
	getline(std::cin, str);
	std::ifstream infile(str.c_str());
	if(!infile.is_open()){
		std::cout << "Failed to open file. Expecting input from console...\n";
		std::cout << "Enter EOF (i.e. Ctrl+D) to finish.\n";
	}
	do{
		index = 0;
		getline( (infile.is_open() ? infile : std::cin) , str);
		if( (infile.is_open() && infile.eof()) || (std::cin.eof()) ) break;
		std::cout << "Read line: \"" << str << "\"\n";
		out << "Read line: \"" << str << "\"\n";
		buffer = (int*)realloc(buffer , sizeof(int)*(str.length()/2 + 1) );
		//source = (char*)realloc(reserved, sizeof(char)*(str.length()+1) );
		//strcpy(source , str.c_str());
		//reserved = source;
		//puts(source);
		source = str.c_str();
		while(source[0] && !isdigit(source[0]) && !strchr(NUMBER_CHARS,source[0])) ++source;
		int result;
		do{
			result = sscanf(source , "%d" , &elem);
			if(result == 1){
			   buffer[index++] = elem;
			   while((source[0])&&(isdigit(source[0]) || strchr(NUMBER_CHARS,source[0]))) 
				++source;
			   while(source[0] && !isdigit(source[0]) && !strchr(NUMBER_CHARS,source[0]))
				++source;
			}
		}while(result == 1);
		std::cout << "Extracted numbers: ";
		out << "Extracted numbers: ";
		for(int i = 0; i < index; ++i) std::cout << buffer[i] << " ";
		for(int i = 0; i < index; ++i) out << buffer[i] << " ";
		std::cout << "\n";
		out << "\n";
		sort_result = solomonSort(buffer , index , out);
		switch(sort_result){
		case EMPTY_ARRAY:
			out << "Error: array is empty!\n";
			std::cout << "Error: array is empty!\n";
			break;
		case ALL_EQUAL:
			out << "All numbers are equal!\n";
			std::cout << "All numbers are equal!\n";
			break;
		default:
			out << "Finished sorting...\n";
			std::cout << "Finished sorting...\n";
			for(int i = 0; i < index; ++i) std::cout << buffer[i] << " ";
			for(int i = 0; i < index; ++i) out << buffer[i] << " ";
			std::cout << "\n";
			out << "\n";
		}
	}while((infile.is_open() && !infile.eof()) || (!(infile.is_open()) && !std::cin.eof()) );

	free(buffer);
	return 0;
}
