#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

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
        vec = new Node [200];
        size = 200;
    }

    void resize(){
        int newSize = size + 200;
        Node* tmp = new Node [newSize];
        for (int i = 0; i<size; i++)
            tmp[i] = vec[i];
        delete [] vec;
        size = newSize;
        vec = tmp;
    }

    void addElem(T data, int ind){
        if (ind*2+2 == size)
            this->resize();
        vec[ind].data = data;
        vec[ind].left = ind*2 + 1;
        vec[ind].right = ind*2 + 2;
    }

    void prefix(int i){
        if (vec[i].left || vec[i].right){
            cout << vec[i].data << " ";
            prefix(vec[i].left);
            prefix(vec[i].right);
        }
    }

    void postfix(int i){
        if (vec[i].left || vec[i].right){
            postfix(vec[i].left);
            postfix(vec[i].right);
            cout << vec[i].data << " ";
        }
    }

    ~BinTree(){
        delete [] vec;
    }
};

void readBinTree(string& infix, int start, int end, int ind, BinTree<char>* bt){
    int depth = 0;
    if (start == end){
        bt->addElem(infix[start], ind);
        return;
    }
    for (int i = start; i<=end; i++){
        if (infix[i] == '(')
            depth++;
        if (infix[i] == ')')
            depth--;
        if (depth == 1 && (infix[i] == '+' || infix[i] == '-' || infix[i] == '*')){
            bt->addElem(infix[i], ind);
            readBinTree(infix, start+1, i-1, ind*2+1, bt);
            readBinTree(infix, i+1, end-1, ind*2+2, bt);
        }
    }
}

int result(BinTree<char>* bt, int ind, bool& err){
    if (bt->vec[ind].data == '+'){
        return result(bt, bt->vec[ind].left, err) + result(bt, bt->vec[ind].right, err);
    }
    if (bt->vec[ind].data == '-'){
        return result(bt, bt->vec[ind].left, err) - result(bt, bt->vec[ind].right, err);
    }
    if (bt->vec[ind].data == '*'){
        return result(bt, bt->vec[ind].left, err) * result(bt, bt->vec[ind].right, err);
    }
    if (isdigit(bt->vec[ind].data))
        return bt->vec[ind].data - '0';
    else{
        err = true;
        return 0;
    }
}

int main(){
    string infix;
    ifstream fin("input.txt");
    while(!fin.eof()){
        BinTree <char>* bt = new BinTree <char>;
        fin >> infix;
        cout << "input: " << infix << '\n';
        readBinTree(infix, 0, infix.length()-1, 0, bt);
        cout << "prefix: ";
        bt->prefix(0);
        cout << '\n';
        cout << "postfix: ";
        bt->postfix(0);
        bool err = false;
        int res = result(bt, 0, err);
        if (!err)
            cout << '\n' << "result = " << res;
        cout << "\n\n";
        delete bt;
    }
    fin.close();
    return 0;
}