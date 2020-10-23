#ifndef TESH_H
#define TESH_H

#include <iostream>
#include <dirent.h>
#include <string>
#include "Workspace.h"

using namespace std;

class Test{
public:
    Test();
    static void Run();
    void File(char *name);
    void Compare(string inputFile);
    string lineOutput;
    string lineAnswers;
    string inputFile;
    string directory;
    ifstream inputFromOutput;
    ifstream inputFromAnswers;
    Workspace workspace;
};

#endif
