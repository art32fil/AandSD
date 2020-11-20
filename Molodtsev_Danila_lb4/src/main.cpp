#include <iostream>

static int iter=0;
template<typename T>
void merge_sort(T* array, int& size){
    int left_index;
    int right_index;
    int left_bord;
    int mid_bord;
    int right_bord;
    for (int i = 1; i < size; i *= 2){
        for (int j = 0; j < size - i; j = j+2*i){
            iter++;
            left_index = 0;
            right_index = 0;
            left_bord = j;
            mid_bord = j + i;
            right_bord = j+2*i;
            if(right_bord >= size){
                right_bord = size;
            }
            T* sorted_array = new T[right_bord - left_bord];
            while (left_bord + left_index < mid_bord && mid_bord + right_index < right_bord){
                if (array[left_bord + left_index] < array[mid_bord + right_index]){
                    sorted_array [left_index + right_index] = array[left_bord + left_index];
                    left_index += 1;
                }
                else{
                    sorted_array[left_index+right_index]=array[mid_bord+right_index];
                    right_index += 1;
                }
            }
            while (left_bord + left_index < mid_bord){
                sorted_array [left_index + right_index] = array[left_bord + left_index];
                left_index += 1;
            }
            while (mid_bord + right_index < right_bord){
                sorted_array[left_index + right_index] = array[mid_bord + right_index];
                right_index += 1;
            }
            std::cout<<"Sorted part:\n";
            for (int k = 0; k < left_index + right_index; k++){
                array[left_bord + k] = sorted_array[k];
                std::cout<<sorted_array[k]<<" ";
            }
            std::cout<<"\nArray on "<<iter<<" iteration.\n";
            for(int k=0;k<size;k++){
                std::cout<<array[k]<<" ";
            }
            std::cout<<"\n";
            delete sorted_array;
        }
    }
}

int main() {
    int size_of_arr;
    std::cout<< "Enter size of sorting array:"<<std::endl;
    std::cin>>size_of_arr;
    if(size_of_arr<=0){
        std::cerr<<"Size cannot be les than 1!\n";
    }else {
        float *array = new float[size_of_arr];
        std::cout << "Enter your array:" << std::endl;
        for (int i = 0; i < size_of_arr; i++) {
            std::cin >> array[i];
        }
        merge_sort(array, size_of_arr);
        std::cout << "Array:\n";
        for (int i = 0; i < size_of_arr; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << "\nWas sorted by " << iter << " iterations.\n";
    }
    return 0;
}







