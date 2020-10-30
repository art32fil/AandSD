#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
using namespace std;

template <class T> 
class stack
{
private:
    T* Buffer;
    int size;
    void addSize(){
        size += 50;
        T *tmp = new T [size];
        for (int i = 0; i < counter; i++)
        {
            tmp[i] = Buffer[i]; 
        }
        delete Buffer;
        Buffer = tmp;      
    }
public:
    int counter;
    int begin;
    stack(){
        size = 50;
        counter = 0;
        begin = 0;
        Buffer = new T [size];
    }
    void pop(){
        begin++;

    }
    T* getBuffer(int n){
        return &Buffer[n];
    }

    T get(){
        return Buffer[begin]; 
    }
    void push(T x){
        if( counter >= size-1 )
            addSize();

        Buffer[counter] = x;
        counter++;
    }
    bool isEmpty(){
        return (this->counter == this->begin);
    }
};

class BinTree
{
    
public:
    BinTree *lSub; 
    BinTree *rSub;
    string info;
    int level;
    BinTree* GetrSub(){
        return rSub;
    }
    BinTree* GetlSub(){
        return lSub;
    }
    BinTree* SetlSub(BinTree* lSub){
        this->lSub = lSub;
    }
    BinTree* SetrSub(BinTree* rSub){
        this->rSub = rSub;
    }
    BinTree(){
        info = "*";
        lSub = nullptr;
        rSub = nullptr;
    }
};

void CreatBinTree(BinTree* b, string& str, int& n, int level){
    if (n >= str.length() ) return;
    if (str[n] == '/'){
        n++;
        b->level = level;
        return;
    }
    else{
        b->info = str[n];
        b->level = level;
        n++;
        b->lSub = new BinTree;
        CreatBinTree(b->lSub,str,n, level + 1);
        b->rSub = new BinTree;
        CreatBinTree(b->rSub,str,n, level + 1);
    }
}

void ShowBinThreeDir (BinTree* head, stack<BinTree>& st, ofstream& fout){
    st.push(*head);
    while(!st.isEmpty()){
        if (st.get().info != "*"){
            if (head->lSub!=nullptr){
                st.push(*st.get().lSub);
            }
            if (head->rSub!=nullptr){
                st.push(*st.get().rSub);
            }
        }
        for(int i = 0; i < st.get().level; i++){
            fout<<"    ";
        }
        fout<<st.get().info<<"\n";
        st.pop();

    }
    return;
}

int main(){
    //BinTree b;
    ifstream fin;
    ofstream fout;
    int n = 0;
    fin.open("KLP.txt");
    fout.open("result1.txt", ios_base::app);
    string str ;
    while(!fin.eof()){
        BinTree b;
        stack<BinTree> st;
        n = 0;
        getline(fin,str);
        fout<< "\nИсходные данные: " << str<<"\n"<<"Результат:\n";
        CreatBinTree(&b,str,n, 0);
        ShowBinThreeDir(&b, st, fout);
    }
    fin.close();
    fout.close();
    return 0;
}
