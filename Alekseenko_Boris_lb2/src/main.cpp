#include "treeWork.h"

int main() {
	treeWork tree;
	tree.startReading();
	tree.writeBin(tree.getTree());
	std::cout << std::endl;
	std::cout << "Weigth: " << tree.W(tree.getTree());
	return 0;
}