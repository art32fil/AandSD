#include "Header.h"


TwoTree::TwoTree() : first(nullptr), second(nullptr) {}

TwoTree::TwoTree(Tree* f, Tree* s) : first(f), second(s) {}

bool TwoTree::isEqual(Tree* f, Tree* s) {

	if (f && s) {

		if (f->info == s->info) return (isEqual(f->left, s->left) && isEqual(f->right, s->right));
		else return false;
	}
	if (f || s) return false;
	return true;
}

bool TwoTree::isEqual() {

	Tree* f = this->first;
	Tree* s = this->second;

	if (f && s) {

		if (f->info == s->info) return (isEqual(f->left, s->left) && isEqual(f->right, s->right));
		else return false;
	}
	if (f || s) return false;
	return true;
}

bool TwoTree::isMirrorEqual(Tree* f, Tree* s) {

	if (f && s) {

		if (f->info == s->info) return (isMirrorEqual(f->left, s->right) && isMirrorEqual(f->right, s->left));
		else return false;
	}
	if (f || s) return false;
	return true;
}

bool TwoTree::isMirrorEqual() {

	Tree* f = this->first;
	Tree* s = this->second;

	if (f && s) {

		if (f->info == s->info) return (isMirrorEqual(f->left, s->right) && isMirrorEqual(f->right, s->left));
		else return false;
	}
	if (f || s) return false;
	return true;
}

bool TwoTree::isSuch(Tree* f, Tree* s) {

	if (f && s) return (isSuch(f->left, s->left) && isSuch(f->right, s->right));
	if (f || s) return false;
	return true;
}

bool TwoTree::isSuch() {

	Tree* f = this->first;
	Tree* s = this->second;

	if (f && s) return (isSuch(f->left, s->left) && isSuch(f->right, s->right));
	if (f || s) return false;
	return true;
}

bool TwoTree::isMirrorSuch(Tree* f, Tree* s) {

	if (f && s) return (isSuch(f->left, s->right) && isSuch(f->right, s->left));
	if (f || s) return false;
	return true;
}

bool TwoTree::isMirrorSuch() {

	Tree* f = this->first;
	Tree* s = this->second;

	if (f && s) return (isSuch(f->left, s->right) && isSuch(f->right, s->left));
	if (f || s) return false;
	return true;
}

void TwoTree::printTrees(std::ostream& out) {

	out << first << '\n' << second << '\n';
}