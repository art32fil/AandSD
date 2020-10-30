#include <iostream>
#include <vector>
#include <algorithm> 
#include <fstream>
#include <unistd.h>
using namespace std;

template<typename T>

void bingo( T* data, int max, ofstream &fout)
{
    T nextValue = data[max];
    int max_arr = max;
    for(int i = max - 1; i != -1; i--){
        if(data[i]>data[max]) nextValue = data[max];
    }

    while (max && (data[max] == nextValue) && max--);

    while (max)
    {
        T value = nextValue;
        nextValue = data[max];
        for (int i = max - 1; i != -1; i--)
            {
                if (data[i] == value)
                {
                    std::swap(data[i], data[max]);
                    max--;
                    for (int j = 0; j < max_arr; j++)
                    {
                        fout << data[j] << " ";
                    }
                    fout<<" value: "<<value<<"\n";

                }
                else if (data[i] > nextValue)
                    nextValue = data[i];
            }
        while (max && (data[max] == nextValue) && max--);
    }
    //return data;
}
 
int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("test.txt");
    fout.open("Result.txt");
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
        fout << "\n\nВходные данные [ ";
        for (int j = 0; j < m; j++)
        {
            fout << arr[j] << " ";
        }
        fout << "]\n";

        bingo(arr, m,fout);
        fout << "Результат: [ ";
        for (int j = 0; j < m; j++)
        {
            fout << arr[j] << " ";
        }
        fout << "]\n";
        // delete res;
        delete arr;
    }
    fin.close();
    fout.close();
        

    return 0;

}