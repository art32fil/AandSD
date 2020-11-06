#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

template <class T> 
class stack
{
private:
    T* Buffer;
    int size;
    int counter;
    void addSize(){
        size += 50;
        T *tmp = new int[size];
        for (int i = 0; i < counter; i++)
        {
            tmp[i] = Buffer[i]; 
        }
        delete Buffer;
        Buffer = tmp;      
    }
public:
    stack(){
        size = 50;
        counter = 0;
        Buffer = new int[size];
    }
    void pop(){
        --counter;
        if(counter < 0 ) 
            counter = 0;

    }
    T top(){
        return Buffer[counter-1]; 
    }
    void push(int x){
        if( counter >= size-1 )
            addSize();

        Buffer[counter] = x;
        counter++;
    }
    bool isEmpty(){
        return counter <= 0;
    }

    void show(ofstream &fout){
        fout << " "; 
        for (int i = 0; i < counter; i++)
        {
            fout << " [ "<< Buffer[i] << " ] "; 
        }
        fout << "\n"; 
    }
};


template <class T>
class listStack 
{
private:
    stack <T> *st;
    int count, size;
    void addSize(){
        size += 50;
        stack <T>*tmp = new stack <T>[size];
        for (int i = 0; i < count; i++)
        {
            tmp[i] = st[i]; 
        }
        delete st;
        st = tmp;      
    }
public:
    listStack(){
        size = 50;
        st = new stack<T>[size];
        count = 0;
    }
    void push(T x) {
        for (int i = 0; i < count; i++)
        {
            if( x < st[i].top() ){
                st[i].push(x);
                return;
            }
        }
        st[count].push(x);
        count++;
    }
    void show(ofstream &fout){
        fout << "\n"; 
        for (int i = 0; i < count; i++)
        {
            if(st[i].isEmpty()) 
                continue;
            fout << "stak[" << i << "] = "; 
            st[i].show(fout);
        }
        fout << "\n"; 
    }
    T get(){

        int tmp_num;
        int tmp;

        for (int i = 0; i < count; i++)
        {
            if(st[i].isEmpty()) 
                continue;
            tmp = st[i].top();
            tmp_num = i;
            break;
        }
        
        for (int i = 0; i < count; i++)
        {    
            if(st[i].isEmpty()) 
                continue;

            if( tmp > st[i].top() )
            {
                tmp = st[i].top();
                tmp_num = i;
            }
        }
        st[tmp_num].pop();
        return tmp;
    }
};


int * patienceSorting(int *mas, int size, ofstream &fout){

    listStack <int>ls;
    for (int i = 0; i < size; i++)
    {

        ls.push(mas[i]);
        fout << "[ ";
        for (int j = i; j < size-1; j++)
        {
            fout << mas[j] << ", ";
        }
        fout << mas[i] << " ]\n";

        ls.show(fout);
    }

    for (int i = 0; i < size; i++)
    {

        mas[i] = ls.get();
        fout << "[ ";
        for (int j = 0; j < i-1; j++){

            fout << mas[j] << ", ";
        }
        fout << mas[i-1] << " ]\n";
        ls.show(fout);
    
    }
    return mas;
}

int main(int argc, char const *argv[]) 
{

    ifstream fin;
    ofstream fout;
    if( argc > 1 ){

        fin.open(argv[1]);
        if( argc > 2 ) {            
            fout.open(argv[2], ios_base::app);
        }
        else {
            fout.open("ResultPatienceSorting.txt");
        }
        int n, m;
        fin >> n;
        for (int i = 0; i < n; i++)
        {
            fin >> m;
            int *arr = new int[m+1];
            for (int j = 0; j < m; j++)
            {
                fin >> arr[j];
            }
            fout << "\n\n[   in   ]\n[  Array ]\n";
            int *res = patienceSorting(arr, m, fout);
            fout << "[   Result   ]\n[";
            for (int j = 0; j < m-1; j++)
            {
                fout << res[j] << ", ";
            }
            fout << res[m-1] << " ]";
            // delete res;
            delete arr;
        }
        fin.close();
        fout.close();
    }    
    return 0;
}