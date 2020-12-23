#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <cctype>

#include <iostream>

using namespace std;

template<typename Elem>
struct Symbol{
    Symbol(): link(nullptr), count(1), deleted(false) {}

    Elem key;
    unsigned count;
    Symbol* link;
    bool deleted;
};

ostream& operator <<(ostream& out, Symbol<char>& symb);

ostream& operator <<(ostream& out, Symbol<char>* symb);

#endif // ELEMENTS_H
