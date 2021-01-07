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
    
    Tree<long int> binTree(vec);

    binTree.printTree(binTree.getRoot());
    int flag = true;
    
    while(flag == true){
        long int deleteData;
        cout<<"Enter element to delete: "<<endl;
        cin>>deleteData;
    
        binTree.deleteData(deleteData);
    
        binTree.printTree(binTree.getRoot());
        
        char way;
        cout<<"Do you want to delete another element? y - yes, n - no"<<endl;
        cin>>way;
        if(way == 'y'){
            flag = true;
        } else{
            flag = false;
            if(way !='n'){
                cout<<"You entered a wrong letter!"<<endl;
            }
        }
    }

    return 0;
}

