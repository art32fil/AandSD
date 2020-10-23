#pragma once
#include "binTree.h"
class binTree;
class node {
private:
	int weight = 0;
	binTree* bin_ = nullptr;
public:
	~node();
	void setWeight(int new_);
	void setBinTree(binTree* bin_);
	int getWeight();
	binTree* getBinTree();

};