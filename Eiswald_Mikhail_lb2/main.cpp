#include <iostream>
#include <fstream>
#include "l_intrfc.h"

using namespace h_list;
using namespace std;

void clear_input(string& expression, char chr){
	int pos = 0;
        while(pos != string::npos){
                pos = expression.find(chr, pos);
                if(pos != string::npos){
                     expression.insert(pos+1 , " ");
                     expression.insert(pos," ");
                     pos += 2;
                }
        }
}

int main(){
	lisp lst = NULL;
	lisp flat_lst = NULL;
	std::string expression;
	std::string filename;
	std::cout << "Specify input file name: ";
	getline(cin, filename);
	ifstream infile(filename.c_str());
	ofstream outfile("output.txt");
	
	if(!infile){
		std::cout << "Failed to open file. Expecting input from console...\n";
		std::cout << "Enter EOF (i.e. Ctrl+D) to finish input.\n";
	}

	while((!infile.eof() && infile.is_open()) || (!cin.eof() && !infile.is_open())){
		infile ? getline(infile,expression) : getline(cin,expression); 
		if(expression != ""){
			outfile << "Initial string: \"" << expression << "\"\n";
			while(expression.find(",") != string::npos){
				expression[expression.find(",")] = ' ';
			}
			clear_input(expression, '(');
			clear_input(expression, ')');
			int pos = 0;
			while(expression.find("power",pos) != string::npos){
				pos = expression.find("power",pos) + 1;
				expression[expression.find("(",pos)] = ' ';
				int counter = 0;
				int pos_bracket = pos;
				while(1){
					if(expression.find(")",pos_bracket)<
					expression.find("(",pos_bracket)){
						if(!counter){ expression[expression.find(")",pos_bracket)]= ' ';
						   break;
						}
						else --counter;
					}
					else ++counter;
					pos_bracket = min(expression.find(")",pos_bracket),
					expression.find("(",pos_bracket)) + 1;
				}
			}
			expression.erase(0, expression.find_first_not_of(" "));
			cout << expression << "\n";
			outfile << "Parsed string: \"" << expression << "\"\n";
			read_lisp(lst, expression);
			write_lisp(lst, &outfile);
        		std::cout << '\n';
			outfile << "\n";
			int result = calculate(lst, &outfile);
			cout << "Result: " << result << "\n";
			outfile << "Result: " << result << "\n";
        		destroy(lst);
			lst = NULL;
		}
	}

	return 0;	

	/*lisp lst = NULL;
	read_lisp(lst, &infile);
	write_lisp(lst);
	std::cout << '\n';
	destroy(lst);
	return 0;*/
}
