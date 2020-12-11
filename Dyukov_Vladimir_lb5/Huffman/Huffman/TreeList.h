#pragma once

#include <iostream>
#include <list>
#include "SFML/Graphics.hpp"

class Tree;

class TreeList {

public:
	std::list<Tree*> list;

	TreeList();

	~TreeList();

	void add(char, std::ostream&);

	void rebuild();

	void drawTree(sf::RenderWindow& window, sf::Font& font, int depth, Tree* tree, int x_pos);

	void drawList(sf::RenderWindow& window, sf::Font& font);

	void printSymCode(std::ostream& out, char sym, bool first = false);
};