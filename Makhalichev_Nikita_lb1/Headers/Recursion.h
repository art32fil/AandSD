#ifndef RECURSION_H
#define RECURSION_H

#include <string>
#include <iostream>

using namespace std;

class Recursion{
public:
    Recursion();
    bool Run(string line, int position = 0, int depth = 0, bool showDepth = true);
private:
    bool isBrackets;
};

#endif
