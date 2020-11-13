#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
class BinTree{
private:
    struct Node{
        T data;
        int left = 0;
        int right = 0;
    };
    int size;
public:
    Node* vec;
    BinTree(){
        vec = new Node [100];
        size = 100;
    }

    void resize(){
        int newSize = size + 100;
        Node* tmp = new Node [newSize];
        for (int i = 0; i<size; i++)
            tmp[i] = vec[i];
        delete [] vec;
        size = newSize;
        vec = tmp;
    }

    void addNode(T data, int ind){
        if (ind*2+2 == size)
            this->resize();
        vec[ind].data = data;
        vec[ind].left = ind*2 + 1;
        vec[ind].right = ind*2 + 2;
    }

    bool doubleChecker(int counter){
        int id = 0;
        int num = 0;
        while (num < counter){
            if(isalnum(vec[id].data)) {
                for(int i = 0; i < id; i++) {
                    if (vec[i].data == vec[id].data)
                        return true;
                }
                num++;
            }
            id++;
        }
        return false;
    }

    ~BinTree(){
        delete [] vec;
    }
};

void readBinTree(string& infix, int start, int end, int ind, BinTree<char>* bt, int& counter){
    int depth = 0;
    if (start == end){
        bt->addNode(infix[start], ind);
        counter++;
        return;
    }
    for (int i = start; i<=end; i++){
        if (infix[i] == '(')
            depth++;
        if (infix[i] == ')')
            depth--;
        if (depth == 1 && (infix[i] == '+' || infix[i] == '-' || infix[i] == '*')){
            bt->addNode(infix[i], ind);
            readBinTree(infix, start+1, i-1, ind*2+1, bt, counter);
            readBinTree(infix, i+1, end-1, ind*2+2, bt, counter);
        }
    }
}

int main(){
    string infix;
    int counter = 0;
    ifstream fin("C:\\Users\\Masha\\CLionProjects\\untitled3\\input.txt");
    while(!fin.eof()){
        BinTree <char>* bt = new BinTree <char>;
        fin >> infix;
        cout << "infix: " << infix << '\n';
        readBinTree(infix, 0, infix.length()-1, 0, bt, counter);
        cout << '\n';
        if (bt->doubleChecker(counter)) {
            cout << "True" << endl;
        } else {
            cout << "False" << endl;
        }
        delete bt;
    }
    fin.close();
    return 0;
}