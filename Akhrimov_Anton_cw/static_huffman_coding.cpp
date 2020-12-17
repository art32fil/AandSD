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

	friend bool operator<(Node& a,  Node& b);
	friend bool operator>(Node& a,  Node& b);


	string s;
	int frequency;
	Node* left = nullptr;
	Node* right = nullptr;
};

bool operator<(Node& a,  Node& b) {
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

bool operator>( Node& a, Node& b) {
	return !(a < b);
}


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
		counter_procedure += 1;
		if (a->left == nullptr && a->right == nullptr) {
			dict[a->s[0]] = code; /*reverse_string(code);*/
			return;
		}
		else {
			tree_traversal(a->left, code + "0", dict);
			tree_traversal(a->right, code + "1", dict);
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

	void print_tree(Node* nd, int& size) {
		cout << "(";
		size += 8;
		if (nd->left == nullptr) {
			cout << nd->s;
			size += 8;
		}
		else {
			print_tree(nd->left, size);
			print_tree(nd->right, size);
		}
		cout << ")";
		size += 8;

	}

	Node* root;
};


void array_shift(vector<Node*>& arr, int i, int j) {
	Node* buff = arr[i];
	if (i < j) {	
		for (int k = i; k < j; k++) {
			arr[k] = arr[k + 1];
			counter_procedure += 1;
		}
		arr[j] = buff;
		counter_procedure += 1;
	}
	if (i > j) {
		for (int k = i; k > j; k--) {
			arr[k] = arr[k - 1];
			counter_procedure += 1;
		}
		arr[j] = buff;
		counter_procedure += 1;
	}
}



void my_qsort(vector<Node*>& arr, int first, int last) {
	int pivot, j, i;
	if (first < last) {
		pivot = (first+last)/2;
		//pivot = first;
		if (first == pivot) return;
		Node* p = arr[pivot];
		i = first;
		j = last;

		while (i < j) {
			while (*arr[i] < *p) {
				i++;
				counter_procedure += 1;
			}
			while (*p < *arr[j] ) {
				j--;
				counter_procedure += 1;
			}
			if (i < j) {
				/*Node* temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;*/
				if (i == pivot)
					pivot = j;
				else if (j == pivot)
					pivot = i;
				array_shift(arr, i, j);
				array_shift(arr, j - 1, i);
				//counter_procedure += 2;
			}
		}

		my_qsort(arr, first, pivot);
		my_qsort(arr, pivot, last);

	}
}








void print_vector(const vector<Node*>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i]->s << " " << arr[i]->frequency << "  ";
	}
	cout << endl;
}


bool check_node(vector<Node*>& arr, const char a) {
	for(int i = 0; i < arr.size(); i++){
		counter_procedure += 1;
		if (arr[i]->s[0] == a) {
			arr[i]->frequency++;
			return true;
		}
	}
	return false;
}

void add_node_in_arr(vector<Node*>& arr, const char a) {
	if (!check_node(arr, a)) {
		Node* nd = new Node(a);
		arr.push_back(nd);
		counter_procedure += 1;
	}
};


BinTree create_tree(vector<Node*>& arr) {
	my_qsort(arr, 0, arr.size() - 1);
	print_vector(arr);
	while (arr.size() > 1) {
		Node* a = arr.front();
		counter_procedure += 1;
		arr.erase(arr.begin());
		counter_procedure += 1;
		Node* b = arr.front();
		counter_procedure += 1;
		arr.erase(arr.begin());
		counter_procedure += 1;
		Node* ab = new Node(a, b);
		cout << "New Node: " << ab->s << endl;
		arr.push_back(ab);
		counter_procedure += 1;
		my_qsort(arr, 0, arr.size() - 1);
		print_vector(arr);
	}
	return BinTree(arr.back());
}




void print_dict(my_dict& dict) {
	my_dict::iterator it = dict.begin();
	for (; it != dict.end(); it++)
		cout << it->first << " = " << it->second << endl;
}




int main(int argc, char* argv[]) {
	vector<Node*> arr;
	string message = "";
	int time1;
	int time2;
	counter_procedure = 0;
	if (argc == 1) {
		char b;
		cin.get(b);
		do {
			message += b;
			add_node_in_arr(arr, b);
			cin.get(b);
		} while (b != '\n');
	}
	else if (argc == 2) {
		ifstream file(argv[1]);
		char b;
		file.get(b);
		do {
			message += b;
			add_node_in_arr(arr, b);
			file.get(b);
		} while (!file.eof());
	}
	else
		return 0;

	
	print_vector(arr);
	BinTree tree = create_tree(arr);
	cout << "Binary Tree:" << endl;
	tree.print();
	cout << "////////" << endl;
	my_dict dict = tree.coding();
	int size = 0;
	counter_procedure += message.size();
	for (int i = 0; i < message.size(); i++) {
		cout << dict[message[i]];
		size += dict[message[i]].size();
	}

	cout << endl;
	tree.print_tree(tree.root, size);
	cout << endl;
	cout << "size = " << size << endl;
	cout << "counter = " << counter_procedure << endl;
	return 0;
}