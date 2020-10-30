#include <iostream>
#include <stack>
#include <string>
#include <ctype.h>
#include <fstream>

using namespace std;

template<typename T>
class BinTree{
protected:
    template<typename U>
    class Node{
    public:
        U value;
        Node<U>* left = nullptr;
        Node<U>* right = nullptr;
        
        static void setVal(Node<U>** node, U value){
            if(*node){
                (*node)->value = value;
            } 
            else {
                *node = new Node<U>;
                (*node)->value = value;
            }
        }
    };

    Node<T>* data = nullptr;

public:
    BinTree(){}
    
    friend ostream& operator<<(ostream& out, const BinTree<T>& bt){
        
        stack<BinTree::Node<T>*> st;
        if(bt.data){
            st.push(bt.data);
        }

        while(!st.empty()){
            auto node = st.top();
            st.pop();
            out << '{' << node->value << '}';
            if(node->right)
                st.push(node->right);
            if(node->left)
                st.push(node->left);
        }
        return out;
        
    }

    
    
    void readTree(string& line, int& cur, int& len, Node<T>** node){
        if(cur < len){
            Node<T>::setVal(node, 0);
            if(isalnum(line[cur])){
                Node<T>::setVal(node, line[cur]);
                //cout << line[cur];
                cur++;
                
            } else if (line[cur] == '(') {
                //cout << line[cur];
                cur++;
                readTree(line, cur, len, &((*node)->left));
               
                //cout << line[cur];
                Node<T>::setVal(node, line[cur]);
                cur++;
                readTree(line, cur, len, &((*node)->right));
                
                //cout <<line[cur];
                cur++;
            } 
            
        } else {
            return;
        }
    }

    void read(string& line, int& cur, int& len){
        readTree(line, cur, len, &data);
    }

    bool isFormula(Node<T>** node){
        Node<T>* root = *node;
        if (root->left->value == '+' && root->right && isalnum(root->right->value) ){
            Node<T>* lElem = root->left;
            if(lElem->left && lElem->right){
                return true;
            }
            else{
                return false;
            }
        }
        else if(root->left && root->right->value == '+' && isalnum(root->left->value)){
            Node<T>* rElem = root->right;
            if(rElem->left && rElem->right){
                return true;
            }
            else{
                return false;
            }

        }
        else{
            return false;
        }
    }

    void change(Node<T>** root){
        Node<T>::setVal(root, '+');
        if((*root)->left->value == '+'){
            Node<T>::setVal(&((*root)->right->right), (*root)->right->value);
            Node<T>::setVal(&((*root)->left), '*');
            Node<T>::setVal(&((*root)->right->left), (*root)->left->right->value);
            Node<T>::setVal(&((*root)->right), '*');
            Node<T>::setVal(&((*root)->left->right), (*root)->right->right->value);
        }
        else{
            Node<T>::setVal(&((*root)->left->left), (*root)->left->value);
            Node<T>::setVal(&((*root)->left), '*');
            Node<T>::setVal(&((*root)->left->right), (*root)->right->left->value);
            Node<T>::setVal(&((*root)->right->left), (*root)->left->left->value);
            Node<T>::setVal(&((*root)->right), '*');
            
        }
        
    }

    void InOrderTraversal(Node<T>** node){
        if (*node){
            InOrderTraversal(&((*node)->left));
            if(((*node)->value == '*') && (this->isFormula(node))){
                change(node);
            }
            InOrderTraversal(&((*node)->right));
        }
        else{
            return;
        }
    }

    void traverse(){
        InOrderTraversal(&(this->data));
    }

    void PrintInOrderTraversal(Node<T>* node, int k){
        if (node){
            if (k == 1){
                cout << "(";
            }
            PrintInOrderTraversal(node->left, 1);
            
            cout << node->value ;
            
            PrintInOrderTraversal(node->right, 2);
            if (k == 2){
                cout << ")";
            }
        }
        else{
            return;
        }
    }

    void print(){
        PrintInOrderTraversal(this->data, 0);
        cout << "\n";
    }

    void CleanInOrder(Node<T>* node){
        if (node){
            CleanInOrder(node->left);
            CleanInOrder(node->right);
            delete node;
            
        }
        else{
            return;
        }
    }

    void clean(){
        CleanInOrder(this->data);
    }
};

int main(){
    string file_name;
    cout << "Enter the name of an input file: " << endl;
    getline(cin, file_name);
    ifstream input(file_name);
    if (!input){
        cout << "You haven't entered correct input file." << endl;
    }
    else{
        cout << "Binary tree traverse:" << endl;
        string line;
        while(getline(input, line)){
            int len = line.length();
            int cur = 0;
            BinTree<char> bt1;
            bt1.read(line, cur, len);
            bt1.print();
            bt1.traverse();
            bt1.print();
            bt1.clean();
            
        }
    }
    return 0;
}