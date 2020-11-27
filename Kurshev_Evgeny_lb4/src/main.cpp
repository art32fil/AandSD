#include <iostream>

template <typename T>
void my_qsort(T* arr, int start, int end){
    if(end - start > 0){
        int num_base = end;
        int cur = start;
        int quanity_base = 1;
        T base = arr[num_base];
        int size = num_base - cur;
        for(int i = 0; i < size; i++){
            if (base > arr[cur])
                cur += 1;
            else if (base == arr[cur]){
                for(int j = 0; j < num_base - cur - 1; j++){
                    T t = arr[cur + j];
                    arr[cur + j] = arr[cur + j + 1];
                    arr[cur + j + 1] = t;
                }
                num_base -= 1;
                quanity_base += 1;
            }
            else{
                T t = arr[cur];
                arr[cur] = arr[num_base - 1];
                arr[num_base - 1] = t;
                for(int k = 0; k < quanity_base; k++){
                    t = arr[num_base - 1 + k];
                    arr[num_base - 1 + k] = arr[num_base + k];
                    arr[num_base + k] = t;
                }
                num_base -= 1;
            }
        }
        std::cout << "less = ";
        if(num_base == 0)
            std::cout << "none ";
        else
            for(int i = 0; i < num_base; i++)
                std::cout << arr[i] << ' ';
        std::cout << "base = ";
        for (int i = 0; i < quanity_base; i++)
            std::cout << base << ' ';
        std::cout << "larger = ";
        if(end + 1 - (num_base + quanity_base) == 0)
            std::cout << "none ";
        else
            for(int i = num_base + quanity_base; i < end + 1; i++)
                std::cout << arr[i] << ' ';
        std::cout << "\n";
        my_qsort(arr, start, num_base - 1);
        my_qsort(arr, num_base + quanity_base, end);
    }
}

int main(){
    int size;
    std::cout << "Enter size of sorting array: ";
    std::cin >> size;
    if (size >= 1){
        int *arr = new int[size];
        std::cout << "Enter your array: ";
        for (int i = 0; i < size; i++)
            std::cin >> arr[i];
        my_qsort(arr, 0, size - 1);
        std::cout << "Sorted array: \n";
        for (int i = 0; i < size; i++)
            std::cout << arr[i] << ' ';
    }
    else
        std::cout << "Error! Size < 1!!\n";
    return 0;
}
