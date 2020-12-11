#include <iostream>
#include <fstream>
#include <string>

#include "hashtable.h"

#define OUTFILE "output.txt"
#define ADD '+'

int main(){
    HashTable<char>* ht = nullptr;
	const char* source;

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
		getline( (infile.is_open() ? infile : std::cin) , str);
		if( (infile.is_open() && infile.eof()) || (std::cin.eof()) ) break;
		std::cout << "Read line: \"" << str << "\"\n";
		out << "Read line: \"" << str << "\"\n";
        if(!str.length()) continue;
		source = str.c_str();
        if(*source != ADD || !ht){
            if(*source == ADD){
                std::cout << "Error: an attempt to add to hash table ";
                std::cout << "without creating one.\n";
                out << "Error: an attempt to add to hash table ";
                out << "without creating one.\n";
                continue;
            }
            else{
                --source;
                delete ht;
            }
            ht = new HashTable<char>(str.length(),out);
            ht->printChains();
        }
        ++source;
		while(*source){
            cout << "Adding '" << *source << "'\n";
            out << "Adding '" << *source << "'\n";
            ht->add(*source);
            ht->printChains();
			++source;
		}
		std::cout << "\n";
		out << "\n";
	}while((infile.is_open() && !infile.eof()) || (!(infile.is_open()) && !std::cin.eof()) );

	return 0;
}

