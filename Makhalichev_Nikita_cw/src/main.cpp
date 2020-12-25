#include <map>
#include <string>
#include <sstream>
#include <fstream>
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
    Node<T> *root;
    ofstream output;
    bool file_output_;
    map<T, int> counter;
    AVLTree();
    int Height(Node<T> *tree);
    int BalanceFactor(Node<T> *tree);
    void ReadTree();
    void UpdateHeight(Node<T> *tree);
    void Find(Node<T> *tree, T elem);
    void Display(Node<T> *tree, int depth);
    void CombinedOutput(const char *message);
    Node<T> *Balance(Node<T> *tree);
    Node<T> *RotateLeft(Node<T> *tree);
    Node<T> *RotateRight(Node<T> *tree);
    Node<T> *MakeNode(Node<T> *tree, T elem);
    Node<T> *FindMinimal(Node<T> *tree);
    Node<T> *RemoveMinimal(Node<T> *tree);
    Node<T> *Remove(Node<T> *tree, T elem);
};

template<typename T>
AVLTree<T>::AVLTree(){
    root = NULL;
}

template<typename T>
void AVLTree<T>::ReadTree(){
    CombinedOutput("  ..::Reading the starting tree::..  \n");
    TYPE elem = 0;
    string str;
    CombinedOutput("Please, enter tree elements: ");
    getline(cin, str);
    if (file_output_){
        output << str << "\n";
    }
	istringstream stream(str);
    while (stream >> elem){
        cout << "\n         ..::Inserting " << elem << "::..        \n";
        if (file_output_){
            output << "\n         ..::Inserting " << elem << "::..        \n";
        }
        root = MakeNode(root, elem);
        CombinedOutput("    :::::::::::::::::::::::::::::    \n");
        CombinedOutput("\n       ..::Current AVL-Tree::..       \n");
        Display(root, 0);
        CombinedOutput("    :::::::::::::::::::::::::::::    \n");
    }
}

template<typename T>
Node<T> *AVLTree<T>::MakeNode(Node<T> *tree, T elem){
	if (tree == NULL) {
        cout << "Putting element into AVL-Tree" << "\n";
        counter[elem] = 1;
        return new Node<T>(elem);
	} else {
        cout << "Comparing " << elem << " with node " << tree->key << "\n";
        if (file_output_){
            output << "Comparing " << elem << " with node " << tree->key << "\n";
        }
        if (elem < tree->key){
            CombinedOutput(" - Going to the left tree\n");
    		tree->left = MakeNode(tree->left, elem);
    	} else if (elem > tree->key){
            CombinedOutput(" - Going to the right tree\n");
    		tree->right = MakeNode(tree->right, elem);
    	} else {
            CombinedOutput(" - This element is already contained in the AVL-Tree\n");
            CombinedOutput("   Increasing the quantity\n");
            counter.at(elem)++;
        }
    }
    cout << "Checking the AVL-Tree with node " << tree->key << " to balancing\n";
    if (file_output_){
        output << "Checking the AVL-Tree with node " << tree->key << " to balancing\n";
    }
    return Balance(tree);
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
int AVLTree<T>::BalanceFactor(Node<T> *tree){
    return Height(tree->right) - Height(tree->left);
}

template<typename T>
Node<T> *AVLTree<T>::RotateLeft(Node<T> *tree){
    CombinedOutput(" - Rotating left next part of tree:\n");
    Display(tree, 0);
    Node<T> *newtree = tree->right;
    tree->right = newtree->left;
    newtree->left = tree;
    UpdateHeight(tree);
    UpdateHeight(newtree);
    CombinedOutput("\n - Part of tree after left rotating:\n");
    Display(newtree, 0);
    CombinedOutput("\n");
    return newtree;
}

template<typename T>
Node<T> *AVLTree<T>::RotateRight(Node<T> *tree){
    CombinedOutput(" - Rotating right next part of tree:\n");
    Display(tree, 0);
    Node<T> *newtree = tree->left;
    tree->left = newtree->right;
    newtree->right = tree;
    UpdateHeight(tree);
    UpdateHeight(newtree);
    CombinedOutput("\n - Part of tree after right rotating:\n");
    Display(newtree, 0);
    CombinedOutput("\n");
    return newtree;
}

template<typename T>
Node<T> *AVLTree<T>::Balance(Node<T> *tree){
    UpdateHeight(tree);
    cout << " - New height is " << root->height << "\n";
    if (file_output_){
        output << " - New height is " << root->height << "\n";
    }
    int balance_factor = BalanceFactor(tree);
    cout << " - Balance factor is " << balance_factor << "\n";
    if (file_output_){
        output << " - Balance factor is " << balance_factor << "\n";
    }
	if (balance_factor == -2){
		if (BalanceFactor(tree->left) > 0)
			tree->left = RotateLeft(tree->left);
		return RotateRight(tree);
	}
	if (balance_factor == 2){
		if (BalanceFactor(tree->right) < 0)
			tree->right = RotateRight(tree->right);
		return RotateLeft(tree);
	}
	return tree;
}

template<typename T>
void AVLTree<T>::Display(Node<T> *tree, int depth){
    for (int i = 0; i < depth; i++){
        CombinedOutput(". ");
    }
    if (tree == NULL){
        CombinedOutput("(empty)\n");
    }
    if (tree != NULL){
        cout << tree->key << " (" << counter[tree->key] << ")\n";
        if (file_output_){
            output << tree->key << " (" << counter[tree->key] << ")\n";
        }
        Display(tree->left, depth + 1);
        Display(tree->right, depth + 1);
    }
}

template<typename T>
void AVLTree<T>::Find(Node<T> *tree, T elem){
    if (counter[elem]){
        cout << " - This element is contained " << counter[elem] << " time(s)\n";
        if (file_output_){
            output << " - This element is contained " << counter[elem] << " time(s)\n";
        }
    } else {
        cout << " - There is no element " << elem << "\n";
        if (file_output_){
            output << " - There is no element " << elem << "\n";
        }
    }
    cout << "\n         ..::Inserting " << elem << "::..        \n";
    if (file_output_){
        output << "\n         ..::Inserting " << elem << "::..        \n";
    }
    root = MakeNode(root, elem);
}

template<typename T>
Node<T> *AVLTree<T>::FindMinimal(Node<T> *tree){
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

template<typename T>
Node<T> *AVLTree<T>::RemoveMinimal(Node<T> *tree){
    if(tree->left == NULL){
        return tree->right;
    }
    tree->left = RemoveMinimal(tree->left);
    return Balance(tree);
}

template<typename T>
Node<T>* AVLTree<T>::Remove(Node<T> *tree, T elem){
    if(tree == NULL){
        CombinedOutput("Current AVL-Tree are not containing this key\n");
        return NULL;
    }
    cout << "Comparing " << elem << " with current node " << tree->key << "\n";
    if (file_output_){
        output << "Comparing " << elem << " with current node " << tree->key << "\n";
    }
	if(elem < tree->key){
        CombinedOutput("Going to look in left tree\n");
		tree->left = Remove(tree->left, elem);
    } else if (elem > tree->key){
        CombinedOutput("Going to look in right tree\n");
		tree->right = Remove(tree->right, elem);
    } else {
        if (!(--counter[tree->key])){
            Node<T>* left = tree->left;
    		Node<T>* right = tree->right;
    		delete tree;
            CombinedOutput("Key was removed from AVL-Tree\n");
    		if(right == NULL){
                return left;
            }
            CombinedOutput(" - Finding minimal key in right tree\n");
    		Node<T>* min = FindMinimal(right);
            cout << " - Minimal key, finded in right tree - " << min->key << "\n";
            if (file_output_){
                output << " - Minimal key, finded in right tree - " << min->key << "\n";
            }
            CombinedOutput(" - Removing minimal key in right tree\n");
    		min->right = RemoveMinimal(right);
            CombinedOutput(" - Placing minimal key in current tree\n");
    		min->left = left;
            cout << "Checking the AVL-Tree with node " << min->key << " to balancing\n";
            if (file_output_){
                output << "Checking the AVL-Tree with node " << min->key << " to balancing\n";
            }
    		return Balance(min);
        } else {
            CombinedOutput("One copy of this key was removed from AVL-Tree\n");
        }
	}
    cout << "Checking the AVL-Tree with node " << tree->key << " to balancing\n";
    if (file_output_){
        output << "Checking the AVL-Tree with node " << tree->key << " to balancing\n";
    }
    return Balance(tree);
}

template<typename T>
void AVLTree<T>::CombinedOutput(const char *message){
    cout << message;
    if (file_output_){
        output << message;
    }
}

int main(){
    system("clear");
    AVLTree<TYPE> tree;
    TYPE elem = 0;
    cout << "Do you need output to a file?\n";
    cout << "Enter \'y\' if yes\n";
    cout << "Your choice - ";
    string choice, working;
    cin >> choice;
    cin.ignore();
    switch(choice[0]){
        case 'y':
            tree.file_output_ = true;
            tree.output.open("output.txt");
            break;
        default:
            tree.file_output_ = false;
            break;
    }
    system("clear");
    if (tree.output.is_open() || (!tree.file_output_)){
        tree.ReadTree();
        do{
            tree.CombinedOutput("\nWhat's next?\n");
            tree.CombinedOutput("Find and insert element - 1, remove element - 2\n");
            tree.CombinedOutput("Your choice - ");
            choice = "";
            cin >> choice;
            cin.ignore();
            if (tree.file_output_){
                tree.output << choice[0] << "\n";
            }
            tree.CombinedOutput("Enter the element you want to operate - ");
            cin >> elem;
            if (tree.file_output_){
                tree.output << elem << "\n";
            }
            switch(choice[0]){
                case '1':
                    tree.CombinedOutput("\n    ..::Finding and inserting::..    \n");
                    tree.Find(tree.root, elem);
                    tree.CombinedOutput("    :::::::::::::::::::::::::::::    \n");
                    break;
                case '2':
                    tree.CombinedOutput("\n       ..::Removing element::..       \n");
                    tree.root = tree.Remove(tree.root, elem);
                    tree.CombinedOutput("    :::::::::::::::::::::::::::::    \n");
                    break;
                default:
                    tree.CombinedOutput("Wrong operation\n");
                    break;
            }
            cout << "\nDo you want to see current tree?\n";
            cout << "Enter \'y\' if yes\n";
            cout << "Your choice - ";
            choice = "";
            cin >> choice;
            cin.ignore();
            if (choice[0] == 'y'){
                tree.CombinedOutput("\n       ..::Current AVL-Tree::..       \n");
                tree.Display(tree.root, 0);
                tree.CombinedOutput("    :::::::::::::::::::::::::::::    \n");
            }
            cout << "\nDo you want to continue?\n";
            cout << "Enter \'y\' if yes\n";
            cout << "Your choice - ";
            working = "";
            cin >> working;
            cin.ignore();
        } while(working[0] == 'y');
        tree.CombinedOutput("\n         ..::Final Result::..        \n");
        tree.Display(tree.root, 0);
        tree.CombinedOutput("    :::::::::::::::::::::::::::::    \n");
    } else {
        cout << "Cannot open file \"output.txt\". The program is shutting down.\n";
    }
    return 0;
}
