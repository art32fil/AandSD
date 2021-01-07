#ifndef TREE_H
#define TREE_H

#include "NodeTree.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void createTabs(int level){
    for(int i = 0; i<level;i++){
        cout<<"      ";
    }
}



template<typename T> class Tree{
    
    std::shared_ptr<NodeTree<T>> _root;
    std::vector<T> _dataVec;
    
    void deleteFunc(NodeTree<T>* node){
        if(node!=nullptr){
            deleteFunc(node->_left);
            deleteFunc(node->_right);
            
            delete node;
        }
    }
    
    std::shared_ptr<NodeTree<T>> createTree(std::shared_ptr<NodeTree<T>> parent ,int numOfElem, int& ind){
        
        if(numOfElem == 0){ return nullptr;}
            
        int leftNum = numOfElem/2;
        int rightNum = numOfElem - leftNum - 1;
        std::shared_ptr<NodeTree<T>> curRoot = std::make_shared<NodeTree<T>>(nullptr,nullptr,parent,-1);
        curRoot->_left = createTree(curRoot,leftNum, ind);
        curRoot->_ind = ind;
        ind++;
        curRoot->_right = createTree(curRoot,rightNum, ind);
        
        return curRoot;
    }
    
    
public:
    Tree(vector<T>& vec){
        int ind = 0;
        _dataVec = vec;
        _root = createTree(nullptr,_dataVec.size(),ind);
    }
    ~Tree() = default;
    
    
    std::shared_ptr<NodeTree<T>> getRoot(){
        return _root;
    }
    
    int depth(const std::shared_ptr<NodeTree<T>>& root){
        if(root == nullptr){return 0;}
        
        if (depth(root->_right)>depth(root->_left)){ 
            return depth(root->_right)+1;
        } else { 
            return depth(root->_left)+1; 
        }
    }
    
    void printLevel(const std::shared_ptr<NodeTree<T>>& currNode, int level){
        if(currNode == nullptr){
            cout<<"  _ ";
            return;
        }
        if(level > 0){
            printLevel(currNode->_left, level-1);
            printLevel(currNode->_right, level-1);
        } else if (level == 0){
            cout<<"   |"<<_dataVec.at(currNode->_ind)<<"|    ";
        }
    }
    
    void printTree(const std::shared_ptr<NodeTree<T>>& currNode){
        if(currNode == nullptr){return;}
        int depth = this->depth(this->getRoot());
        for(int i = 0; i<depth; i++){
            createTabs(depth-i);
            printLevel(currNode, i);
            cout<<endl;
        }
    }
    
    bool find(const std::shared_ptr<NodeTree<T>>& currNode, T findData){
        if(currNode == nullptr){ return false;}
        
        if(findData == _dataVec.at(currNode->_ind)){ return true;}
        
        if(findData < _dataVec.at(currNode->_ind)){
            return(currNode->_left, findData);
        } else { return (currNode->_right, findData);}
    }
    
    void deleteData(T deleteData){
        if(find(_root,deleteData) == false){
            cout<<"The data to delete wasn't found!"<<endl;
            return;
        }
        
        typename std::vector<T>::iterator iter;
        iter = std::find(_dataVec.begin(),_dataVec.end(), deleteData);
        _dataVec.erase(iter);
        int ind = 0;
        _root = createTree(nullptr, _dataVec.size(),ind);
        
    }
    
    void insertData(T insertData){
        _dataVec.push_back(insertData);
        std::sort(_dataVec.begin(),_dataVec.end());
        int ind = 0;
        _root = createTree(nullptr, _dataVec.size(),ind);
    }
    
    int getDataVecSize(){
        return _dataVec.size();
    }
    
};

vector<long int> createRandVec(long int size){
    srand(time(0));
    vector<long int> researchVec;
    cout<<"Ctreated Vector: ";
    for(int i = 0; i<size; i++){
        long int data = rand()%1500 + 1;    
        researchVec.push_back(data);
    }
    return researchVec;
}

vector<long int> treeVector(){
    long int num;
    vector<long int> vec;
    cout<<"Enter your Tree:"<<endl;
    string n;
    do{ 
        cin >> n; 
        num = stoi(n);
        vec.push_back(num);
    }while(cin.peek() != '\n');
    
    std::sort(vec.begin(),vec.end());
    
    return vec;
}


#endif
