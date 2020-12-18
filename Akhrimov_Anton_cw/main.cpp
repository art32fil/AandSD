#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <limits>
#include <cmath>


using namespace std;

int counter_procedure;




string reverse_string(string s) {
	string copy = s;
	for (int i = s.size() - 1, j = 0; i >= 0; i--, j++)
		copy[j] = s[i];
	return copy;
}

string binary_code(int a) {
	string s;
	while (a > 0) {
		if (a % 2)
			s += "1";
		else
			s += "0";
		a = a / 2;
	}
	if (s.size() < 8) {
		int size = s.size();
		for (int i = 0; i < (8 - size); i++)
			s += "0";
	}
	return reverse_string(s);
}

int from_binary(string s) {
	int a = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[s.size() - i - 1] == '1')
			a += pow(2,i);
	}
	return a;
}


class Node
{
public:
	Node(char c) {
		this->c = c;
		weight = 1;
	}

	int weight;
	char c;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

void swap(Node* a, Node* b) {
	if (a->parent != nullptr && b->parent != nullptr) {
		Node* buff = a->parent;
		a->parent = b->parent;
		b->parent = buff;
		if (a->parent == b->parent) {
			if (a->parent->left == a) {
				a->parent->left = b;
				a->parent->right = a;
			}
			if (a->parent->right == a) {
				a->parent->right = b;
				a->parent->left = a;
			}
		}
		else {
			if (a->parent->left == b) {
				a->parent->left = a;
			}
			else if (a->parent->right == b) {
				a->parent->right = a;
			}
			if (b->parent->left == a)
				b->parent->left = b;
			else if (b->parent->right == a)
				b->parent->right = b;
		}
	}
}

class BinTree
{
public:
	BinTree() {
		Node* nd = new Node('\0');
		nd->weight = 0;
		zero_node = nd;
		root = nd;
	}

	void addNode(const char c) {
		Node* nd = new Node(c);
		Node* new_zero = new Node('\0');
		new_zero->weight = 0;
		zero_node->right = nd;
		zero_node->left = new_zero;
		zero_node->weight = 1;
		nd->parent = zero_node;
		new_zero->parent = zero_node;
		zero_node = new_zero;
		counter_procedure += 2;
	}

	void find_zero(Node* nd, string s) {
		counter_procedure += 1;
		if (nd->weight == 0) { 
			current_coding_message += s;
			return;
		}
		else if(nd->left != nullptr && nd->right != nullptr){
			find_zero(nd->left, (s + "0"));
			find_zero(nd->right, (s + "1"));
		}
	}

	bool check_sym(const char c, Node* nd, string s) {
		counter_procedure += 1;
		if (nd->left == nullptr && nd->right == nullptr) {
			if (nd->c == c) {
				nd->weight += 1;
				current_coding_message += s;
				return true;
			}
			return false;
		}
		else
			return check_sym(c, nd->left, s + "0") || check_sym(c, nd->right, s + "1");
	}

	int refresh_weight(Node* nd) {
		if (nd == nullptr)
			return 0;
		counter_procedure += 1;
		if (nd->left == nullptr && nd->right == nullptr)
			return nd->weight;
		else {
			nd->weight = refresh_weight(nd->left) + refresh_weight(nd->right);
			return nd->weight;
		}
	}

	void check_weight(queue<Node*> que, int size, Node** bad_node, int current_weight) {
		int new_size = 0;
		while (size > 0) {
			Node* nd = que.front();
			que.pop();
			size -= 1;
			counter_procedure += 1;
			if (nd->right != nullptr) {
				if (nd->right->weight > current_weight)
					*bad_node = nd->right;
				else
					current_weight = nd->right->weight;
				que.push(nd->right);
				new_size += 1;
				counter_procedure += 1;
			}
			if (nd->left != nullptr) {
				if (nd->left->weight > current_weight)
					*bad_node = nd->left;
				else
					current_weight = nd->left->weight;
				que.push(nd->left);
				new_size += 1;
				counter_procedure += 1;
			}
		}
		if (!que.empty())
			check_weight(que, new_size, bad_node, current_weight);
	}

	void swap_nodes(queue<Node*>& que, int size, Node* bad_node) {
		int new_size = 0;
		while (size > 0) {
			Node* nd = que.front();
			que.pop();
			size -= 1;
			counter_procedure += 1;
			if (nd->right != nullptr) {
				if (nd->right->weight < bad_node->weight) {
					swap(nd->right, bad_node);
					return;
				}
				que.push(nd->right);
				new_size += 1;
				counter_procedure += 1;
			}
			if (nd->left != nullptr) {
				if (nd->left->weight < bad_node->weight) {
					swap(nd->left, bad_node);
					return;
				}
				que.push(nd->left);
				new_size += 1;
				counter_procedure += 1;
			}
		}
		if (!que.empty())
			swap_nodes(que, new_size, bad_node);
	}

	void refresh_tree() {
		refresh_weight(root);
		int flag;
		do {
			flag = 0;
			Node* bad_node = nullptr;
			queue<Node*> que;
			que.push(root);
			check_weight(que, 1, &bad_node, root->weight);
			if (bad_node != nullptr) {
				queue<Node*> que;
				que.push(root);
				swap_nodes(que, 1, bad_node);
				refresh_weight(root);
				flag = 1;
			}
		} while (flag);
	}


	string coding() {
		current_coding_message = "";
		char b;
		cin.get(b);
		while (b != '\n') {
			string s = "";
			if (!check_sym(b, root, s)){
				find_zero(root, s);
				current_coding_message += binary_code(b);
				addNode(b);
			}
			refresh_tree();
			cin.get(b);
			print();
		}
		
		return current_coding_message;
	}

	string coding(ifstream& file) {
		current_coding_message = "";
		char b;
		while (file.get(b)) {
			string s = "";
			if (!check_sym(b, root, s)) {
				find_zero(root, s);
				current_coding_message += binary_code(b);
				addNode(b);
			}
			refresh_tree();
			print();
		}

		return current_coding_message;
	}


	char decode_symbol() {
		string s = "";
		char b;
		for (int i = 0; i < 8; i++) {
			cin.get(b);
			s += b;
		}
		return from_binary(s);
	}

	bool follow_code(Node* nd) {
		counter_procedure += 1;
		if (nd->weight == 0) {
			char b = (char) decode_symbol();
			current_decoding_message += b;
			addNode(b);
			return true;
		}
		if (nd->left == nullptr) {
			nd->weight += 1;
			current_decoding_message += nd->c;
			return true;
		}
		char b;
		cin.get(b);
		if (b == '0') {
			return follow_code(nd->left);;
		}
		else if (b == '1') {
			return follow_code(nd->right);
		}
		 return false;
	}

	string decoding() {
		current_decoding_message = "";
		while (follow_code(root)) {
			refresh_tree();
			print();
		}
		refresh_weight(root);
		print();
		return current_decoding_message;
	}

	char decode_symbol(ifstream& file) {
		string s = "";
		char b;
		for (int i = 0; i < 7; i++) {
			file.get(b);
			s += b;
		}
		return from_binary(s);
	}


	bool follow_code(Node* nd, ifstream& file) {
		
		if (nd->weight == 0) {
			char b = (char)decode_symbol(file);
			current_decoding_message += b;
			addNode(b);
			return true;
		}
		if (nd->left == nullptr) {
			nd->weight += 1;
			current_decoding_message += nd->c;
			return true;
		}
		char b;
		file.get(b);
		if (b == '0') {
			return follow_code(nd->left, file);
		}
		else if (b == '1') {
			return follow_code(nd->right, file);
		}
		return false;
	}

	string decoding(ifstream& file) {
		current_decoding_message = "";
		while (follow_code(root, file)) {
			refresh_tree();
			print();
		}
		refresh_weight(root);
		print();
		return current_decoding_message;
	}


	int count_level(Node* nd, int n) {
		n += 1;
		if (nd->left == nullptr)
			return n;
		else {
			int a = count_level(nd->left, n);
			int b = count_level(nd->right, n);
			return a > b ? a : b;
		}
	}


	void printNode(Node* a, int k) {
		for (int i = 0; i < k; i++)
			cout << "   ";
		if (a->c == '\0' && a->weight != 0)
			cout << "\\" << a->weight << "/" << endl;
		else if (a->weight == 0)
			cout << "0-node" << endl;
		else
			cout << a->c << " = " << a->weight << endl;
		if (a->left != nullptr) {
			printNode(a->left, k + 1);
			printNode(a->right, k + 1);
		}
	}

	void print() {
		printNode(root, 0);
		cout <<"/////////" <<endl;
	}

	Node* root;
	Node* zero_node;
	string current_coding_message;
	string current_decoding_message;
};



int main(int argc, char* argv[]) {
	string message;
	if (argc == 1) {
		int flag = 0;
		int start;
		int end;
		cout << "Hello there!\n";
		while (!flag) {
			cout << "Continue?[y/n]\n";
			counter_procedure = 0;
			BinTree bt;
			char b;
			string s;
			cin >> b;
			switch (b) {
			case 'y':
				break;
			case 'n':
				return 0;
			}
			cout << "Coding/Decoding?[c/d]\n";
			cin >> b;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (b)
			{
			case 'c':
				s = bt.coding();
				cout << s << endl;				
				cout << "counter = " << counter_procedure << endl;
				break;
			case 'd':
				cout << bt.decoding() << endl;
				cout << "counter = " << counter_procedure << endl;
				break;
			}
			cout << "//////" << endl;
		}
	}
	else if (argc == 2) {
			ifstream file(argv[1]);
			char b;
			BinTree bt;
			file.get(b);
			if (b == '0') {

				cout << bt.coding(file) << endl;
				
			}
			else if (b == '1') {
				cout << bt.decoding(file) << endl;
			}
			file.close();
		}
	else if (argc == 3) {
		ifstream input(argv[1]);
		ofstream output(argv[2]);
		char b;
		BinTree bt;
		input.get(b);
		if (b == '0') {
			output << '1';
			output << bt.coding(input);
		}
		else if (b == '1') {
			output << '0';
			output << bt.decoding(input);
		}
		input.close();
		output.close();
	}
	else
		return 0;



	return 0;
}