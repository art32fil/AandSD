#include <iostream>
#include <fstream>
#include <string>
#include <list>
#define ESCAPE 257
using namespace std;

class Tree {
public:
	Tree* left;
	Tree* right;
	Tree* parent;
	int code;
    bool symbol_code;
	int weight;
    Tree(Tree* left, Tree* right, Tree* parent, bool symbol_code) {
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->symbol_code = symbol_code;
        this->weight = 0;
        this->code = 255;
    }
};

int InputBits(string& str, int& n,  ofstream& fout) {
    int result = 0;
    char symbol;
    //cout << n<< " ";
    for (int i = n; i < n + 8; i++) {
        fout << str[i];
        symbol = str[i];
        result = (result << 1) + atoi(&symbol);
    }
    n += 8;
    //cout << n << endl;
    //cout << char(result)<<" "<<result<<endl;
    return result;
}

void addweight(Tree* tree) {
    tree->weight++;
    if (tree->parent) addweight(tree->parent);
}

void remweight(Tree* tree) {
    tree->weight--;
    if (tree->parent) remweight(tree->parent);
}

void restore(list<Tree*>& sort) {
    Tree* prev = *(--sort.end());
    Tree* current = nullptr;
    for (std::list<Tree*>::iterator i = --sort.end(); true; i--) {
        if (prev->weight > (*i)->weight) current = prev;
        if (current && (current->weight <= (*i)->weight)) {
            Tree test = *current;
            current->left = prev->left;
            if (current->left) current->left->parent = current;
            current->right = prev->right;
            if (current->right) current->right->parent = current;
            current->code = prev->code;
            current->symbol_code = prev->symbol_code;
            prev->left = test.left;
            if (prev->left) prev->left->parent = prev;
            prev->right = test.right;
            if (prev->right) prev->right->parent = prev;
            prev->code = test.code;
            prev->symbol_code = test.symbol_code;
            int diff = current->weight - prev->weight;
            for (int i = 0; i < diff; i++) {
                remweight(current);
                addweight(prev);
            }
            restore(sort);
            break;
        }
        prev = *i;
        if (i == sort.begin()) break;
    }
}

int DecodeSymbol(Tree* tree, string& str, int& n, int& flag_parent, list<Tree*>& sort, ofstream& fout) {

    if (flag_parent) {

        if (n + 8 > str.length()) return 258;
        fout << "symbol = ";
        tree->right = new Tree(nullptr, nullptr, tree, true);
        tree->right->code = InputBits(str, n, fout);
        addweight(tree->right);
        tree->left = new Tree(nullptr, nullptr, tree, true);
        tree->left->code = ESCAPE;
        flag_parent = 0;
        sort.push_back(tree->right);
        sort.push_back(tree->left);
        fout<<" ("<<char(tree->right->code) << ")"<< endl;
        return tree->right->code;
    }
    Tree* tree_test = tree;
    if (n >= str.length() )
        return 258;
    fout << "symbol = ";
    while (1) {
        if (n >= str.length()) return 258;
        if (str[n] == '1') {
            fout << "1";
            tree_test = tree_test->right;
            if (!tree_test) return 256;
            if (tree_test->symbol_code) {
                n += 1;
                addweight(tree_test);
                //fout << endl;
                fout<<" ("<<char(tree_test->code) << ")"<< endl;
                return tree_test->code;
            }
        }
        else if (str[n] == '0') {
            fout << "0";
            tree_test = tree_test->left;
            if (!tree_test) return 256;
            if (tree_test->symbol_code) {
                if (tree_test->code == ESCAPE) {
                    n += 1;
                    tree_test->right = new Tree(nullptr, nullptr, tree_test, true);
                    tree_test->right->code = InputBits(str, n, fout);
                    addweight(tree_test->right);
                    tree_test->left = new Tree(nullptr, nullptr, tree_test, true);
                    tree_test->left->code = ESCAPE;
                    tree_test->symbol_code = false;
                    sort.push_back(tree_test->right);
                    sort.push_back(tree_test->left);
                    fout<<" ("<<char(tree_test->right->code) << ")"<< endl;
                    return tree_test->right->code;
                }
                else {
                    n += 1;
                    addweight(tree_test);
                    fout<<" ("<<char(tree_test->code) << ")"<< endl;
                    return tree_test->code;
                }
            }
        }
        n += 1;
    }
}

void DecodingFile(string& str, ofstream& fout) {
    Tree tree(nullptr, nullptr, nullptr, false);
    list<Tree*> sort;
    sort.push_back(&tree);
    string result = "";
    int symbol;
    int n = 0;
    int f = 1;
    while ((symbol = DecodeSymbol(&tree, str, n, f, sort, fout)) != 256 && symbol != 258) {
        // cout << "res: " << symbol << "\n";
        result += (char)symbol;
        //cout << result << endl;
        restore(sort);
    }
    fout << "Result: " << result;
}

int main() {
    cout << "[1] - Enter from file test.txt \n[2] - Complete the program\n";
    char flag;
    cout << "--> ";
    cin >> flag;
    ofstream fout;
    ifstream fin;
    string str;
    string result;
    switch (flag) {
    case '1':
        fin.open("test.txt");
        fout.open("result.txt");
        while (!fin.eof()) {
            getline(fin, str);
            fout << "\nOriginal data: " << str << endl;
            DecodingFile(str, fout);
        }
        fin.close();
        fout.close();
        break;
    case '2':
        cout << "Thanks for your attention!";
        break;
    default:
        cout << "\nInvalid data entered!";
        break;
    }
    return 0;
}