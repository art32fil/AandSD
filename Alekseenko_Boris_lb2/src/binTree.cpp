#include "binTree.h"
void binTree::setLeft(arm* new_) {
	this->left = new_;
}

void binTree::setRight(arm* new_) {
	this->right = new_;
}

arm* binTree::getLeft() {
	return this->left;
}

arm* binTree::getRight() {
	return this->right;
}

binTree::~binTree() {
	delete this->left;
	delete this->right;
}
