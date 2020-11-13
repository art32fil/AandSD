#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stack>

using namespace std;

class BinTree{
private:
    char value;
    BinTree* left;
    BinTree* right;

public:
    BinTree(){
        left = nullptr;
        right = nullptr;
    }

    BinTree* Get_left(){
        return this->left;
    }

    BinTree* Get_right(){
        return this->right;
    }

    void Create_right(){
        this->right = new BinTree;
    }

    void Create_left(){
        this->left = new BinTree;
    }

    char Get_value() const{
        return this->value;
    }

    void Set_value(char val){
        this->value = val;
    }

    void add(char data, BinTree *p){
        p->Set_value(data);
        p->Create_left();
        p->Create_right();
    }
};

void read_tree(string& line, int start, int end, BinTree* tree){
    int def = 0;
    if (start == end)
        tree->add(line[start], tree);
    else{
        for (int i = start; i <= end; i++){
            if (line[i] == '(')
                def++;
            if (line[i] == ')')
                def--;
            if (def == 1 && (line[i] == '+' || line[i] == '-' || line[i] == '*')){
                tree->add(line[i], tree);
                read_tree(line, start+1, i-1, tree->Get_right());
                read_tree(line, i+1, end-1, tree->Get_left());
            }
        }
    }
}

void postfix(BinTree *p, stack<char> &st){
    if (p->Get_left() || p->Get_right()){
        st.push(p->Get_value());
        postfix(p->Get_left(), st);
        postfix(p->Get_right(), st);
    }
}

void prefix(BinTree *p, stack<char> &st){
    if (p->Get_left() || p->Get_right()){
        prefix(p->Get_left(), st);
        prefix(p->Get_right(), st);
        st.push(p->Get_value());
    }
}

int res(BinTree* tree, bool& err){
    if (tree->Get_value() == '+')
        return res(tree->Get_left(), err) + res(tree->Get_right(), err);
    if (tree->Get_value() == '-')
        return res(tree->Get_right(), err) - res(tree->Get_left(), err);
    if (tree->Get_value() == '*')
        return res(tree->Get_left(), err) * res(tree->Get_right(), err);
    if (isdigit(tree->Get_value()))
        return tree->Get_value() - '0';
    else{
        err = true;
        return 0;
    }
}

int main(){
    string path;
    cout << "Enter the file name:\n";
    getline(cin,path);
    ifstream input(path);
    if(!input)
        cout << "Wrong file name!\n";
    else{
        cout << '\n';
        string line;
        while(getline(input, line)){
            stack <char> s1, s2;
            auto *tree = new BinTree;
            read_tree(line, 0, line.length() - 1, tree);
            cout << "input: " << line << '\n';
            cout << "prefix: ";
            prefix(tree, s1);
            while(!s1.empty()){
                cout << s1.top();
                s1.pop();
            }
            cout << '\n';
            cout << "postfix: ";
            postfix(tree, s2);
            while(!s2.empty()){
                cout << s2.top();
                s2.pop();
            }
            cout << '\n';
            bool error = false;
            int r = res(tree, error);
            if (!error)
                cout << "res = " << r;
            cout << "\n\n";
        }
    }
    return 0;
}

