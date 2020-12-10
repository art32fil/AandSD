#ifndef ELEMENTS_H
#define ELEMENTS_H

template<typename Elem>
struct Symbol{
    Symbol(): link(nullptr), count(1) {}

    Elem key;
    unsigned count;
    Symbol* link;
};

#endif // ELEMENTS_H
