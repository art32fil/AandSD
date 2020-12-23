#ifndef BINTREE_H
#define BINTREE_H
#include "libs.h"

class BinTree  {
    std::string data="";	//string of coded simbols
    int sum=0;		//summ of frequency
    BinTree* left=nullptr;	//left tree
    BinTree* right= nullptr;	//right tree
    std::string code="";	//current code
public:
    std::string& Get_Code(){
            return this->code;
        }
        void Set_Code(std::string& str){
            this->code=str;
        }
        std::string& Get_Data(){
            return this->data;
        }
        BinTree(std::string& str){
            this->data=str;
        }
        ~BinTree(){
            if(left!=nullptr){
                delete left;
            }
            if(right!=nullptr){
                delete right;
            }
        }
        void SetSum(int s){
            this->sum=s;
        }
        int GetSum(){
            return this->sum;
        }
        void SetLeft(BinTree* tree){
            this->left=tree;
        }
        void SetRight(BinTree* tree){
            this->right=tree;
        }
        void Create_left(std::string& str) {
            this->left = new BinTree(str);
        }
        void Create_right(std::string& str){
            this->right = new BinTree(str);
        }
        void Set_Str(std::string& str){
            this->data=str;
        }
        BinTree* Get_left(){
            return this->left;
        }
        BinTree* Get_right(){
            return this->right;
        }
};

#endif // BINTREE_H
