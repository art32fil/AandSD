#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <vector>

using namespace std;

int counter_procedure;

class Node
{
public:
	Node() {}
	Node(char s, int f)
	{
		this->s += s;
		frequency = f;
	}

	Node(char s)
	{
		this->s += s;
		frequency = 1;
	};

	Node(Node* l, Node* r) {
		frequency = l->frequency + r->frequency;
		left = l;
		right = r;
		s = l->s + r->s;
	}

	friend bool operator<(Node& a, Node& b);
	friend bool operator>(Node& a, Node& b);


	string s;
	int frequency;
	Node* left = nullptr;
	Node* right = nullptr;
};

bool operator<(Node& a, Node& b) {
	if (a.frequency < b.frequency)
		return true;
	else if (a.frequency == b.frequency) {
		if (a.s.size() < b.s.size())
			return true;
		else if (a.s.size() == b.s.size()) {
			return a.s[0] < b.s[0];
		}
		else return false;
	}
	return false;
}

bool operator>(Node& a, Node& b) {
	return !(a < b);
}



class BinTree
{
public:
	BinTree(Node* a) : root(a) {}
	BinTree() {}

	void read_node(Node* nd) {
		counter_procedure += 1;
		char b;
		cin.get(b);
		if (b == '(') {
			Node* l = new Node;
			read_node(l);
			nd->left = l;
			cin.get(b);
			Node* r = new Node;
			read_node(r);
			nd->right = r;
		}
		else if (b != ')') {
			nd->s = b;
		}
		cin.get(b);

	}

	void read_tree() {
		char b;
		cin >> b;
		if (b == '(') {
			Node* nd = new Node;
			read_node(nd);
			root = nd;
		}
		else {
			cerr << "error" << endl;
		}		
	}



	string decoding() {
		string decode = "";
		while (tree_traversal(root, decode)) {};
		return decode;
	}

	bool tree_traversal(Node* a, string& decode) {
		counter_procedure += 1;
		if (a->left == nullptr && a->right == nullptr) {
			decode += a->s;
			return true;
		}
		char b;
		cin.get(b);
		if (b == '0')
			tree_traversal(a->left, decode);
		else if (b == '1')
			tree_traversal(a->right, decode);
		else
			return false;
	}

	void printNode(Node* a, int k) {
		for (int i = 0; i < k; i++)
			cout << "   ";
		cout << a->s << endl;
		if (a->left != nullptr) {
			printNode(a->left, k + 1);
			printNode(a->right, k + 1);
		}
	}

	void print() {
		printNode(root, 0);
	}

	void print_tree(Node* nd) {
		cout << "(";
		if (nd->left == nullptr) {
			cout << nd->s;
		}
		else {
			print_tree(nd->left);
			print_tree(nd->right);
		}
		cout << ")";

	}

	Node* root = nullptr;
};





int main(int argc, char* argv[]) {
	vector<Node*> arr;
	string message = "";
	counter_procedure = 0;
	BinTree tree;
	tree.read_tree();
	tree.print_tree(tree.root);
	cout << endl;
	cout << tree.decoding() << endl;

	cout << "counter = " << counter_procedure << endl;
	return 0;
}