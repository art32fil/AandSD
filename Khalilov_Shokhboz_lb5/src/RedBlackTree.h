
//! 1
//* Каждый узел промаркирован красным или чёрным цветом
//! 2
//* Корень и конечные узлы (листья) дерева - чёрные
//! 3
//* У красного узла родительский узел - черный
//! 4
//* Все простые пути из любого узла х до листьев содержат одинокавое количества чёрных узлов
//! 5
//* Чёрный узел может иметь чёрного родителя

#include <iostream>
#include <fstream>

enum color_t {  
	BLACK = 0,  
	RED = 1 
	};

class Node
{
private:
    Node *parent;
    Node *left;
    Node *right;
    int key;
    color_t Color;
public:
    Node(){
        Color = RED;
        parent = left = right = nullptr;
    }
    Node(int val, color_t cl) : key(val), Color(cl) {
        
        parent = left = right = nullptr;
    }
    
	Node *&Left() { return left; }
    Node *&Right() { return right; }

    Node *&Parent() { return parent; }
    int getVal() { return key; }
    void setValue(int val) { key = val; }
    color_t& color(){  return Color; } 
    ~Node(){

	}
};



void createForest(Node *&root, int *arr, int size);
void showForestOnConcole(Node *root, int n);
void ShowForestWithoutColor(Node *root, int);
void fixProperties(Node *elem);

bool isRed(Node *n);
bool isBlack(Node *n);
bool isLeft(Node *n);
bool isRight(Node *n);

Node *GrandParent(Node *n);
Node *Parent(Node *n);
Node *Brother(Node *n);
Node *Uncle(Node *n);
Node * Root(Node* elem);

void InsertRecurse(Node *&root, Node *n);
Node *Insert(Node *root, Node *n);
Node *findElem(Node *root, int key);
void RotateLeft(Node *n);
void RotateRight(Node *n);

void deleteElem(Node *&root, int key);
void deleteNode(Node *elem);
void deleteFixup(Node *elem);

bool isLeaf(Node *elem);
bool isNotLeaf(Node *elem);
void free(Node *elem);
void WriteToFile(Node *elem, std::ofstream &fout);
Node* ReadFromConsole(Node *head);
Node* ReadFromFile( Node* head );
int CountElem(Node *elem, int key);
