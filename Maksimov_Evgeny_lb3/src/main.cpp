#include <iostream>
#include <fstream>

using namespace std;

typedef struct Node{
	char data = 0;
	Node* left = NULL;
	Node* right = NULL;
} Node;

class Tree{
private:
	Node* tree = new Node;
	bool errorFlag = false;

	bool isData(char c){
		return ((c>=48)&&(c<=57))||((c>=65)&&(c<=90))||((c>=97)&&(c<=122));
	}

	bool isOperator(char c){
		return ((c == '+')||(c == '-')||(c == '*'));
	}

	void setData(Node* node, char data){
		node->data = data;
		return;
	}

	bool equal(Node* tree1, Node* tree2){
		if(tree1->data != tree2->data) return false;
		if((tree1->left != NULL)&&(tree2->left != NULL)){
			if(equal(tree1->left, tree2->left) == false) return false;
			if(equal(tree1->right, tree2->right) == false) return false;
		}
		return true;
	}

	void recursionPrintDepth(char s, int n){
		for(int i=0; i<n; i++) cout << "\t";
		cout << "Symbol: " << s << "\tdepth: " << n << endl;
	    return;
	}

	void recursionPrint(Node* tree, int depth = 0){
		if(errorFlag) return;
		if(tree->left != NULL){
			cout << "(";
			recursionPrint(tree->left, depth+1);
			cout << tree->data;
			recursionPrint(tree->right, depth+1);
			cout << ")";
		} else cout << tree->data;
		if(depth == 0) cout << endl;
		return;
	}

	void recursionReduce(Node* tree){
		if(errorFlag) return;
		if((tree->data == '+')&&(equal(tree->left, tree->right))){
			tree->left->data = '2';
			tree->left->left = NULL;
			tree->left->right = NULL;
			tree->data = '*';
		}
		if(tree->left != NULL) recursionReduce(tree->left);
		if(tree->right != NULL) recursionReduce(tree->right);
		return;
	}

    void recursionError(int n){
		cout << "Error!\t";
 		switch(n){
			case 3: cout << "Non-permitted symbol is string. Permitted symbols for tree are: [A-Za-z0-9+-*]." << endl; break;
			case 4: cout << "Unexpected sequence after tree string." << endl; break;
			case 5: cout << "Expected more symbols in tree formula." << endl; break;
 		};
		errorFlag = true;
		return;
	}

	void recursionConstruct(const string& line, int& i, Node* root, int depth = 0){
		if(errorFlag) return;
		if(i >= line.length()) return recursionError(5);
		recursionPrintDepth(line[i], depth);
		if(isOperator(line[i])){
			setData(root, line[i]);
			Node* nodeLeft = new Node;
			Node* nodeRight = new Node;
			recursionConstruct(line, ++i, nodeLeft, depth+1);
			recursionConstruct(line, ++i, nodeRight, depth+1);
			root->left = nodeLeft;
			root->right = nodeRight;
		}
		else if(isData(line[i])) setData(root, line[i]);
		else return recursionError(3);	
		if((depth == 0)&&(i+1 != line.length())) return recursionError(4);
		return;
	}

	void recursionDestruct(Node* tree){
		if(tree->left != NULL){
			recursionDestruct(tree->left);
			recursionDestruct(tree->right);
		}
		delete tree;
	}

public:

	Tree(const string& line){
		int i = 0;
		recursionConstruct(line, i, tree);
	}

	~Tree(){
		recursionDestruct(tree);
	}

	void reduce(){
		recursionReduce(tree);
	}

	void print(){
		recursionPrint(tree);
	}

	bool isValid(){
		return !errorFlag;
	}

};

int error(int n){
	cout << "Error!\t";
 	switch(n){
  		case 0: cout << "Empty file." << endl; break;
		case 1: cout << "Incorrect input arguments. Write file path or tree string." << endl; break;
		case 2: cout << "File not found." << endl; break;
 	};
	return 0;
}

int main(int argc, char *argv[]){
	string line;
	switch(argc){
		case 1:
		{
			cout << "Write input tree:\t";
			getline(cin, line);
			Tree tree(line);
			if(tree.isValid()){
				cout << "Your input:\t";
				tree.print();
				tree.reduce();
				cout << "Reduced tree:\t";
				tree.print();
			}
		} break;
		case 2:
		{
			line = argv[1];
			ifstream in(line);
			if(!in) return error(2);
			ofstream out("Trees.txt");
    		streambuf *coutbuf = cout.rdbuf();
    		cout.rdbuf(out.rdbuf());
			int lineNum;
			for(lineNum = 1; getline(in, line); lineNum++){
				cout << "\n\tString #" << lineNum << endl;
				Tree tree(line);
				if(tree.isValid()){
					cout << "Your input:\t";
					tree.print();
					tree.reduce();
					cout << "Reduced tree:\t";
					tree.print();
				}
			}
			cout.rdbuf(coutbuf);
			if(lineNum == 1) return error(0); else cout << "Results are saved in Trees.txt file." << endl;
		} break;
		default: return error(1);
	}
	return 0;
}
