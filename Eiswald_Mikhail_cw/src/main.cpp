#include <cstring>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "hashtable.h"
#include "colorout.h"

#define OUTFILE "output.txt"
#define ADD '+'
#define REMOVE '-'
#define INFO '?'
#define SPECIAL "+-?"

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
        std::cout << "Enter EOF (e.g. Ctrl+D on Linux) to finish.\n";
	}
	do{
		getline( (infile.is_open() ? infile : std::cin) , str);
		if( (infile.is_open() && infile.eof()) || (std::cin.eof()) ) break;
        std::cout << "Read line: \"" << str << "\"\n";
		out << "Read line: \"" << str << "\"\n";
        if(!str.length()) continue;
		source = str.c_str();

        if(strchr(SPECIAL, source[0])){
            //received a command
            if(!ht){
                color(FOREGROUND_RED);
                cout << "(!)Rejected: No hash table has been created yet to add, " <<
                        "remove, or print detailed info.\n";
                out << "(!)Rejected: No hash table has been created yet to add, " <<
                        "remove, or print detailed info.\n";
                cout << "To create a new hash table, type any " <<
                        "string not starting with: ";
                out << "To create a new hash table, type any " <<
                        "string not starting with: ";
                for(const char* ptr = SPECIAL; *ptr; ++ptr){
                    cout << "'" << *ptr << "' ";
                    out << "'" << *ptr << "' ";
                }
                cout << "\n";
                out << "\n";
                color(FOREGROUND_WHITE);
                continue;
            }
            switch(source[0]){
            case ADD:
                ++source;
                if(!(*source)){
                    color(FOREGROUND_YELLOW);
                    cout << "Warning: no elements to add.\n";
                    out << "Warning: no elements to add.\n";
                    color(FOREGROUND_WHITE);
                }
                while(*source){
                    ht->add(*source);
                    ht->printChains();
                    ++source;
                }
                continue;
            case REMOVE:
                ++source;
                if(!(*source)){
                    color(FOREGROUND_YELLOW);
                    cout << "Warning: no elements to remove.\n";
                    out << "Warning: no elements to remove.\n";
                    color(FOREGROUND_WHITE);
                }
                while(*source){
                    ht->remove(*source);
                    ht->printChains();
                    ++source;
                }
                continue;
            case INFO:
                cout << "Printing detailed info...\n";
                out << "Printing detailed info...\n";
                ht->printInfo();
                continue;
            }
        }

        delete ht;
        ht = new HashTable<char>(str.length(),out);
        ht->printChains();

		while(*source){
            ht->add(*source);
            ht->printChains();
			++source;
		}
		std::cout << "\n";
		out << "\n";
	}while((infile.is_open() && !infile.eof()) || (!(infile.is_open()) && !std::cin.eof()) );

    cout << "[Quit]\n";
    delete ht;
	return 0;
}

