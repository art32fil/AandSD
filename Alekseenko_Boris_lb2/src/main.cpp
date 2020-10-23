#include "treeWork.h"

int main() {
	treeWork tree;
	tree.startReading();
	tree.writeBin(tree.getTree());
	std::cout << std::endl;
	int weight = tree.W(tree.getTree());
	std::cout << "Weight: " << weight << std::endl;  
	return 0;
}