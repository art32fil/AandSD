#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>

using namespace std;


class Node
{
public:
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

	string s;
	int frequency;
	Node* left = nullptr;
	Node* right = nullptr;
};

typedef map<char, string> my_dict;

string reverse_string(string s) {
	cout << " before: " << s << endl;
	string copy = s;
	for (int i = s.size() - 1, j = 0; i >= 0; i--, j++)
		copy[j] = s[i];
	cout << " after: " << copy << endl;
	return copy;
}




class BinTree
{
public:
	BinTree(Node* a) : root(a) {}
	my_dict coding() {
		my_dict dict;
		string code = "";
		tree_traversal(root, code, dict);
		return dict;
	}

	void tree_traversal(Node* a, string code, my_dict& dict) {
		if (a->left == nullptr && a->right == nullptr) {
			dict[a->s[0]] = code; /*reverse_string(code);*/
			return;
		}
		else {
			tree_traversal(a->left, code + "0" , dict);
			tree_traversal(a->right, code + "1" , dict);
		}

	}
	void printNode(Node* a, int k) {
		for (int i = 0; i < k; i++)
			cout << "   ";
		cout << a->s << " = " << a->frequency << endl;
		if (a->left != nullptr) {
			printNode(a->left, k + 1);
			printNode(a->right, k + 1);
		}
	}

	void print() {
		printNode(root, 0);
	}

	Node* root;
};



class Compare {
public:
	bool operator()(Node* a, Node* b) {
		if (a->frequency > b->frequency)
			return true;
		else
			return false;
	}
};

typedef priority_queue<Node*, vector<Node*>, Compare > my_que;


void print_queue(my_que que) {
	while(que.size()) {
		cout << que.top()->s << " " << que.top()->frequency << endl;
		que.pop();
	}	
}

bool check_node(my_que que, const char a) {
	while (que.size()) {
		if (que.top()->s[0] == a) {
			que.top()->frequency++;
			return true;
		}
		que.pop();
	}
	return false;
}

void add_node_in_queue(my_que& que, const char a) {
	if (!check_node(que, a)) {
		Node* nd = new Node(a);
		que.push(nd);
	}
};


BinTree create_tree(my_que& que) {
	while (que.size() > 1) {
		Node* a = que.top();
		que.pop();
		Node* b = que.top();
		que.pop();
		Node* ab = new Node(a, b);
		que.push(ab);
	}
	return BinTree(que.top());
}




void print_dict(my_dict& dict) {
	my_dict::iterator it = dict.begin();
	for (; it != dict.end(); it++)
		cout << it->first << " = " << it->second << endl;
}


int main(int argc, char* argv[]) {
	my_que que;
	string message = "";
	if (argc == 1) {
		char b;
		cin.get(b);
		do {
			message += b;
			add_node_in_queue(que, b);
			cin.get(b);
		} while (b != '\n');
	}
	else if (argc == 2) {
		ifstream file(argv[1]);
		char b;
		file.get(b);
		do {
			message += b;
			add_node_in_queue(que, b);
			file.get(b);
		} while (!file.eof());
	}
	else
		return 0;
	BinTree tree = create_tree(que);
	cout << "Binary Tree:" << endl;
	tree.print();
	cout << "////////" << endl;
	my_dict dict = tree.coding();
	cout << "Dictionary:\n";
	print_dict(dict);
	cout << "Encoded message:\n";
	for (int i = 0; i < message.size(); i++) {
		cout << dict[message[i]];
	}
	cout << endl;

	return 0;
}
