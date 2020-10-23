#pragma once
#include "arm.h"
class arm;
class binTree {
public:
	~binTree();
	void setLeft(arm* new_);
	void setRight(arm* new_);
	arm* getLeft();
	arm* getRight();

private:
	arm* left = nullptr;
	arm* right = nullptr;
};