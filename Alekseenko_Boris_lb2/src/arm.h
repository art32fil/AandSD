#pragma once
#include "node.h"
class node;
class arm {
private:
	int length = 0;
	bool tag = false;
	node* node_ = nullptr;
public:
	~arm();
	void setLength(int new_);
	void setTag(bool new_);
	void setNode(node* new_);
	int getLength();
	bool getTag();
	node* getNode();
};