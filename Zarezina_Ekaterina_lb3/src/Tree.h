#ifndef TREE_H
#define TREE_H

#include "NodeTree.h"
#include <sstream>
#include <iostream>
#include <vector>
#define EMPTY '_'

using namespace std;

template<typename T> class Tree{
    
    NodeTree<T>* _root;
    
    void deleteFunc(NodeTree<T>* node){
        if(node!=nullptr){
            deleteFunc(node->_left);
            deleteFunc(node->_right);
            
            delete node;
        }
    }
    
    
    
public:
    Tree(): _root(nullptr){}
    
    void readTree(NodeTree<T>**root, vector<long int>& vec){
        
        
        int data = vec.back();
        vec.pop_back();
        *root = new NodeTree<T>(data);
        if(data == 0){
            return;
        }
        
        readTree(&((*root)->_left),vec);
        readTree(&(*root)->_right,vec);
    }
    
    NodeTree<T>* getRoot(){
        return _root;
    }
    
    void setRoot(NodeTree<T>* root){
        _root = root;
    }
    
    void preorder(NodeTree<T>*root){
        if(root == nullptr){
            cout<<"Sorry, root == nullptr"<<endl;
        } else {
            if(root->getData() !=0){
                cout<<root->_data<<" ";
                preorder(root->_left);
                preorder(root->_right);
            }
        }
    }
    
    ~Tree(){
        deleteFunc(_root);
    }
    
    void isBinSearch(NodeTree<T>** node,long int& min, bool& flagBS){
        long int data = (*node)->getData();
        if(node == nullptr){
            cout<<"Sorry, node == nullptr"<<endl;
        }
        if((data != 0)&&(flagBS == true)){
            
        isBinSearch(&((*node)->_left), min, flagBS);
        flagBS &= (*node)->getData() > min;
        min = (*node)->getData();
        isBinSearch(&((*node)->_right), min, flagBS);
        }
    }
    
    void isPyramide(NodeTree<T>** node, bool& flagPyr){
        long int currData = (*node)->getData();
        long int leftData = (*node)->_left->getData();
        long int rightData = (*node)->_right->getData();
        if((leftData == 0)&&(rightData == 0)){
            return;
        }
        if(leftData == 0){
            flagPyr &= currData>=rightData;
            isPyramide(&((*node)->_right),flagPyr);
        } else if(rightData == 0){
            flagPyr &= currData>=leftData;
            isPyramide(&((*node)->_left),flagPyr);
        } else {
            flagPyr &= (currData>=leftData)&&(currData>=rightData);
            isPyramide(&((*node)->_left),flagPyr);
            isPyramide(&((*node)->_right),flagPyr);
        }
    }
    
};

vector<long int> treeVector(){
    long int num;
    vector<long int> vec;
    vector<long int> vecRes;
    cout<<"Enter your Tree:"<<endl;
    string n;
    do{ 
        cin >> n; 
        num = stoi(n);
        vec.push_back(num);
    }while(cin.peek() != '\n');
    
    for(int i = vec.size()-1; i>-1;i--){
    
        vecRes.push_back(vec.at(i));
    }
    
    return vecRes;
}

void printResult(bool flagBS, bool flagPyr){
    cout<<"\n\tis Binary Search Tree?  -  ";
    if(flagBS){
        cout<<"YES"<<endl;
    } else {
        cout<<"NO"<<endl;
    }
    cout<<"\tis Pyramide Tree?  -  ";
    if(flagPyr){
        cout<<"YES"<<endl;
    } else {
        cout<<"NO"<<endl;
    }
}


#endif
