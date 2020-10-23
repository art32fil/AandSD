#pragma once
#include "arm.h"
#include "binTree.h"
#include <string>
#include <fstream>
#include <iostream>

class treeWork {
public:
	void startReading();
	void readBin(binTree* tree, char sym); // Взаимно рекурсивные
	arm* readArm(arm* arm_);
	void readBinFile(binTree* tree, char sym, std::ifstream& in);
	arm* readArmFile(arm* arm_, std::ifstream& in);
	void writeArm(arm* arm_);
	void writeBin(binTree* tree);
	void outPut(int level, int weight_, int allWeigth);
	void tourArm(arm* arm_, int& level, unsigned int& weight_);
	void tourBin(binTree* tree, int& level, unsigned int& weight_);
	binTree* getTree();
	unsigned int W(binTree* bk);
private:
	binTree* tree_;
};