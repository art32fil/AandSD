#include <iostream>

using namespace std;

template <typename T>
void SortByMax(T pyramid[], int index, int size, int size_of_array){
    for (int i = 0; i < size_of_array; i++){
        cout << pyramid[i] << ' ';
    }
    cout << endl;
    int left_root = 2 * index + 1;
    int right_root = 2 * index + 2;
    int max = index;
    if ((left_root < size) && (pyramid[left_root] > pyramid[max])){
        max = left_root;
    }
    if ((right_root < size) && (pyramid[right_root] > pyramid[max])){
        max = right_root;
    }
    if (max != index){
        swap(pyramid[index], pyramid[max]);
        SortByMax(pyramid, max, size, size_of_array);
    }
}

template <typename T>
void SortByMin(T pyramid[], int index, int size, int size_of_array){
    for (int i = 0; i < size_of_array; i++){
        cout << pyramid[i] << ' ';
    }
    cout << endl;
    int left_root = 2 * index + 1;
    int right_root = 2 * index + 2;
    int min = index;
    if ((left_root < size) && (pyramid[left_root] < pyramid[min])){
        min = left_root;
    }
    if ((right_root < size) && (pyramid[right_root] < pyramid[min])){
        min = right_root;
    }
    if (min != index){
        swap(pyramid[index], pyramid[min]);
        SortByMin(pyramid, min, size, size_of_array);
    }
}

template <typename T>
void PyramidSort(T pyramid[], int size, int sort_type){
    for (int i = (size / 2 - 1); i >= 0; i--){
        if (sort_type == 1){
            SortByMax(pyramid, i, size, size);
        } else {
            if (sort_type == 2){
                SortByMin(pyramid, i, size, size);
            } else {
                cout << "Wrong choice" << endl;
                return;
            }
        }
    }
    for (int i = (size - 1); i >= 0; i--){
        swap(pyramid[0], pyramid[i]);
        if (sort_type == 1){
            SortByMax(pyramid, 0, i, size);
        } else {
            SortByMin(pyramid, 0, i, size);
        }
    }
}

int main(){
    int quantity = 0;
    cout << "Amount of numbers = ";
    cin >> quantity;
    int array[quantity];
    for (int i = 0; i < quantity; i++){
        array[i] = (rand() % (2 * quantity)) - quantity;
    }
    cout << "Generated array: ";
    for (int i = 0; i < quantity; i++){
        cout << array[i] << ' ';
    }
    cout << endl;
    int choice = 0;
    cout << "The way to sort ('1' to min->max; '2' to max->min): ";
    cin >> choice;
    PyramidSort(array, quantity, choice);
    cout << "Result: ";
    for (int i = 0; i < quantity; i++){
        cout << array[i] << ' ';
    }
    cout << endl;
    return 0;
}
