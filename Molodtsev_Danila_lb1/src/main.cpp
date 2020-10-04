#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

static int depth=0;
static int curr_ind=0;
static int len=0;

void PrettyPrint(int is_start);
void ErrorPrint(int error);
bool is_row_of_brackets(string &analized_str);
bool is_brackets(string &analized_str);
bool main_analizator(string analized_str);

int main() {
    string path;
    string analized_brack;
    cout<<"Enter file name:\n";
    getline(cin,path);
    fstream input_file(path);
    if(!input_file.is_open()){
        cout<<"Wrong filename.\n";
    }else{
        cout<<"File has opened.\n\n";
    }
    while(getline(input_file,analized_brack)){
        if(main_analizator(analized_brack)){
            cout<<"These brackets are right: "<<analized_brack<<'\n';
        }else{
            cout<<"These brackets are wrong: "<< analized_brack <<'\n';
        }
        depth=0;
        curr_ind=0;
        len=0;
    }
    return 0;
}

void ErrorPrint(int error){
    switch (error) {
        case 1:
            cout<<"Error 1: Wrong structure of brackets.\n";
            break;
        case 2:
            cout<<"Error 2: Wrong structure of row of brackets.\n";
            break;
        default:
            break;
    }
}

void PrettyPrint(int is_start) {
    if(is_start==1) {
        for (int i = 0; i < depth; i++) {
            cout << "#";
        }
        cout << "Start\n";
        depth++;
    }else if(is_start==2){
        depth--;
        for (int i = 0; i < depth; i++) {
            cout << "#";
        }
        cout << "End\n";
    }
    curr_ind++;
}

bool main_analizator(string analized_str){
    len = analized_str.length();
    if(analized_str[0]!='A'){
        ErrorPrint(1);
        return false;
    }else{
        return is_brackets(analized_str);
    }
}

bool is_row_of_brackets(string &analized_str){
    if(depth==0 && curr_ind==len){
        return true;
    }else if (analized_str[curr_ind]=='A'){
        PrettyPrint(0);
        return is_row_of_brackets(analized_str);
    }else if(analized_str[curr_ind]==';'){
        if(analized_str[curr_ind+1]=='A'){
            PrettyPrint(0);
            return is_row_of_brackets(analized_str);
        }else{
            ErrorPrint(2);
            return false;
        }
    }else if(analized_str[curr_ind]=='('){
        PrettyPrint(1);
        return is_row_of_brackets(analized_str);
    }else if(analized_str[curr_ind]==')'){
        PrettyPrint(2);
        return is_brackets(analized_str);
    }else{
        ErrorPrint(1);
        return false;
    }
}

bool is_brackets(string &analized_str){
    if(depth==0 && curr_ind==len){
        return true;
    }
    else if(analized_str[curr_ind]=='A'){
        PrettyPrint(0);
        return is_brackets(analized_str);
    }else if(analized_str[curr_ind]=='('){
        if(analized_str[curr_ind+1]=='A'){
            PrettyPrint(1);
            return is_row_of_brackets(analized_str);
        }else{
            ErrorPrint(1);
            return false;
        }
    }else if(analized_str[curr_ind]==')'){
        PrettyPrint(2);
        return is_brackets(analized_str);
    }else if(analized_str[curr_ind]==';'){
        if(analized_str[curr_ind+1]=='A'){
            PrettyPrint(0);
            return is_row_of_brackets(analized_str);
        }else{
            ErrorPrint(1);
            return false;
        }
    }else {
        ErrorPrint(1);
        return false;
    }
}