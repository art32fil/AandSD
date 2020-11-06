#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <fstream>

using namespace std;

class BinTree{
public:
    BinTree();
    BinTree *left;
    BinTree *right;
    char element;
    bool IsNull(BinTree *tree);
    BinTree *Left(BinTree *tree);
    BinTree *Right(BinTree *tree);
    char RootElement(BinTree *tree);
    void MakeElement(BinTree *tree, char element, BinTree *left, BinTree *right);
    void FunctionRead(BinTree *tree, string &line, int from, int to);
    void ReadTree(BinTree *tree, string &line);
    void Destroy(BinTree *tree);
    void Display(BinTree *tree, int n);
    void PostfixPrint(BinTree *tree);
    void FunctionPrint(BinTree *tree, string &res);
    void Diff(BinTree *tree);
private:
    string operands = "abcdefghijklmnopqrstuvwxyz01234567890";
    string operators = "+-*";
    string numbers = "0123456789";
};

#endif
