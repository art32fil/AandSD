#pragma once

class Tree {

public:
	Tree* left;
	Tree* right;
	Tree* parent;
	char data;
	char code;
	int weight;
	int depth;

	Tree(char _d, char _c, Tree* _p, int _t) : data(_d), weight(0), left(nullptr), right(nullptr), parent(_p), code(_c), depth(_t) {}

	void operator++ (int);
	void operator-- (int);
	void inc_dep(int);
	void dec_dep(int);
};