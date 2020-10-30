#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct Tree{
	char data = 0;
	Tree* left = NULL;
	Tree* right = NULL;
} Tree;

void lineToTree(string& line, vector<Tree*>& pointerCollector);
Tree* getTree(string& line, int& i, Tree* root, vector<Tree*>& pointerCollector, int depth = 0);
bool isOperator(char c);
bool isData(char c);
void setData(Tree* node, char data);
void recursionDepth(char s, int n);
void printTree(Tree* tree);
void reduceTree(Tree* tree);
bool equalSubTrees(Tree* tree1, Tree* tree2);
Tree* error(int n);

int main(int argc, char *argv[]){
	string line;
	vector<Tree*> pointerCollector;
	if(argc==1){
		cout << "Write input tree:\t";
		getline(cin, line);
		lineToTree(line, pointerCollector);
	}else if(argc==2){
		line = argv[1];
		ifstream in(line);
		if(!in){
			error(2);
			return 0;
		}
		ofstream out("Trees.txt");
    	streambuf *coutbuf = cout.rdbuf();
    	cout.rdbuf(out.rdbuf());
		int lineNum;
		for(lineNum = 1; getline(in, line); lineNum++){
			cout << "\n\tString #" << lineNum << endl;
			lineToTree(line, pointerCollector);
		}
		cout.rdbuf(coutbuf);
		if(lineNum == 1) error(0); else cout << "Results are saved in Trees.txt file." << endl;
	} else error(1);
	for(int i=0; i<pointerCollector.size(); i++) delete pointerCollector[i];						
	return 0;
}

void lineToTree(string& line, vector<Tree*>& pointerCollector){
	int i = 0;
	Tree* tree = new Tree;
	pointerCollector.push_back(tree);
	if(getTree(line, i, tree, pointerCollector) == NULL){
		error(5);
		return;
	}
	cout << "Your input:\t";
	printTree(tree);
	cout << endl;
	reduceTree(tree);
	cout << "Reduced tree:\t";
	printTree(tree);
	cout << endl;
	return;
}

Tree* getTree(string& line, int& i, Tree* root, vector<Tree*>& pointerCollector, int depth){
	if(i >= line.length()) return error(6);
	recursionDepth(line[i], depth);
	if(isOperator(line[i])){
		setData(root, line[i]);
		Tree* nodeLeft = new Tree; pointerCollector.push_back(nodeLeft);
		if(getTree(line, ++i, nodeLeft, pointerCollector, depth+1) == NULL) return NULL; else root->left = nodeLeft;
		Tree* nodeRight = new Tree; pointerCollector.push_back(nodeRight);
		if(getTree(line, ++i, nodeRight, pointerCollector, depth+1) == NULL) return NULL; else root->right = nodeRight;
	} else if(isData(line[i])) setData(root, line[i]);
	else return error(3);
	if((depth == 0)&&(i+1 != line.length())) return error(4); else return root;
}

bool isOperator(char c){
	return ((c == '+')||(c == '-')||(c == '*'));
}

bool isData(char c){
	return ((c>=48)&&(c<=57))||((c>=65)&&(c<=90))||((c>=97)&&(c<=122));
}

void setData(Tree* node, char data){
	node->data = data;
	return;
}

void recursionDepth(char s, int n){
	for(int i=0; i<n; i++) cout << "\t";
	cout << "Symbol: " << s << "\tdepth: " << n << endl;
	return;
}

void printTree(Tree* tree){
	if(tree->left != NULL){
		cout << "(";
		printTree(tree->left);
		cout << tree->data;
		printTree(tree->right);
		cout << ")";
	} else cout << tree->data;
	return;
}

bool equalSubTrees(Tree* tree1, Tree* tree2){
	if(tree1->data != tree2->data) return false;
	if((tree1->left != NULL)&&(tree2->left != NULL)){
		if(equalSubTrees(tree1->left, tree2->left) == false) return false;
		if(equalSubTrees(tree1->right, tree2->right) == false) return false;
	}
	return true;
}

void reduceTree(Tree* tree){
	if((tree->data == '+')&&(equalSubTrees(tree->left, tree->right))){
		tree->left->data = '2';
		tree->left->left = NULL;
		tree->left->right = NULL;
		tree->data = '*';
	}
	if(tree->left != NULL) reduceTree(tree->left);
	if(tree->right != NULL) reduceTree(tree->right);
	return;
}

Tree* error(int n){
	cout << "Error!\t";
 	switch (n){
  		case 0: cout << "Empty file." << endl; break;
		case 1: cout << "Incorrect input arguments. Write file path or tree string." << endl; break;
		case 2: cout << "File not found." << endl; break;
		case 3: cout << "Non-permitted symbol is string. Permitted symbols for tree are: [A-Za-z0-9+-*]." << endl; break;
		case 4: cout << "Unexpected sequence after tree string." << endl; break;
		case 5: cout << "Tree string has invalid syntax." << endl; break;
		case 6: cout << "Expected more symbols in tree formula." << endl; break;
 	};
	return NULL;
}
