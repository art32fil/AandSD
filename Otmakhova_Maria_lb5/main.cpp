#include <iostream>

using namespace std;

void printHeat(int* num, int n, int size) {
    cout << "[ " << num[0] << " ]\n";
    int tmpInd = 1;
    int numOfBrackets = 1;
    while(tmpInd < size) {
        for(int j = 0; j < numOfBrackets; j++) {
            cout << '[';
            for (int i = tmpInd; i < tmpInd + n; i++) {
                cout << ' ' << num[i] << ' ';
            }
            cout << ']';
            tmpInd += n;
        }
        cout << '\n';
        numOfBrackets *= n;
    }
    cout << '\n';
}

void pathToLeaf(int index, int n, int* num, int size) {
    if (index*n+1 >= size) {
        return;
    }
    int max = num[index*n+1];
    int max_pos = index*n+1;
    for(int i = index*n + 1; (i <= index * n + n) && (i < size); i++ ) {
        if (num[i] > max) {
            max = num[i];
            max_pos = i;
        }
    }
    cout << max << ' ';
    pathToLeaf(max_pos, n, num, size);
}

int main() {
    int size;
    cout << "enter the number of array elements: " << endl;
    cin >> size;

    if(size<=0) {
        cout << "invalid data" << endl;
        return 0;
    }

    cout << "enter an array : " << endl;

    int* num = new int[size];
    for( int i = 0; i < size; i++) {
        cin >> num[i];
    }

    int n;
    cout << "enter value n: " << endl;
    cin >> n;

    if(n<=0) {
        cout << "invalid data" << endl;
        return 0;
    }

    cout << "heap looks something like this: " << endl ;
    printHeat(num, n, size);

    cout << "path to leaf: ";

    cout << num[0] << ' ';
    pathToLeaf(0, n, num, size);

    delete[] num;
    return 0;
}


