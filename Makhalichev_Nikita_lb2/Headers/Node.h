#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>

using namespace std;

typedef char Base;

class  s_expr;

class two_ptr{
public:
	s_expr *hd;
	s_expr *tl;
};

class s_expr{
public:
	bool tag;
	union {
		Base atom;
		two_ptr pair;
	} node;
};

typedef s_expr *lisp;
lisp head(const lisp s);
lisp tail(const lisp s);
lisp cons(const lisp h, const lisp t);
lisp make_atom(const Base x);
bool isAtom(const lisp s);
bool isNull(const lisp s);
void destroy(lisp s);
Base getAtom(const lisp s);
void read_lisp(lisp& y, string *line = NULL);
void read_s_expr(Base prev, lisp& y, string *line);
void read_seq(lisp& y, string *line);
void write_lisp(const lisp x, string &out);
void write_seq(const lisp x,  string &out);
int depth(lisp x, int d, bool &isNotEmpty);
int depth_search(lisp x, int deep = 0);

#endif
