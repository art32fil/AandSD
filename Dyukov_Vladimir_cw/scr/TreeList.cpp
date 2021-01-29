#include "TreeList.h"
#include "Tree.h"

std::string ItoS(int num) {

	int sym;
	std::string str;

	if (!num) str = "0";

	while (num) {

		sym = num % 10;

		if (sym == 0) str += '0';
		if (sym == 1) str += '1';
		if (sym == 2) str += '2';
		if (sym == 3) str += '3';
		if (sym == 4) str += '4';
		if (sym == 5) str += '5';
		if (sym == 6) str += '6';
		if (sym == 7) str += '7';
		if (sym == 8) str += '8';
		if (sym == 9) str += '9';

		num = num / 10;
	}

	for (int i = 0; i < str.length() / 2; i++) {

		char reserve = str[i];
		str[i] = str[str.length() - i - 1];
		str[str.length() - i - 1] = reserve;
	}

	return str;
}

// Interface

TreeList::TreeList() {

	list.push_back(new Tree(ESC, '.', nullptr, 1));
}

TreeList::~TreeList() {

	for (std::list<Tree*>::iterator i = list.begin(); i != list.end(); i++)
		delete* i;
}

void TreeList::rebuild() {

	Tree* prev = *(--list.end());
	Tree* max = nullptr;

	for (std::list<Tree*>::iterator i = --list.end(); true; i--) {

		if (prev->weight > (*i)->weight) max = prev;
		if (max && (max->weight <= (*i)->weight)) {

			Tree test = *max;

			// max restore
			max->left = prev->left;
			if (max->left) max->left->parent = max;
			max->right = prev->right;
			if (max->right) max->right->parent = max;
			max->data = prev->data;
			max->dec_dep(max->depth - prev->depth);
			(*max)--;

			// prev restore
			prev->left = test.left;
			if (prev->left) prev->left->parent = prev;
			prev->right = test.right;
			if (prev->right) prev->right->parent = prev;
			prev->data = test.data;
			prev->inc_dep(prev->depth - test.depth);
			(*prev)++;

			rebuild();

			break;
		}
		prev = *i;

		if (i == list.begin()) break;
	}
}

void TreeList::drawTree(std::ostream& out, char sym) {

	out << "Binary tree, showing the code of the elements after adding: '" << sym << "'\n\n";

	int tree_on_lvl = 1;
	Tree** trees = new Tree*[1];
	trees[0] = *list.begin();
	int depth = (*(--list.end()))->depth;

	while (depth) {

		int num = 0;
		for (int i = 0; i < depth - 1; i++)
			num = num + 3 * pow(2, i);

		for (int i = 0; i < tree_on_lvl; i++) {
			

			for (int j = 0; j < num; j++) out << ' ';
			if (trees[i] != nullptr) {

				if (trees[i]->data == ESC) out << "[~ ";
				else out << "[" << trees[i]->data << " ";
				out << trees[i]->weight << " ";
				out << trees[i]->code << "]";
			}
			else out << "       ";
			for (int j = 0; j < num; j++) out << ' ';
		}
		depth--;
		out << "\n\n\n";

		tree_on_lvl = tree_on_lvl * 2;
		Tree** n_trees = new Tree * [tree_on_lvl];
		for (int i = 0; i < tree_on_lvl; i++) {

			if (trees[i / 2] == nullptr) n_trees[i] = nullptr;
			else {

				if (i % 2) n_trees[i] = trees[i / 2]->right;
				else n_trees[i] = trees[i / 2]->left;
			}
		}
		delete[] trees;
		trees = n_trees;
	}

	out << "List of sorting elements: ";
	for (std::list<Tree*>::iterator i = list.begin(); i != list.end(); i++) {

		if ((*i)->data == ESC) out << "[~ " << (*i)->weight << "] ";
		else out << "[" << (*i)->data << " " << (*i)->weight << "] ";
	}

	out << "\n\nHint: [symbol weight code] ; '~' - mean ESC\n\n\n\n";
}

// Encode

char EncodeTreeList::add(std::istream& in, std::ostream& out) {

	bool new_symb = true;
	char symb;
	in.get(symb);
	if (in.eof()) return 0;

	for (std::list<Tree*>::iterator i = list.begin(); i != list.end(); i++)
		if ((*i)->data == symb) {

			(*(*i))++;
			new_symb = false;
		}

	if (new_symb) {

		Tree* esc = *(--list.end());
		esc->right = new Tree(symb, '1', esc, esc->depth + 1);
		(*esc->right)++;
		esc->left = new Tree(ESC, '0', esc, esc->depth + 1);
		list.push_back(esc->right);
		list.push_back(esc->left);
	}

	print(out, symb, new_symb);
	rebuild();

	return symb;
}

void EncodeTreeList::print(std::ostream& out, char sym, bool first) {

	std::string code = "";
	Tree* end = nullptr;
	for (std::list<Tree*>::iterator i = list.begin(); i != list.end(); i++) {

		if ((*i)->data == sym) {

			end = (*i);
			break;
		}
	}

	if (end) {

		if (first) end = end->parent;

		for (end; end->parent; end = end->parent) {

			code += end->code;
		}

		for (int i = 0; i < code.length() / 2; i++) {

			char reserve = code[i];
			code[i] = code[code.length() - i - 1];
			code[code.length() - i - 1] = reserve;
		}

		out << code;

		if (first) {

			int k = 128;
			for (int i = 7; i > -1; i--) {

				out << ((sym & k) >> i);
				k = k >> 1;
			}
		}
	}
}

// Decode

char DecodeTreeList::add(std::istream& in, std::ostream& out) {

	char res = 0;
	Tree* tree = *list.begin();

	while (tree && tree->left) {

		in.get(res);
		if (in.eof()) return 0;
		switch (res) {
		case 49:
			tree = tree->right;
			break;
		case 48:
			tree = tree->left;
			break;
		default:
			tree = nullptr;
			break;
		}
	}

	if (!tree) return 0;
	if (tree->data != 0) (*tree)++;
	else {

		res = 0;
		for (int i = 0; i < 8; i++) {

			res = res * 2 + in.get() - 48;
			if (in.eof()) return 0;
		}

		Tree* esc = *(--list.end());
		esc->right = new Tree(res, '1', esc, esc->depth + 1);
		(*esc->right)++;
		esc->left = new Tree(ESC, '0', esc, esc->depth + 1);
		list.push_back(esc->right);
		list.push_back(esc->left);
		tree = tree->right;
	}

	print(out, tree->data, 0);
	rebuild();

	return tree->data;
}

void DecodeTreeList::print(std::ostream& out, char sym, bool first) {

	out << sym;
}