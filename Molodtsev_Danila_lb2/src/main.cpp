#include <iostream>
#include <string>
#include <fstream>
#include <vector>


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
    bool is_atomic;
    union{
        base atom;
        two_ptr pair;
    } Node;
};

List* Get_head(const List* s);//
List* Get_end(const List* s);
bool isAtom(const List* s);
bool isNull(const List* s);
List* Set_new_list(List* new_head, List* new_end);//
List* Set_atom(const base atom);//

void ReadList(List* &y,const string& line, int& cur, int& len,vector<int>& v);//
void ReadElem(List* &y,const string& line, int& cur, int& len,vector<int>& v);//
void ReadBranch(List* &y,const string& line, int& cur, int& len,vector<int>& v);//

void write_list(const List* x);//
void write_branch(const List* x);//

void destroy(List* elem);//

bool is_right(const string &str){
    int flag=0;
    if(str[0]!='('){
        return false;
    }
    for(int i=0;i<str.length();i++){
        if(str[i]=='('){
            flag++;
        }
        if(str[i]==')'){
            flag--;
        }
    }
    return !flag;
}

int main() {
    string path;
    cout<<"Enter the file name.\n";
    getline(cin,path);
    ifstream input(path);
    if(!input){
        cout<<"Wrong file name, try again!\n";
    }else{
        string analized_str;
        List* analized_list;
        vector<int> vect1;
        cout<<"Enter the analized string.\n";
        getline(cin,analized_str);

        int len = analized_str.length();
        int cur = 0;
        if(!is_right(analized_str)){
            cerr<<"Wrong analized string.\n";
            exit(1);
        }

        ReadList(analized_list,analized_str,cur,len,vect1);

        string file_line;
        while(getline(input, file_line)){
            if(!is_right(file_line)){
                cout<<"String "<<file_line<<" is wrong string.\n";
                continue;
            }
            vector<int> vect2;
            len = file_line.length();
            cur = 0;
            List* list_file;
            ReadList(list_file, file_line, cur, len,vect2);
            if(vect1==vect2){
                cout<<"List ";
                write_list(list_file);
                cout<<" and ";
                write_list(analized_list);
                cout<<" has the same structure.\n";
            }else{
                cout<<"List ";
                write_list(list_file);
                cout<<" and ";
                write_list(analized_list);
                cout<<" has the different structure.\n";
            }
        }
    }
    return 0;
}

List* Set_new_list(List* new_head, List* new_end){
    List* elem;
    if(isAtom(new_end)){
        cerr << "Error, tail is atomic" << endl;
        exit(1);
    }
    else{
        elem = new List;
        elem->is_atomic = false;
        elem->Node.pair.head = new_head;
        elem->Node.pair.tail = new_end;
        return elem;
    }
}

List* Set_atom(const base data){
    List* elem = new List;
    elem->is_atomic = true;
    elem->Node.atom = data;
    return elem;
}

List* Get_head(const List* elem){// PreCondition: not null (s)
    if (elem != nullptr){
        if (!isAtom(elem)){
            return elem->Node.pair.head;
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

List* Get_end(const List* elem){
    if (elem != nullptr){
        if (!isAtom(elem)){
            return elem->Node.pair.tail;
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

bool isAtom(const List* elem){
    if (elem == NULL){
        return false;
    }
    else {
        return (elem->is_atomic);
    }
}

bool isNull(const List* elem){
    return elem == NULL;
}

void ReadList(List* &y,const string& line, int& cur, int& len, vector<int>& v){
    while(line[cur] == ' '){
        cur++;
    }
    ReadElem(y, line, cur, len,v);
}

void ReadElem(List* &y,const string& line, int& cur, int& len, vector<int>& v){
    v.push_back(1);
    base prev = line[cur];
    if ( prev == ')'){
        cout << "Error" << endl;
        exit(1);
    }else if(prev != '('){
        y = Set_atom(prev);
    }else{
        ReadBranch(y, line, cur, len,v);
    }
}

void ReadBranch(List* &y,const string& line, int& cur, int& len, vector<int>& v){
    v.push_back(2);
    List* firstElem;
    List* secondElem;

    if(cur >= len){
        cout << "Error" << endl;
        exit(1);
    }
    else{
        cur++;
        while( line[cur] == ' ') cur++;
        if ( line[cur] == ')'){
            y = nullptr;
        }
        else{
            ReadElem(firstElem, line, cur, len,v);
            ReadBranch(secondElem, line, cur, len,v);
            y = Set_new_list(firstElem, secondElem);
        }
    }
}

void destroy(List* elem){
    if(elem!=nullptr){
        if (!isAtom(elem)) {
            destroy(Get_head(elem));
            destroy(Get_end(elem));
        }
        delete elem;
    }
}

void write_list(const List* elem){
    if(isNull(elem)){
        cout<<"()";
    }else if(isAtom(elem)){
        cout<<"("<<elem->Node.atom<<")";
    }else{
        cout<<"(";
        write_branch(elem);
        cout<<")";
    }
}

void write_branch(const List* elem){
    if(!isNull(elem)){
        write_list(Get_head(elem));
        write_branch(Get_end(elem));
    }
}