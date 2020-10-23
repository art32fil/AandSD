#include "arm.h"

void arm::setLength(int new_) {
	this->length = new_;
}

void arm::setTag(bool new_) {
	this->tag = new_;
}

void arm::setNode(node* new_) {
	this->node_ = new_;
}

int arm::getLength() {
	return this->length;
}

bool arm::getTag() {
	return this->tag;
}

node* arm::getNode() {
	return this->node_;
}

arm:: ~arm() {
	delete this->node_;
}