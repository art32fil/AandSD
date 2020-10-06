#ifndef WORKSPACE_H
#define WORKSPACE_H

#define RED "\033[1;31m"
#define ORANGE "\033[1;33m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

#include <iostream>
#include <string>
#include <fstream>
#include "../Headers/Recursion.h"

using namespace std;

class Workspace{
public:
    Workspace();
    void ChooseInput();
    static string ClearSymbols(string line);
    static string Output(string line, bool isBrackets);
    void Console();
    void File(string inputFile, bool deepon = true);
    string line;
    string inputFile;
    Recursion recursion;
    ifstream input;
    ofstream output;
    bool isBrackets;
};

#endif
