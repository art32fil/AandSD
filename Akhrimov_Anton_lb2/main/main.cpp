#include <iostream>
#include <fstream>

using namespace std;

struct Node;
struct Arm;
struct binTree
{
	Arm* arm1;
	Arm* arm2;

	binTree(Arm* a1 = nullptr, Arm* a2 = nullptr):
		arm1(a1), 
		arm2(a2)
	{}
};

struct Arm
{
	int length;
	bool tag;
	Node* node;

	Arm(int len = 0, bool tg = false, Node* nd = nullptr):
		length(len),
		tag(tg),
		node(nd)
	{}
};


struct Node {
	int weight;
	binTree* binT;
	Node(int wt = 0, binTree* binT = nullptr):
		weight(wt),
		binT(binT)
	{}
};


void write_binT(binTree* list);

void write_arm(Arm* arm);

void read_binTree_from_file(char prev, binTree* list, ifstream& in);

Arm* read_arm_from_file(ifstream& in);

void start_read_from_file(binTree* list, ifstream& in) {
	char buf;
	in.get(buf);
	if (buf == '(')
		read_binTree_from_file(buf, list, in);
}

void read_binTree_from_file(char prev, binTree* list, ifstream& in) {
	if (prev == '(') {
		list->arm1 = read_arm_from_file(in);
		char buf;
		in.get(buf);
		if(buf != ' ') { cerr << "Error binT1!\n" + buf; exit(1); }
		list->arm2 = read_arm_from_file(in);
		in.get(buf);
		if (buf != ')') { cerr << "Error binT2!\n"; exit(1); }
	}
	else { cerr << "Error binT3!\n"; exit(1); }
}

Arm* read_arm_from_file(ifstream& in) {
	char buf;
	Arm* arm = new Arm;
	in.get(buf);
	if (buf == '(') {
		in >> arm->length;
		in.get(buf);
		if (buf == '(') {
			arm->tag = true;
			Node* nd = new Node;
			arm->node = nd;
			binTree* binT = new binTree;
			arm->node->binT = binT;
			read_binTree_from_file(buf, arm->node->binT, in);
		}
		else if (buf == ' ') {
			arm->tag = false;
			Node* nd = new Node;
			arm->node = nd;
			in >> arm->node->weight;
		}
		in.get(buf);
		if (buf != ')') { cerr << "Error arm1!\n"; exit(1); }
	}
	else { cerr << "Error arm2!\n"; exit(1); }
	
	return arm;
}

void read_binTree(char prev, binTree* list);

Arm* read_arm();

void start_read(binTree* list) {
	char buf;
	cin.get(buf) ;
	if (buf == '(')
		read_binTree(buf, list);
}

void read_binTree(char prev, binTree* list) {
	if (prev == '(') {
		list->arm1 = read_arm();
		char buf;
		cin.get(buf);
		if (buf != ' ') { cerr << buf; exit(1); }
		list->arm2 = read_arm();
		cin.get(buf);
		if (buf != ')') { cerr << "Error binT2!\n"; exit(1); }
	}
	else { cerr << "Error binT3!\n"; exit(1); }
}

Arm* read_arm() {
	char buf;
	Arm* arm = new Arm;
	cin.get(buf);
	if (buf == '(') {
		cin >> arm->length;
		cin.get(buf);
		if (buf == '(') {
			arm->tag = true;
			Node* nd = new Node;
			arm->node = nd;
			binTree* binT = new binTree;
			arm->node->binT = binT;
			read_binTree(buf, arm->node->binT);
		}
		else if (buf == ' ') {
			arm->tag = false;
			Node* nd = new Node;
			arm->node = nd;
			cin >> arm->node->weight;
		}
		cin.get(buf);
		if (buf != ')') { cerr << "Error arm1!\n"; exit(1); }
	}
	else { cerr << "Error arm2!\n"; exit(1); }

	
	return arm;
}


void write_arm(Arm* arm) {
	if (arm == nullptr) {
		cout << "(?)";
		return;
	}
	cout << '(';
	cout << arm->length;
	if (arm->tag == false) {
		cout << ' ';
		cout << arm->node->weight;
	}
	else
		write_binT(arm->node->binT);
	cout << ')';
}

void write_binT(binTree* list) {
	if (list == nullptr) { cout << "()\n"; return; }
	cout << '(';
	write_arm(list->arm1);
	cout << ' ';
	write_arm(list->arm2);
	cout << ')';
}

void Destroy_arm(Arm* arm);

void Destroy(binTree* tree) {
	if (tree->arm1 != nullptr)
		Destroy_arm(tree->arm1);
	if (tree->arm2 != nullptr)
		Destroy_arm(tree->arm2);
	delete tree;
}

void Destroy_arm(Arm* arm) {
	if (arm->tag == true)
		Destroy(arm->node->binT);
	delete arm->node;
	delete arm;
}


void traversal_arm(Arm* arm, int& k, int& level);
void traversal_tree(binTree* tree, int& k, int& level);

void output_recursion(const int level, const int lenght, const int k) {
	for (int i = 0; i < level; i++)
		cout << ' ';
	cout << "tree depth level = " << level << " lenght = " << lenght << " current k = " << k << endl;
}

int i = 0;

short Length(const binTree* tree) {
	int k = 0;
	int level = 0;
	traversal_arm(tree->arm1, k, level);
	traversal_arm(tree->arm2, k, level);
	return k;
}

void traversal_arm(Arm* arm, int& k, int& level) {
	level += 1;
	k += arm->length;
	output_recursion(level, arm->length, k);
	if (arm->tag) {
		traversal_tree(arm->node->binT, k, level);
	}
	level -= 1;
}

void traversal_tree(binTree* tree, int& k, int& level) {
	traversal_arm(tree->arm1, k, level);
	traversal_arm(tree->arm2, k, level);
}


int main() {
	
	string filename;
	binTree* tree = new binTree;
	ifstream in;

	char ans;
	cout << "Read from file? [y/n]\n";
	cin >> ans;
	switch (ans) {
	case 'y':
		cout << "Enter filename.\n";
		cin >> filename;
		in.open(filename);
		start_read_from_file(tree, in);
		in.close();
		break;
	case 'n':
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		start_read(tree);
		break;
	default:
		cerr << "Invalid ans";
		exit(1);
	}

	write_binT(tree);
	cout << endl;

	int k = Length(tree);

	cout << "Length = " << k << endl;

	return 0;

}