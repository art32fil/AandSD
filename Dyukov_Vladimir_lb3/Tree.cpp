#include "Header.h"

Tree::Tree() {

	info = 0;
	left = nullptr;
	right = nullptr;
}

Tree::~Tree() {

	if (this->left) delete this->left;
	if (this->right) delete this->right;
}

std::istream& operator>>(std::istream& in, Tree** tree) {

	char symb;
	short brackets = 0;
	Tree* stack[100];
	stack[0] = nullptr;
	bool r = false;

	do {

		in >> symb;
		if (symb == '(') {

			stack[brackets] = new Tree;
			in >> stack[brackets]->info;
			if (brackets > 0) {

				if (stack[brackets - 1]->right) break;
				if ((stack[brackets - 1]->left && !stack[brackets - 1]->right) || r) stack[brackets - 1]->right = stack[brackets];
				if (!stack[brackets - 1]->left && !r) stack[brackets - 1]->left = stack[brackets];
			}
			brackets++;
			r = false;
		}
		else if (symb == ')') brackets--;
		else if (symb == 'N') r = true;
		else break;

	} while (brackets > 0);

	if (brackets == 0 && stack[0]) *tree = stack[0];
	else if (stack[0]) delete stack[0];
	return in;
}

std::ostream& operator<<(std::ostream& out, Tree* tree) {

	if (tree) {

		out << '(' << tree->info;
		if (tree->left) out << ' ' << tree->left;
		if (tree->right) {

			if (!tree->left) out << " N";
			out << ' ' << tree->right;
		}
		out << ')';
	}
	return out;
}