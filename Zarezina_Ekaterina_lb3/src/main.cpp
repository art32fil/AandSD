#include "NodeTree.h"
#include "Tree.h"

#include <iostream>
#include <sstream>
#include <climits>



using namespace std;

template<typename T> class Tree;

int main()
{
    vector<long int> vec = treeVector();
    Tree<long int>*binTree = new Tree<long int>();
    NodeTree<long int> *root = binTree->getRoot();
    binTree->readTree(&root,vec);
    binTree->setRoot(root);
    long int min = LONG_MIN;
    bool flagBS = true;
    bool flagPyr = true;
    binTree->isBinSearch(&root,min, flagBS);
    binTree->isPyramide(&root, flagPyr);
    printResult(flagBS,flagPyr);
    

    return 0;
}

