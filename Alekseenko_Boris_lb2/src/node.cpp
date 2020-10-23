#include "node.h"

void node::setWeight(int new_) {
	this->weight = new_;
}

void node::setBinTree(binTree* new_) {
	this->bin_ = new_;
}

int node::getWeight() {
	return this->weight;
}

binTree* node::getBinTree() {
	return this->bin_;
}

node::~node() {
	delete this->bin_;
}