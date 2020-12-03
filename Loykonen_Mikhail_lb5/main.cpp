#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

class BinSearchTree{
private:
    struct Node{
        int data;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        Node(int el): data(el), left(nullptr), right(nullptr) {}
    };
        
    void add(shared_ptr<Node> &node, int el){
        if (!node){
            node = make_shared<Node>(el);
            return;
        }
        if (el < node->data){
            add(node->left, el);
        }
        else if (el > node->data){
            add(node->right, el);
        }
    }

    int findMin(shared_ptr<Node> node){
        auto cur = node;
        while (cur->left){
            cur = cur->left;
        }
        return cur->data;
    }

    int findMax(shared_ptr<Node> node){
        auto cur = node;
        while (cur->right){
            cur = cur->right;
        }
        return cur->data;
    }

    void deleteEl(shared_ptr<Node>& node, int el){
        if (!node){
            cout << "Данного элемента нет в дереве\n";
            return;
        }
        if (el > node->data){
            deleteEl(node->right, el);
        }
        else if (el < node->data){
            deleteEl(node->left, el);
        }
        else{
            if (node->right){
                int tmp = findMin(node->right);
                deleteEl(node, tmp);
                node->data = tmp;
            }
            else if (node->left){
                int tmp = findMax(node->left);
                deleteEl(node, tmp);
                node->data = tmp;
            }
            else
                node = nullptr;
        }
    }

    void print(shared_ptr<Node> node, int color, int level){
        if (node){
            print(node->right, 2, level+5);
            for (int i = 0; i<level; i++){
                cout << "\033[0;0m ";
            }
            if (color == 1)
                cout << "\033[1;34m" << node->data << "\033[0;0m" << '\n';
            else if (color == 2)
                cout << "\033[1;31m" << node->data << "\033[0;0m" << '\n';
            else
                cout << "\033[1;32m" << node->data << "\033[0;0m" << '\n';
            print(node->left, 3, level+5);
        }
    }

    shared_ptr<Node> head;
public:
    BinSearchTree(): head(nullptr) {};
    ~BinSearchTree() = default;

    void addElem(int el){
        add(head, el);
    }

    void deleteElem(int el){
        deleteEl(head, el);
    }

    bool isEmpty(){
        if (head)
            return false;
        else
            return true;
    }

    void printTree(){
        if (head)
            print(head, 1, 0);
        else
            cout << "В дереве нет элементов";
    }

};

int main(){
    string name;
    cout << "Введите название файла: ";
    cin >> name;
    ifstream fin(name);
    BinSearchTree* bst = new BinSearchTree();
    int elem;
    char opt = 'y';
    cout << "Исходная последовательность элементов: ";
    while(!fin.eof()){
        fin >> elem;
        cout << elem << " ";
        bst->addElem(elem);
    }
    cout << '\n';
    bst->printTree();
    while (opt == 'y'){
        cout << "Введите элемент, который нужно удалить: ";
        cin >> elem;
        bst->deleteElem(elem);
        if (bst->isEmpty()){
            cout << "В дереве нет элементов\n";
            break;
        }
        cout << '\n';
        bst->printTree();
        cout << '\n';
        cout << "Хотите удалить ещё один элемент? y - да | n - нет : ";
        cin >> opt;
    }
    delete bst;
    return 0;
}