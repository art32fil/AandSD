#include "Tree.h"

void Tree::operator++ (int) {

	weight++;
	if (parent) (*parent)++;
}

void Tree::operator-- (int) {
	
	weight--;
	if (parent) (*parent)--;
}

void Tree::inc_dep(int a) {

	depth += a;
	if (left) left->inc_dep(a);
	if (right) right->inc_dep(a);
}

void Tree::dec_dep(int a) {
	depth -= a;
	if (left) left->dec_dep(a);
	if (right) right->dec_dep(a);
}