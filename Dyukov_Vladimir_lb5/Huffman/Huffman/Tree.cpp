#include "Tree.h"

void Tree::operator++ (int) {

	weight++;
	if (parent) (*parent)++;
}

void Tree::operator-- (int) {
	
	weight--;
	if (parent) (*parent)--;
}