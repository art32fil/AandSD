#include <iostream>
#include <cstdlib>
#include "list.h"

using namespace std;

namespace list{

    struct Stack::node {
        base *hd;
        node *tl;

        node() {
            hd = nullptr; tl = nullptr;
        }
    };

    base Stack::pop() {
        if (topOfStack == nullptr) {
            cerr << "Error: pop (null) \n";
            exit(1);
        }
        else {
            node *oldTop = topOfStack;
            base r = *topOfStack->hd;
            topOfStack = topOfStack->tl;
            delete oldTop->hd;
            delete oldTop;
            return r;
        }
    }

    void Stack::push(const base &x) {
        node *p;
        p = topOfStack;
        topOfStack = new node;
        if (topOfStack != nullptr) {
            topOfStack->hd = new base;
            *topOfStack->hd = x;
            cout << "push -> " << x << endl;
            topOfStack->tl = p;
        }
        else {
            cerr << "Memory not enough\n"; exit(1);
        }
    }

    void Stack::destroy() {
        while (topOfStack != nullptr) {
            pop();
        }
    }
}
