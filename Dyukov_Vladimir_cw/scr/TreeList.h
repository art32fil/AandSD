#pragma once

#include <iostream>
#include <list>

#define ESC 0

class Tree;

class TreeList {

public:
	std::list<Tree*> list;

	TreeList();
	virtual ~TreeList();

	virtual char add(std::istream&, std::ostream&) = 0;
	void rebuild();
	void drawTree(std::ostream&, char);
	virtual void print(std::ostream& out, char sym, bool first = false) = 0;
};

class EncodeTreeList : public TreeList {

public:
	EncodeTreeList() : TreeList() {};

	virtual char add(std::istream&, std::ostream&);
	virtual void print(std::ostream& out, char sym, bool first = false);
};

class DecodeTreeList : public TreeList {

public:
	DecodeTreeList() : TreeList() {};

	virtual char add(std::istream&, std::ostream&);
	virtual void print(std::ostream& out, char sym, bool first = false);
};