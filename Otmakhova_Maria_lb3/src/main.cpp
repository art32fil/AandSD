#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
class BinTree {
private:
    struct Node {
        T data;
        int left = 0;
        int right = 0;
    };
    int size;
public:
    Node* vec;
    bool answer = false;
    BinTree() {
        vec = new Node[100];
        size = 100;
    }

    void resize() {
        int newSize = size + 100;
        Node* tmp = new Node[newSize];
        for (int i = 0; i < size; i++)
            tmp[i] = vec[i];
        delete[] vec;
        size = newSize;
        vec = tmp;
    }

    void addNode(T data, int ind) {
        if (ind * 2 + 2 == size)
            this->resize();
        vec[ind].data = data;
        vec[ind].left = ind * 2 + 1;
        vec[ind].right = ind * 2 + 2;
    }


    ~BinTree() {
        delete[] vec;
    }
};

void readBinTree(string& infix, int start, int end, int ind, BinTree<char>* bt) {
    int depth = 0;
    if (start == end) {
        for (int i = 0; i < start; i++)
            if (infix[start] == infix[i])
                bt->answer = true;

        bt->addNode(infix[start], ind);
        return;
    }
    for (int i = start; i <= end; i++) {
        if (infix[i] == '(')
            depth++;
        if (infix[i] == ')')
            depth--;
        if (depth == 1 && (infix[i] == '+' || infix[i] == '-' || infix[i] == '*')) {
            bt->addNode(infix[i], ind);
            readBinTree(infix, start + 1, i - 1, ind * 2 + 1, bt);
            readBinTree(infix, i + 1, end - 1, ind * 2 + 2, bt);
        }
    }
}

int main() {
    string infix;
    ifstream fin("C:\\Users\\Masha\\CLionProjects\\untitled3\\input.txt");
    while (!fin.eof()) {
        BinTree <char>* bt = new BinTree <char>;
        fin >> infix;
        cout << "infix: " << infix << '\n';
        readBinTree(infix, 0, infix.length() - 1, 0, bt);
        cout << '\n';
        if (bt->answer) {
            cout << "True" << endl;
            cout << '\n';
        }
        else {
            cout << "False" << endl;
            cout << '\n';
        }
        delete bt;
    }
    fin.close();
    return 0;
}


/*tests
(((a+b)*c)-(d+(e+(f*g))))
(((a-b)+b)*c)
(((4-9)+1)*((0*2)+7))
((f+(g*e))-(t-(p*m)))
(((1-8)+(3-8))*(7*9))
(a+(b+c))
*/
