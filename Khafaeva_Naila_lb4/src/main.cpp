#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;

void my_qsort(int*& arr, int start, int end, int size) {
    if (end - start <= 0) {
        return;
    }

    int pivot = start;
    int success = start;
    int temp;
    int i = start + 1;

    while (i <= end) {
        if (arr[i] < arr[pivot]) {
            success = i;
        } else {
            temp = i + 1;
            while (temp <= end) {
                if (arr[temp] < arr[pivot]) {
                    success = i;
                    int cur = arr[temp];
                    arr[temp] = arr[i];
                    arr[i] = cur;
                    break;
                }
                temp++;
            }
            if (arr[i] >= arr[pivot]) {
                break;
            }
        }
        i++;
    }
    if (success != start) {
        int cur = arr[success];
        arr[success] = arr[pivot];
        arr[pivot] = cur;
    }
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "Check from " << start << " to " << end << endl;
    my_qsort(arr, start, success - 1, size);
    my_qsort(arr, success + 1, end, size);
}

int main() {
    srand(time(NULL));
    int size = rand() % 10 + 5;
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;
    my_qsort(arr, 0, size - 1, size);
    cout << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    delete[] arr;
    return 0;
}
