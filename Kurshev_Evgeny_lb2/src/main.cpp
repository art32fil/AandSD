#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

typedef char base;

class List;

class two_ptr{
public:
    List* head;
    List* tail;
};

class List{
public:
    bool tag;
    union{
        base atom;
        two_ptr pair;
    } node;
};

void insert_at_bottom(char x, stack<char>& st);
void reverse(stack<char>& st);
List* head(const List* s);
List* end(const List* s);
bool isAtom(const List* s);
bool isNull(const List* s);
List* new_list(List* new_head, List* new_end);
List* make_atom(base atom);

void ReadList(List* &L, const string& str, int& cur, int& len,vector<char>& v, stack<char> &st, vector<char>& v2);//
void ReadElement(List* &L, const string& str, int& cur, int& len,vector<char>& v, stack<char> &st, vector<char>& v2);//
void ReadLine(List* &L, const string& str, int& cur, int& len,vector<char>& v, stack<char> &st, vector<char>& v2);//

void write_list(const List* x);
void write_branch(const List* x);

void destroy(List* elem);
bool isRight(const string &str);

int main() {
    string path;
    cout<<"Enter the file name:\n";
    getline(cin,path);
    ifstream input(path);
    if(!input)
        cout<<"Wrong file name!\n";
    else{
        cout << '\n';
        string line;
        while(getline(input, line)){
            if(!isRight(line)){
                cout << line <<" is wrong string!!\n\n";
                continue;
            }
            vector<char> vect, vect2;
            stack<char> st;
            int len = line.length();
            int cur = 0;
            List* L;
            ReadList(L, line, cur, len, vect, st, vect2);
            reverse(st);
            stack<char> tmp = st;
            cout << "Hierarchical list ";
            write_list(L);
            cout << " has " << vect2.size() << " different atoms" << '\n';
            cout << "Linear list = (";
            while(!tmp.empty()){
                cout << tmp.top();
                tmp.pop();
            }
            cout << ")\n\n";

        }
    }
    return 0;
}

List* new_list(List* new_head, List* new_end){
    List* elem;
    if(isAtom(new_end)){
        cerr << "Error, tail = atomic!" << endl;
        exit(1);
    }
    else{
        elem = new List;
        elem->tag = false;
        elem->node.pair.head = new_head;
        elem->node.pair.tail = new_end;
        return elem;
    }
}

List* make_atom(base atom){
    List* elem = new List;
    elem->tag = true;
    elem->node.atom = atom;
    return elem;
}

List* head(const List* s){
    if (s != nullptr){
        if (!isAtom(s)){
            return s->node.pair.head;
        }else {
            cerr << "Error: Head(atom) \n";
            exit(1);
        }
    }
    else {
        cerr << "Error: Head(nullptr) \n";
        exit(1);
    }
}

List* end(const List* s){
    if (s != nullptr){
        if (!isAtom(s)){
            return s->node.pair.tail;
        }
        else {
            cerr << "Error: Tail(atom) \n";
            exit(1);
        }
    }
    else {
        cerr << "Error: Tail(nullptr) \n";
        exit(1);
    }
}

bool isAtom(const List* s){
    if (s == nullptr){
        return false;
    }
    else {
        return (s->tag);
    }
}

bool isNull(const List* s){
    return s == nullptr;
}

void destroy(List* elem){
    if(elem != nullptr){
        if (!isAtom(elem)) {
            destroy(head(elem));
            destroy(end(elem));
        }
        delete elem;
    }
}

void write_list(const List* x){
    if(isNull(x))
        cout << "()";
    else if(isAtom(x))
        cout << "(" << x->node.atom << ")";
    else{
        cout << "(";
        write_branch(x);
        cout << ")";
    }
}

void write_branch(const List* x){
    if(!isNull(x)){
        write_list(head(x));
        write_branch(end(x));
    }
}

void ReadList(List* &L, const string& str, int& cur, int& len, vector<char>& v, stack<char> &st, vector<char>& v2){
    while(str[cur] == ' ')
        cur += 1;
    ReadElement(L, str, cur, len, v, st, v2);
}

void ReadElement(List* &L, const string& str, int& cur, int& len, vector<char>& v, stack<char> &st, vector<char>& v2){
    base prev = str[cur];
    v.push_back(prev);
    if(prev == ')'){
        cout << "Error" << endl;
        exit(1);
    }else if(prev != '('){
        if(find(v2.begin(), v2.end(), str[cur]) == v2.end())
            v2.push_back(prev);
        st.push(prev);
        L = make_atom(prev);
    }else{
        ReadLine(L, str, cur, len, v, st, v2);
    }
}

void ReadLine(List* &L, const string& str, int& cur, int& len, vector<char>&v , stack<char> &st, vector<char>& v2){
    List* firstElem;
    List* secondElem;
    if(cur >= len){
        cout << "Error!\n" << endl;
        exit(1);
    }
    else{
        cur++;
        while(str[cur] == ' ') cur++;
        if (str[cur] == ')'){
            v.push_back(str[cur]);
            L = nullptr;
        }
        else{
            ReadElement(firstElem, str, cur, len, v, st, v2);
            ReadLine(secondElem, str, cur, len, v, st, v2);
            L = new_list(firstElem, secondElem);
        }
    }
}

void insert_at_bottom(char x, stack<char>& st){
    if(st.empty())
        st.push(x);
    else{
        char a = st.top();
        st.pop();
        insert_at_bottom(x, st);
        st.push(a);
    }
}

void reverse(stack<char>& st){
    if(!st.empty()){
        char x = st.top();
        st.pop();
        reverse(st);
        insert_at_bottom(x, st);
    }
}

bool isRight(const string &str){
    int errors = 0;
    if(str[0] != '(')
        return false;
    for(char i : str){
        if(i == '(')
            errors++;
        else if(i == ')')
            errors--;
    }
    if(!errors)
        return true;
    else
        return false;
}