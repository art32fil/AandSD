#include "NodeTree.h"
#include "Tree.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <climits>
#include <cstdlib>
#include <cstring>



using namespace std;

template<typename T> class Tree;

int main()
{
    vector<long int> vec = treeVector();
    
    Tree<long int> binTree(vec);

    binTree.printTree(binTree.getRoot());
    int flag = true;
    
    long int deleteData;
    cout<<"Enter element to delete: "<<endl;
    cin>>deleteData;
    binTree.deleteData(deleteData);
    binTree.printTree(binTree.getRoot());
        
    long int insertData;
    cout<<"Enter element to insert: "<<endl;
    cin>>insertData;
    binTree.insertData(insertData);
    binTree.printTree(binTree.getRoot());
    
    cout<<"Let's start the Research!"<<endl;
    vector<long int> researchVec = createRandVec(100);

    ofstream researchDepth("Research.txt");
    srand(time(0));
    vector<long int> testVec = {1};
    Tree<long int> researchTree(testVec);
    while(researchVec.size()>0){
        int i = researchVec.size() - 1;
        researchTree.insertData(researchVec.at(i));
        researchVec.pop_back();
        researchDepth<<researchTree.getDataVecSize()<<" "<<researchTree.depth(researchTree.getRoot())<<endl;
        if(i%1000==0){
            cout<<i<<endl;
        }
    }
    researchDepth.close();
    cout<<"OK"<<endl;
    

    return 0;
}

