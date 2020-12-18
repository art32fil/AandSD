#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Tree {
private:

	struct node
	{
		int key;
		int height;
		node* left;
		node* right;
		node(int k) { key = k; left = right = 0; height = 1; }
	};

	node* root;

	int differenceHeight(node* tempNode) {
		return calculateHeight(tempNode->right) - calculateHeight(tempNode->left);
	}

	node* rotateright(node* tempNode)
	{
		node* tempNodeQ = tempNode->left;
		tempNode->left = tempNode->right;
		tempNodeQ->right = tempNode;
		countingHeight(tempNode);
		countingHeight(tempNodeQ);
		return tempNodeQ;
	}

	node* turnLeft(node* tempNode)
	{
		node* tempNodeQ = tempNode->right;
		tempNode->right = tempNodeQ->left;
		tempNodeQ->left = tempNode;
		countingHeight(tempNode);
		countingHeight(tempNodeQ);
		return tempNodeQ;
	}
	
	int calculateHeight(node* tempNode) {
		if (tempNode) {
			return tempNode->height;
		}
		return 0;
	}

	void countingHeight(node* tempNode) {
		if (tempNode == nullptr) {
			return;
		}
		countingHeight(tempNode->right);
		countingHeight(tempNode->left);
		int rightHeight = calculateHeight(tempNode->right), leftHeight = calculateHeight(tempNode->left);

		if (rightHeight > leftHeight) {
			tempNode->height = rightHeight + 1;
		}
		else {
			tempNode->height = leftHeight + 1;
		}
	}

	node* balance(node* tempNode)
	{

		countingHeight(tempNode);

		if (differenceHeight(tempNode) == 2)
		{
			if (differenceHeight(tempNode->right) < 0)
				tempNode->right = rotateright(tempNode->right);
			return turnLeft(tempNode);
		}
		if (differenceHeight(tempNode) == -2)
		{
			if (differenceHeight(tempNode->left) > 0)
				tempNode->left = turnLeft(tempNode->left);
			return rotateright(tempNode);
		}
		return tempNode;
	}

	node* pushNode(int key, node* tempNode) {
		if (!tempNode) {
			node* temp = new node(key);
			return temp;
		}
		if (key < tempNode->key)
			tempNode->left = pushNode(key, tempNode->left);
		else
			tempNode->right = pushNode(key, tempNode->right);
		return balance(tempNode);

	}

	void showVAL(node* tempNode) {
		cout << tempNode->key << " ";
		if (tempNode->left) {
			showVAL(tempNode->left);
		}
		if (tempNode->right) {
			showVAL(tempNode->right);
		}


	}

	node* findMin(node* tempNode)
	{
		if (tempNode->left) {
			return findMin(tempNode->left);
		}
		return tempNode;
	}

	node* delMin(node* tempNode)
	{
		if (tempNode->left == 0)
			return tempNode->right;
		tempNode->left = delMin(tempNode->left);
		return balance(tempNode);
	}

	node* del(node* tempNode, int key)
	{
		if (!tempNode) return 0;
		if (key < tempNode->key)
			tempNode->left = del(tempNode->left, key);
		else if (key > tempNode->key)
			tempNode->right = del(tempNode->right, key);
		else
		{
			node* tempNodeQ = tempNode->left;
			node* tempNodeR = tempNode->right;
			delete tempNode;
			if (!tempNodeR) return tempNodeQ;
			node* min = findMin(tempNodeR);
			min->right = delMin(tempNodeR);
			min->left = tempNodeQ;
			return balance(min);
		}
		return balance(tempNode);
	}

	bool checkElem(node* tempNode, int key, bool& it_) {
		if (tempNode->key == key) {
			it_ = true;
		}
		if (tempNode->left) {
			checkElem(tempNode->left, key, it_);
		}
		if (tempNode->right) {
			checkElem(tempNode->right, key, it_);
		}

		return it_;
	}

	void printTree(node* tempNode, int level)
	{
		if (tempNode)
		{
			printTree(tempNode->right, level + 1);

			for (int i = 0; i < level; i++) {
				cout << "   ";
			}
			cout << tempNode->key << endl;

			printTree(tempNode->left, level + 1);
		}
	}

public:

	Tree() {
		root = 0;
	}


	void push(int key) {
		root = pushNode(key, root);
	}

	node* getRoot() {
		return this->root;
	}

	void show() {
		showVAL(root);
	}

	void pop(int key) {
		if (key == root->key) {
			root = del(root, key);
		}
		else {
			del(root, key);
		}
	}

	bool check(int key) {
		bool it_ = false;
		if (checkElem(root, key, it_) == true) {
			return true;
		}
		else {
			return false;
		}
	}

	void showAVL() {
		printTree(root, 0);
	}

};

int main() {
	char c = 'y';
	int input = 0;
	Tree tree;
	int* data;
	string name_;
	ifstream f;
	cout << "Enter a file name.\n";
	cin >> name_;
	f.open(name_);
	if (!f.is_open()) {
		cout << "Invalid file name.\n";
		return 1;
	}
	
	int size;
	f >> size;
	for (int i = 0; i < size; i++)
	{
		int in_;
		f >> in_;
		tree.push(in_);
	}
	std::cout << "\nTree from input\n";
	tree.showAVL();
	cout << "q - for exit." << endl;
	while (c == 'y')
	{
		cout << "Input key wich you want to delete: ";
		std::cin >> input;
		if (tree.check(input)) {
			tree.pop(input);
			std::cout << "\nTree after edit\n";
			tree.showAVL();
		}
		else {
			cout << "There isn't that element which one you inputed." << endl;
			cout << "Tree: " << endl;
			tree.showAVL();
		}

		if (!tree.getRoot())
		{
			cout << "Your tree is empty!" << endl;
			break;
		}
		cout << "Are want you to continue? [y/n]" << endl;
		cin >> c;
		std::cout << std::endl;
	}
	return 0;
}