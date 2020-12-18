#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#define TYPE int

using namespace std;

template<typename T>
class Node{
public:
    Node(T elem);
    T key;
    int height;
    Node *left;
    Node *right;
};

template<typename T>
Node<T>::Node(T elem){
    this->key = elem;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}

template<typename T>
class AVLTree{
public:
    AVLTree();
    Node<T> *root;
    std::map<T, int> counter;
    void Read();
    Node<T> *MakeNode(Node<T> *tree, T elem);
    Node<T> *Balance(Node<T> *tree);
    int BalanceFactor(Node<T> *tree);
    int Height(Node<T> *tree);
    void UpdateHeight(Node<T> *tree);
    Node<T> *RotateLeft(Node<T> *tree);
    Node<T> *RotateRight(Node<T> *tree);
    void Display(Node<T> *tree, int depth);
    void Find(Node<T> *tree, T elem);
};

template<typename T>
AVLTree<T>::AVLTree(){
    root = NULL;
}

template<typename T>
void AVLTree<T>::Read(){
    TYPE elem = 0;
    string str;
    cout << "Please, enter tree elements: ";
    getline(cin, str);
	istringstream stream(str);
    while (stream >> elem){
        cout << "\n-Inserting " << elem << "...\n" << endl;
        root = MakeNode(root, elem);
        Display(root, 0);
    }
}

template<typename T>
Node<T> *AVLTree<T>::MakeNode(Node<T> *tree, T elem){
	if (tree == NULL) {
        counter[elem] = 1;
        return new Node<T>(elem);
	} else if (elem < tree->key){
		tree->left = MakeNode(tree->left, elem);
	} else if (elem > tree->key){
		tree->right = MakeNode(tree->right, elem);
	} else {
        counter.at(elem)++;
    }
    return Balance(tree);
}

template<typename T>
Node<T> *AVLTree<T>::Balance(Node<T> *tree){
    UpdateHeight(tree);
	if (BalanceFactor(tree) == -2){
		if (BalanceFactor(tree->left) > 0)
			tree->left = RotateLeft(tree->left);
		return RotateRight(tree);
	}
	if (BalanceFactor(tree) == 2){
		if (BalanceFactor(tree->right) < 0)
			tree->right = RotateRight(tree->right);
		return RotateLeft(tree);
	}
	return tree;
}

template<typename T>
Node<T> *AVLTree<T>::RotateLeft(Node<T> *tree){
    cout << "--Rotating left next part of tree:\n" << endl;
    Display(tree, 0);
    Node<T> *newtree = tree->right;
    tree->right = newtree->left;
    newtree->left = tree;
    UpdateHeight(tree);
    UpdateHeight(newtree);
    cout << "\n--Part of tree after left rotating:\n" << endl;
    Display(newtree, 0);
    cout << "\n-----------------------------------\n\n";
    return newtree;
}

template<typename T>
Node<T> *AVLTree<T>::RotateRight(Node<T> *tree){
    cout << "--Rotating right next part of tree:\n" << endl;
    Display(tree, 0);
    Node<T> *newtree = tree->left;
    tree->left = newtree->right;
    newtree->right = tree;
    UpdateHeight(tree);
    UpdateHeight(newtree);
    cout << "\n--Part of tree after right rotating:\n" << endl;
    Display(newtree, 0);
    cout << "\n-----------------------------------\n\n";
    return newtree;
}

template<typename T>
int AVLTree<T>::BalanceFactor(Node<T> *tree){
    return Height(tree->right) - Height(tree->left);
}

template<typename T>
int AVLTree<T>::Height(Node<T> *tree){
    if (tree != NULL){
        return tree->height;
    }
    return 0;
}

template<typename T>
void AVLTree<T>::UpdateHeight(Node<T> *tree){
	tree->height = max(Height(tree->left), Height(tree->right))+1;
}

template<typename T>
void AVLTree<T>::Display(Node<T> *tree, int depth){
    for (int i = 0; i < depth; i++){
        cout << ". ";
    }
    if (tree == NULL){
        cout << "(empty)" << endl;
    }
    if (tree != NULL){
        cout << tree->key << " (" << counter[tree->key] << ')' << endl;
        Display(tree->left, depth + 1);
        Display(tree->right, depth + 1);
    }
}

template<typename T>
void AVLTree<T>::Find(Node<T> *tree, T elem){
    if (counter[elem]){
        cout << "-This element is contained " << counter[elem] << " time(s)" << std::endl;
    } else {
        cout << "-There is no element = " << elem << std::endl;
    }
    cout << "-Inserting " << elem << "..." << endl;
    root = MakeNode(root, elem);
}

int main(){
    AVLTree<TYPE> tree;
    tree.Read();
    TYPE elem = 0;
    string continue_;
    string show_;
    do{
        cout << "\nDo you want to see current tree? ('n' if you don't) - ";
        getline(cin, show_);
        if (show_[0] != 'n'){
            cout << "\n__CURRENT_TREE__" << endl;
            tree.Display(tree.root, 0);
        }
        cout << "\nDo you want to continue? ('n' if you don't) - ";
        getline(cin, continue_);
        if (continue_[0] != 'n'){
            cout << "Please, enter element what you want to find - ";
            cin >> elem;
            cin.ignore();
            tree.Find(tree.root, elem);
        }
    } while(continue_[0] != 'n');
    cout << "\n__FINAL_RESULT__" << endl;
    tree.Display(tree.root, 0);
    return 0;
}
