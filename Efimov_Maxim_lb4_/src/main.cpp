#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
void Swap(T& first,T& second,std::ofstream &fout){
    std::cout<<"Смена "<<first<<" на "<<second;
    fout<<"Смена "<<first<<" на "<<second;
    std::cout<<std::endl;
    fout<<std::endl;
    T tmp = first;
    first = second;
    second = tmp;
}
template <typename T>
void Print(T* arr, int n, std::ofstream &fout,int change,T buf){
std::cout<<"Смена номер "<<change<<" Текущий буфер: "<<buf;
fout<<"Смена номер "<<change<<" Текущий буфер: "<< buf;
std::cout<<std::endl;
fout<<std::endl;
for (int i =0; i<n; i++) {
        std::cout << arr[i]<<' ';
        fout << arr[i]<<' ';
 }
std::cout<<std::endl;
fout<<std::endl;
}

template <typename T>
void Sort (T* arr, int n, std::ofstream &fout)
{ 
    int change = 0; 
    for (int first_cycle=0; first_cycle <=n-1; first_cycle++) 
    { 
        T buf = arr[first_cycle]; 
        int possition = first_cycle; 
        for (int g = first_cycle+1; g<n; g++) 
            if (arr[g] < buf ) 
                possition++; 
        if (possition == first_cycle) 
            continue; 
  
        while (buf == arr[possition]) 
            possition += 1; 
        if (possition != first_cycle) 
        {
            Swap(buf , arr[possition],fout); 
            change++; 
            Print(arr,n,fout,change,buf);
        } 


        while (possition != first_cycle) 
        { 
            possition = first_cycle; 
  
            for (int i = first_cycle+1; i<n; i++) 
                if (arr[i] <  buf ) 
                    possition += 1; 
            while (buf == arr[possition]) 
                possition += 1; 
            if (buf != arr[possition]) 
            { 
                Swap( buf , arr[possition],fout); 
                change++; 

                Print(arr,n,fout,change,buf);
            } 
        } 
    } 
} 

int main(int argc, char const *argv[]){

std::ifstream fin;
std::ofstream fout;
    if( argc > 1 ){
        fin.open(argv[1]);
        if( argc > 2 ) {            
            fout.open(argv[2], std::ios_base::app);
        }
        else {
            fout.open("result.txt");
        }
        int m;
        fin >> m;
        int *arr = new int[m];
        for (int j = 0; j < m; j++)
        {
            fin >> arr[j];
        }
        Sort(arr, m, fout);
        delete[] arr;
        fin.close();
        fout.close();
    }

else{
    fout.open("result.txt");
    int m;
    std::cin >> m;
    int *arr = new int[m];
    for (int j = 0; j < m; j++)
    {
        std::cin >> arr[j];
    }
    Sort(arr, m, fout);
    delete[] arr;
    
}
return 0;
}





