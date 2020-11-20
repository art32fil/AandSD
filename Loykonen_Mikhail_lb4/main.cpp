#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
T* readFromFile(ifstream& fin, int size){
    T* arr = new T[size];
    for (int i = 0; i<size; i++)
        fin >> arr[i];
    return arr;
}

template <typename T>
void printArr(T* arr, ofstream& fout, int size){
    fout << "[ ";
    for (int i = 0; i<size; i++){
        fout << arr[i] << " ";
    }
    fout << "]\n";
}

template<typename T>
void bubbleSort(T* arr, int left, int right){
    for (int i = left; i<=right; i++){
        for (int j = left; j<=right-1; j++){
            if (arr[j] > arr[j+1]){
                T tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

template <typename T>
void quickSort(T* arr, int left, int right, int size, int par, ofstream& fout){
    if ((right - left + 1) <= par){
        bubbleSort(arr, left, right);
        printArr<T>(arr, fout, size);
        return;
    }
    int mid = arr[(left + right)/2];
    int l = left;
    int r = right;
    while (left <= right){
        while (arr[left] < mid)
            left++;
        while (arr[right] > mid)
            right--;
        if (left <= right){
            T tmp = arr[right];
            arr[right] = arr[left];
            arr[left] = tmp;
            left++;
            right--;
        }
    }
    printArr<T>(arr, fout, size);
    if (l < right)
        quickSort<T>(arr, l, right, size, par, fout);
    if (r > left)
        quickSort<T>(arr, left, r, size, par, fout);
}

int main(){
    ifstream fin("test.txt");
    ofstream fout("result.txt");
    while (!fin.eof()){
        int size, par;
        fin >> size;
        fin >> par;
        int* arr = readFromFile<int>(fin, size);
        fout << "Исходный массив: ";
        printArr<int>(arr, fout, size);
        quickSort<int>(arr, 0, size-1, size, par, fout);
        fout << "Отсортированный массив: ";
        printArr<int>(arr, fout, size);
        fout << '\n';
        delete [] arr;
    }
    fin.close();
    fout.close();
    return 0;
}