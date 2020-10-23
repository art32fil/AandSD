#include "treeWork.h"

void treeWork::startReading() {
	std::cout << "Will you use file input or from consol?(f - file / c - console)" << std::endl;
	char choice;
	std::cin >> choice;
	switch (choice) {
	case 'f': {
		std::cout << "Enter file's name" << std::endl;
		std::string name_;
		while (std::cin.get() != '\n');
		getline(std::cin, name_);
		std::ifstream in(name_);
		char cur;
		in.get(cur);
		binTree* tree = new binTree;
		this->tree_ = tree;
		if (cur == '(') {
			readBinFile(tree, cur, in);
		}
		break;
	}
	case 'c': {
		std::cout << "Enter input data" << std::endl;
		char cur;
		char trash;
		scanf("%c", &trash);
		std::cin.get(cur);
		binTree* tree = new binTree;
		this->tree_ = tree;
		if (cur == '(') {
			readBin(tree, cur);
		}
	}
		break;
	}
}


void treeWork::readBin(binTree* tree, char sym) {
	if (sym == '('){
		arm* left = new arm;
		left = readArm(left);
		if (!left) {
			std::cout << "error in bin left" << std::endl;
			exit(1);
		}
		tree->setLeft(left);
		char cur;  
		std::cin.get(sym);
		if (sym != ' ') {
			std::cout << "error in bin" << std::endl;
			exit(1);
		}
		arm* right = new arm;
		right = readArm(right);
		if (!right) {
			std::cout << "error in bim right" << std::endl;
			exit(1);
		}
		tree->setRight(right);
		std::cin.get(sym);
		if (sym != ')') {
			std::cout << "error in ')' bin" << std::endl;
			exit(1);
		}
	}
	else {
		std::cout << "ERROR" << std::endl;
		exit(1);
	}
}

arm* treeWork::readArm(arm* arm_) {
	char cur;
	std::cin.get(cur);
	if (cur == '(') {
		int length;
		std::cin >> length;
		arm_->setLength(length);
		std::cin.get(cur);
		if (cur == '(') {
			arm_->setTag(true);
			node* node_ = new node;
			binTree* bin_ = new binTree;
			node_->setBinTree(bin_);
			arm_->setNode(node_);
			readBin(bin_, cur);
		}
		else if (cur == ' ') {
			arm_->setTag(false);
			node* node_ = new node;
			int weigth;
			std::cin >> weigth;
			node_->setWeight(weigth);
			arm_->setNode(node_);
		}
		std::cin.get(cur);
		if (cur != ')') {
			std::cout << "error ')' in arm" << std::endl;
			return nullptr;
		}
	}
	else {
		std::cout << "error arm" << std::endl;
		return nullptr;
	}
	return arm_;
}

void treeWork::readBinFile(binTree* tree, char sym, std::ifstream& in) {
	if (sym == '(') {
		arm* left = new arm;
		left = readArmFile(left, in);
		if (!left) {
			std::cout << "error in bin left" << std::endl;
			exit(1);
		}
		tree->setLeft(left);
		char cur;
		in.get(sym);
		if (sym != ' ') {
			std::cout << "error in bin" << std::endl;
			exit(1);
		}
		arm* right = new arm;
		right = readArmFile(right, in);
		if (!right) {
			std::cout << "error in bim right" << std::endl;
			exit(1);
		}
		tree->setRight(right);
		in.get(sym);
		if (sym != ')') {
			std::cout << "error in ')' bin" << std::endl;
			exit(1);
		}
	}
	else {
		std::cout << "ERROR";
		exit(1);
	}
}

arm* treeWork::readArmFile(arm* arm_, std::ifstream& in) {
	char cur;
	in.get(cur);
	if (cur == '(') {
		int length;
		in >> length;
		arm_->setLength(length);
		in.get(cur);
		if (cur == '(') {
			arm_->setTag(true);
			node* node_ = new node;
			binTree* bin_ = new binTree;
			node_->setBinTree(bin_);
			arm_->setNode(node_);
			readBinFile(bin_, cur, in);
		}
		else if (cur == ' ') {
			arm_->setTag(false);
			node* node_ = new node;
			int weigth;
			in >> weigth;
			node_->setWeight(weigth);
			arm_->setNode(node_);
		}
		in.get(cur);
		if (cur != ')') {
			std::cout << "error3";
			return nullptr;
		}
	}
	else {
		std::cout << "error4";
		return nullptr;
	}
	return arm_;
}

void treeWork::writeBin(binTree* tree) {
	
	if (!tree) {
		std::cout << "()" << std::endl;
		return;
	}

	std::cout << '(';
	writeArm(tree->getLeft());
	std::cout << ' ';
	writeArm(tree->getRight());
	std::cout << ')';
}

void treeWork::writeArm(arm* arm_) {
	node* node_ = arm_->getNode();
	if (!arm_) {
		std::cout << "()";
		return;
	}
	std::cout << '(';
	std::cout << arm_->getLength();
	if (!arm_->getTag()) {
		std::cout << ' ';
		std::cout << node_->getWeight();
	}
	else {
		writeBin(node_->getBinTree());
	}
	std::cout << ')';
}

binTree* treeWork::getTree() {
	return this->tree_;
}

unsigned int treeWork::W(binTree* bk) {
	unsigned int weigth_ = 0;
	int level = 0;
	tourBin(bk, level, weigth_);
	return weigth_;
}

void treeWork::tourBin(binTree* tree, int& level, unsigned int& weight_) {
	tourArm(tree->getLeft(), level, weight_);
	tourArm(tree->getRight(), level, weight_);
}

void treeWork::tourArm(arm* arm_, int& level, unsigned int& weight_) {
	level++;
	node* node_ = arm_->getNode();
	weight_ += node_->getWeight();
	outPut(level, node_->getWeight(), weight_);
	if (arm_->getTag()) {
		tourBin(node_->getBinTree(), level, weight_);
	}
	level--;
}

void treeWork::outPut(int level, int weight_, int allWeigth) {
	std::cout << "depth: " << level << " length: " << " summ of weight: " << allWeigth << std::endl;
}

treeWork::~treeWork(){
	delete this->tree_;
}