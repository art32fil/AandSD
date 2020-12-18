#include <iostream>
#include <fstream>
using namespace std;

struct Node {
	int key;
	int size;
	Node* left;
	Node* right;
	Node(int k) {
		key = k;
		left = right = nullptr;
		size = 1;
	}
};

int getsize(Node* btree){
	if (!btree) return 0;
	return btree->size;
}

void fixsize(Node* btree){
	btree->size = getsize(btree->left) + getsize(btree->right) + 1;
}

Node* rotateright(Node* btree){
	Node* newbtree = btree->left;
	if (!newbtree) return btree;
	btree->left = newbtree->right;
	newbtree->right = btree;
	newbtree->size = btree->size;
	fixsize(btree);
	return newbtree;
}

Node* rotateleft(Node* btree){
	Node* newbtree = btree->right;
	if (!newbtree) return btree;
	btree->right = newbtree->left;
	newbtree->left = btree;
	newbtree->size = btree->size;
	fixsize(btree);
	return newbtree;
}

Node* insertroot(Node* btree, int k){
	if (!btree) return new Node(k);
	if (k < btree->key){
		btree->left = insertroot(btree->left, k);
		return rotateright(btree);
	}
	else{
		btree->right = insertroot(btree->right, k);
		return rotateleft(btree);
	}
}

Node* insert(Node* btree, int k){
	if (!btree) return new Node(k);
	if (rand() % (btree->size + 1) == 0)
	return insertroot(btree, k);
	
	if (btree->key > k)
		btree->left = insert(btree->left, k);
	else
		btree->right = insert(btree->right, k);
	
	fixsize(btree);
	return btree;
}

Node* Create(int key, Node* left, Node* right){
	
	Node* res = new Node(key);
	res->left = left;
	res->right = right;
		
	return res;
}


void Print(Node* btree, int level){

	if (btree->right != nullptr){
		Print(btree->right, level + 1);
	}
	for (int i = 0; i < level; i++) {
		cout << "    ";
	}
		
	cout << btree->key << "\n";	

	if (btree->left != nullptr) {
		Print(btree->left, level + 1);
	}
}
	
void LTR(Node* btree, ofstream & out){
	if(btree == nullptr) return;
	LTR(btree->left, out);
	out << btree->key << " ";
	LTR(btree->right, out);
}

int main() {
	char c = 'y';
	int input = 0;

	int size;
	cout << "Введите количество элементов: ";
	cin >> size;
	while (size<=0){ 
		cout << "Неправильно указано количество элементов.\nВведите количество элементов: ";
		cin >> size;
	}
	Node* tree = nullptr;
	srand(time(0));

	for (int i = 0; i < size; i++) {
		int in;
		cin >> in;
		tree = insert(tree, in);
	}

	cout << endl << "Случайное БДП с рандомизацией:" << endl;
	Print(tree, 0);
	ofstream file;
	file.open("result.txt");
	LTR(tree, file);
	file.close();
	return 0;
}
