#pragma once

class Tree {

public:
	Tree* left;
	Tree* right;
	Tree* parent;
	char data;
	char code;
	int weight;

	Tree(char _d, char _c, Tree* _p) : data(_d), weight(0), left(nullptr), right(nullptr), parent(_p), code(_c) {}

	void operator++ (int);
	void operator-- (int);
};