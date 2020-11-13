#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct BinTree {
    BinTree* left = nullptr;
    BinTree* right = nullptr;
    char data = '0';
};

void CreatBinTree(BinTree* b, string& str, unsigned int& n, bool& cond) {
    if (n >= str.length()) return;

    if (str[n] == '#') {
        n++;
        return;
    } else {
        b->data = str[n];
        n++;
        for (int i = 0; i < n - 1; i++) {
            if (str[i] == b->data && cond == false) {
                cond = true;
            }
        }

        b->left = new BinTree;
        CreatBinTree(b->left, str, n, cond);
        b->right = new BinTree;
        CreatBinTree(b->right, str, n, cond);
    }
}

void DeleteBinTree(BinTree* b) {
    if (b == nullptr) {
        return;
    }

    DeleteBinTree(b->left);
    DeleteBinTree(b->right);
    delete b;
    return;
}

int main() {
    ifstream fin;
    unsigned int n = 0;
    bool cond = false;
    fin.open("inputfile.txt");
    string str;

    if (!fin.is_open()) {
        cout << "Permission denied or wrong path.";
        return 0;
    }

    while (getline(fin, str)) {
        BinTree* b = new BinTree;
        cout << "Input data: " << str << endl;
        CreatBinTree(b, str, n, cond);

        if (cond) {
            cout << "TRUE" << endl;
        } else {
            cout << "FALSE" << endl;
        }

        cond = false;
        n = 0;
        DeleteBinTree(b);
    }
    fin.close();
    return 0;
}
