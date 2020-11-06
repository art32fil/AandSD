#include <iostream>
#include <fstream>

using namespace std;

class BinTree
{
private:
    string value;
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
        this->right=new BinTree;
    }

    void Create_left(){
        this->left=new BinTree;
    }

    string Get_value(){
        return this->value;
    }

    void Delete_left(){
        if(left!= nullptr){
            left->Delete_left();
            left->Delete_right();
            delete left;
        }
    }

    void Delete_right(){
        if(right!= nullptr){
            right->Delete_left();
            right->Delete_right();
            delete right;
        }
    }

    void Set_value(string val){
        this->value=val;
    }
};




string getLeft( string &str, int to)
{
    string out = "";
    for (int i = 1; i < to; i++)
    {
        out += str[i];
    }
    return out;
}

string getRight( string &str, int from)
{
    string out = "";
    for (int i = from+1; i < str.length()-1; i++)
    {
        out += str[i];
    }
    return out;
}

void read_tree(string str, BinTree *head ){
    string c="";
    int i = 0;
    int depth = 0;
    while (i < str.length()){
        if(str[i] == '(') depth++;
        if(str[i] == ')') depth--;
        if ( (str[i]=='+' || str[i]=='*') && depth == 1) {
            c  += str[i];
            break;
        }
        i++;
    }
    if(c == "+" || c == "*" ) {
        head->Set_value(c);
        head->Create_left() ;
        head->Create_right();
        string Left = getLeft(str, i);
        string Right = getRight(str, i);
        read_tree(Left, head->Get_left()) ;
        read_tree(Right, head->Get_right());
    }else{
        head->Set_value(str);
        return;
    }

}



bool Is_formula(BinTree &head) {
    if(head.Get_value()=="*" || head.Get_value()=="+") {
        if(head.Get_right()->Get_value()=="*" && head.Get_left()->Get_value()=="*") {
            if( head.Get_right()->Get_right()->Get_value() == head.Get_left()->Get_right()->Get_value()){
                return true;
            }else if(head.Get_right()->Get_left()->Get_value() == head.Get_left()->Get_left()->Get_value()){
                return true;
            }
            else if(head.Get_right()->Get_left()->Get_value() == head.Get_left()->Get_right()->Get_value()){
                return true;
            }else if(head.Get_right()->Get_right()->Get_value() == head.Get_left()->Get_left()->Get_value()){
                return true;
            }
        }
        return false;
    }
    return false;
}


void Change_tree(BinTree *left, BinTree *right, string root){
    string a,b,c;
    if(right->Get_right()->Get_value() == left->Get_right()->Get_value()){
        c=right->Get_right()->Get_value();
        a=right->Get_left()->Get_value();
        b=left->Get_left()->Get_value();
    }
    else if(right->Get_left()->Get_value() == left->Get_left()->Get_value()){
        c=right->Get_left()->Get_value();
        a=right->Get_right()->Get_value();
        b=left->Get_right()->Get_value();
    }
    else if(right->Get_left()->Get_value() == left->Get_right()->Get_value()){
        c=right->Get_left()->Get_value();
        a=right->Get_right()->Get_value();
        b=left->Get_left()->Get_value();
    }
    else if(right->Get_right()->Get_value() == left->Get_left()->Get_value()){
        c=right->Get_right()->Get_value();
        a=right->Get_left()->Get_value();
        b=left->Get_right()->Get_value();
    }
    right->Set_value(c);
    left->Set_value(root);
    left->Get_right()->Set_value(b);
    left->Get_left()->Set_value(a);
    right->Delete_left();
    right->Delete_right();
}

string ShowTree(BinTree &head){
    if(head.Get_value() == "+" || head.Get_value() == "*" )
    {
        return "("
               + ShowTree( *(head.Get_left()))
               + head.Get_value()
               + ShowTree( *(head.Get_right()))
               + ")";
    }
    return head.Get_value();
}

void DetourTree(BinTree *head){
    if((head->Get_value() == "+" || head->Get_value() == "*") && Is_formula(*head)){
        string s=head->Get_value();
        head->Set_value(head->Get_right()->Get_value());
        Change_tree(head->Get_left(),head->Get_right(),s);
    }else{
        if(head->Get_value()=="*" || head->Get_value()=="+"){
            if(head->Get_left()->Get_value()=="*" || head->Get_left()->Get_value()=="+"){
                DetourTree(head->Get_left());
            }
            if(head->Get_right()->Get_value()=="*" || head->Get_right()->Get_value()=="+"){
                DetourTree(head->Get_right());
            }
        }
    }
}

int main() {
    string path;
    cout<<"Enter file name:"<<'\n';
    getline(cin,path);
    ifstream input(path);
    if(!input){
        cout<<"Wrong file name, try again!\n";
    }
    else{
        string line;
        while(!input.eof()){
            getline(input,line);
            if(input.eof()) break;
            cout<<"Input formula:\n";
            cout<<line<<"\n";
            if(line[0]!='('){
                cout<<"Wrong string!\n";
                continue;
            }
            BinTree *tree=new BinTree;
            read_tree(line, tree);
            DetourTree(tree);
            cout<<"Output formula:\n";
            cout<<ShowTree(*tree)<<"\n";
        }
    }
    return 0;
}