#include <iostream>
#include <fstream>
#include <string>

#include "binarytree.h"

#define OUTFILE "output.txt"

int main(){

	std::string str;
	std::cout << "Specify input file name: ";
	getline(std::cin, str);
	std::ifstream infile(str.c_str());
	std::ofstream outfile(OUTFILE);
	if(!outfile.is_open()){
		std::cout << "Failed to create output file. Exiting...\n";
		return 0;
	}

	BT::BinTree<char> tree = BT::BinTree<char>(&outfile);

	if(!infile.is_open()){
		std::cout << "Failed to open file. Expecting input from console...\n";
		std::cout << "Enter EOF (i.e. Ctrl+D) to finish.\n";
		std::cin >> noskipws;
	}
	else{
		infile >> noskipws;
	}

	BT::CustomQueue<char> queue(&outfile);

	do{
		tree.read(&infile);
		getline( (infile.is_open() ? infile : std::cin) , str);
		std::cout << "\n";
		std::cout << "Finished reading...\n";
		outfile << "\nFinished reading..." << std::endl;

		queue.pushTree(tree.root(),0);

		std::cout << "\nTree levels:\n";
		outfile << "\nTree levels:\n";
		queue.print();
		std::cout << "\n";
		outfile << std::endl;

		tree.reset();
		queue.clear();
	}while(1);
	return 0;
}
