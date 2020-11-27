#include <iostream>

using namespace std;

void quickSort(int* num, int left, int right, int n)
{
    cout << "quickSort called for " << left << " to " << right << " : ";
    for( int i = left; i <= right; i++) {
        cout << num[i] << ' ';
    }
    cout << '\n';
    int pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = num[left];
    while (left < right)
    {
        while ((num[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            num[left] = num[right];
            left++;
        }
        while ((num[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            num[right] = num[left];
            right--;
        }
    }
    num[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;

    if (left < pivot) {
        quickSort(num, left, pivot - 1, n);

    }
    if (right > pivot) {
        quickSort(num, pivot + 1, right, n);

    }
}

int main() {
    int n;
    cout << "enter the number of array elements: " << endl;
    cin >> n;
    int* num = new int[n];
    for( int i = 0; i < n; i++) {
        cin >> num[i];
    }

    quickSort(num, 0, n-1, n);

    cout << "sorted array: " << endl;
    for( int i = 0; i < n; i++) {
        cout << num[i] << ' ';
    }
    delete[] num;
    return 0;
}