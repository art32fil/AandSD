
#include <iostream>
#include <time.h>
#include <stdlib.h>

//#define N 13

template<typename T>
void merge_sort(T* array, T* buffer, size_t size){
    if(size > 1){
        T* arr = array;
        T* buf = buffer;
        size_t left_size = size / 2;
        size_t right_size = size - left_size;

        merge_sort(array, buffer, left_size);
        merge_sort(&array[left_size], buffer, right_size);

        size_t left_ind = 0;
        size_t right_ind = left_size;
        size_t i = 0;
        while((left_ind < left_size) || (right_ind < (size))){
            if(arr[left_ind] < arr[right_ind]){
                buf[i] = arr[left_ind];
                
                left_ind++;
            }
            else{
                buf[i] = arr[right_ind];
                
                right_ind++;
            }
            i++;
            if (left_ind == left_size){
                for(int j = right_ind; j < (size); j++){
                    buf[i] = arr[j];
                    i++;
                }
                break;
            }
            if (right_ind == size){
                for(int j = left_ind; j < left_size; j++){
                    buf[i] = arr[j];
                    i++;
                }
                break;
            }
        }
        
        for(int j = 0; j < size; j++){
            arr[j] = buf[j];
        }
        

    }
    else{
        return;
    }
}

int main(){
    srand(time(NULL));

    int N = rand()%20 + 1;

    int* arr = new int[N];
    int* buf = new int[N];
    
    for(int i = 0; i < N; i++){
        arr[i] = rand()%100;
    }
    for(int i = 0; i < N; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    merge_sort(arr, buf, N);
    for(int i = 0; i < N; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    delete [] arr;
    delete [] buf;
    return 0;
}