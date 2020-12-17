#include "TreeList.h"
#include "Tree.h"
#include "Define.h"

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

//

TreeList::TreeList() {

	list.push_back(new Tree(0, '.', nullptr));
}

TreeList::~TreeList() {

	for (std::list<Tree*>::iterator i = list.begin(); i != list.end(); i++)
		delete* i;
}

void TreeList::add(char symb, std::ostream& out) {

	bool new_symb = true;

	for (std::list<Tree*>::iterator i = list.begin(); i != list.end(); i++)
		if ((*i)->data == symb) {

			(*(*i))++;
			new_symb = false;
		}

	if (new_symb) {

		Tree* esc = *(--list.end());
		esc->right = new Tree(symb, '1', esc);
		(*esc->right)++;
		esc->left = new Tree(0, '0', esc);
		list.push_back(esc->right);
		list.push_back(esc->left);
	}

	printSymCode(out, symb, new_symb);

	rebuild();
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
			(*max)--;

			// prev restore
			prev->left = test.left;
			if (prev->left) prev->left->parent = prev;
			prev->right = test.right;
			if (prev->right) prev->right->parent = prev;
			prev->data = test.data;
			(*prev)++;

			rebuild();

			break;
		}
		prev = *i;

		if (i == list.begin()) break;
	}
}

void TreeList::drawTree(sf::RenderWindow& window, sf::Font& font, int depth, Tree* tree, int x_pos) {

	if (tree->left) drawTree(window, font, depth + 1, tree->left, x_pos - TREE_CENT / pow(2, depth));
	if (tree->right) drawTree(window, font, depth + 1, tree->right, x_pos + TREE_CENT / pow(2, depth));

	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::White);
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(LEAF_SIZE, LEAF_SIZE));
	rect.setPosition(sf::Vector2f(x_pos, depth * LEAF_STEP));
	window.draw(rect);

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(25);
	text.setStyle(sf::Text::Bold);

	text.setString(tree->data);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(x_pos + 2, depth * LEAF_STEP));
	window.draw(text);

	text.setString(ItoS(tree->weight));
	text.setFillColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(x_pos + 2, depth * LEAF_STEP + LEAF_SIZE / 2));
	window.draw(text);

	text.setString(tree->code);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(sf::Vector2f(x_pos + 2 + LEAF_SIZE / 2, depth * LEAF_STEP));
	window.draw(text);
}

void TreeList::drawList(sf::RenderWindow& window, sf::Font& font) {

	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::White);
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(LEAF_SIZE, LEAF_SIZE));

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(25);
	text.setStyle(sf::Text::Bold);

	int j = 5;
	for (std::list<Tree*>::iterator i = list.begin(); i != list.end(); i++) {

		rect.setPosition(sf::Vector2f(j, WIND_SIZE_H - LEAF_SIZE - 5));
		window.draw(rect);

		text.setFillColor(sf::Color::Black);
		text.setPosition(sf::Vector2f(j + 2, WIND_SIZE_H - LEAF_SIZE - 5));
		text.setString((*i)->data);
		window.draw(text);

		text.setFillColor(sf::Color::Red);
		text.setPosition(sf::Vector2f(j + 2, WIND_SIZE_H - LEAF_SIZE / 2 - 5));
		text.setString(ItoS((*i)->weight));
		window.draw(text);

		j += LEAF_SIZE + 5;
	}
}

void TreeList::printSymCode(std::ostream& out, char sym, bool first) {

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