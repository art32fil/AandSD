#ifndef WORKSPACE_H
#define WORKSPACE_H

#define RED "\033[1;31m"
#define ORANGE "\033[1;33m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include "Node.h"

using namespace std;

class Workspace{
public:
    Workspace();
    void ChooseInput();
    void Console();
    void File(string inputFile);
    static string ClearSymbols(string line);
    string TransformLine(string line);
    string line;
    string inputFile;
    ifstream input;
    ofstream output;
    bool isBrackets;
    lisp x;
};

#endif
