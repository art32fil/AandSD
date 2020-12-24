#include <iostream>

using namespace std;

void printHeap(int* num, int n, int size) {
    cout << "[ " << num[0] << " ]\n";
    int tmpInd = 1;
    int numOfBrackets = 1;
    while (tmpInd < size) {
        for (int j = 0; j < numOfBrackets; j++) {
            cout << '[';
            for (int i = tmpInd; i < tmpInd + n; i++) {
                cout << ' ' << num[i] << ' ';
                if (&num[i] == &num[size-1]) {
                    cout << "]\n";
                    return;
                    
                }
            }
           
            cout << ']';
            tmpInd += n;
        }
        cout << '\n';
        numOfBrackets *= n;
    }
    cout << '\n';
}



void topDownSift(int* num, int n, int size, int start, int end) {
    int root = start;
    int current;
    int max;
    int t;
    while (1) {
        int child = root * n + 1;
        if (child > end) {
            break;
        }
        max = child;
        for (int i = 2; i < n+1 ; i++) {
            current = root * n + i;
            if (current > end) {
                break;
            }
            if (num[current] > num[max]) {
                max = current;
            }
        }
        if (num[root] < num[max]) {
            printHeap(num, n, size);
            cout << '\n';
            t = num[root];
            num[root] = num[max];
            num[max] = t;
            root = max;
        }
        else {
            break;
        }

    }
}



void topDownSort(int* num, int n, int size, int start, int end) {
    int t;
    for (int i = size-1; i>=0; i--) {
        topDownSift(num, n, size, i, size-1 );
    }
    for (int i = end; i < size-1; i++) {
        t = num[end];
        num[end] = num[0];
        num[0] = t;
        topDownSift(num, n, size, 0, end - 1);
    }

}

int leafSearch(int* num, int curr, int n, int size) {
    if (curr * n + 1 >= size) {
        return curr;
    }
    int max = curr * n + 1;

    for (int i = 2; i <= n; i++) {
        if (curr * n + i > size) {
            break;
        }
        if (num[curr * n + i] > num[max]) {
            max = curr * n + i;
        }
    }

    return leafSearch(num, max, n, size);
}



void bottomUpSift(int* num, int n, int size, int root) {
    if (root * n + 1 >= size) {
        return;
    }
    int curr = leafSearch(num, root, n, size);
    while (num[curr] < num[root]) {
        curr = (curr - 1) / n;
    }
    int tmp = num[curr];
    num[curr] = num[root];
    curr = (curr - 1) / n;
    while (curr > root) {
        int t = num[curr];  
        num[curr] = tmp;       
        tmp = t;         
        curr = (curr - 1) / n;
    }

    num[root] = tmp;
}



int main() {
    int size;
    cout << "enter the number of array elements: " << endl;
    cin >> size;

    if (size <= 0) {
        cout << "invalid data" << endl;
        return 0;
    } 
    
    cout << "enter an array : " << endl;
    int* num = new int[size];
    for (int i = 0; i < size; i++) {
        cin >> num[i];
    }

    int* numbers = new int[size];
    for (int i = 0; i < size; i++) {
        numbers[i] = num[i];
    }


    int n;
    cout << "enter value n: " << endl;
    cin >> n;

    if (n <= 0 ) {
        cout << "invalid data" << endl;
        return 0;
    } 

    cout << "unsorted heap looks something like this: " << endl;
    printHeap(num, n, size);

    cout << "how to sort?\n1.top-down\n2.bottom-up\n" << endl;
    int v ;
    
    while (1) {
        cin >> v;
        if (v != 1 && v != 2) {
            cout << "invalid data. there were only 2 options. try again bro\nhow to sort?\n1.bottom-up\n2.top-down" << endl;
        }
        else {
            break;
        }

    }
    
    if (v == 1) {
 
        topDownSort(num, n, size, 0, size-1);
        printHeap(num, n, size);

        char a;
        cout << "you can look at the bottom-up sort. do you want? [y/n]";
        cin >> a;
        int* answer = new int[size];
        switch (a) {
        case 'y':
            for (int i = size; i >= 0; i--) {
                cout << endl;
                bottomUpSift(numbers, n, size, i);
                printHeap(numbers, n, size);
                
            }

            cout << "\nsorted array:\n";

            for (int i = 0; i < size; i++) {
                answer[size - (i + 1)] = num[0];
                num[0] = num[size - (i + 1)];
                bottomUpSift(num, n, size - (i + 1), 0);
            }

            for (int i = 0; i < size; i++) {
                cout << answer[i] << ' ';
            }

            delete[] answer;
            return 0;
        case 'n':
            return 0;
        }

    }
    else if (v == 2) {

        topDownSort(num, n, size, 0, size - 1);
        printHeap(num, n, size);

        char a;
        cout << "you can look at the top-down sort. do you want? [y/n]\n";
        cin >> a;
        switch (a) {
        case 'y':
            topDownSort(numbers, n, size, 0, size - 1);
            printHeap(numbers, n, size);
    
            return 0;
        case 'n':
            return 0;
        }
    }

 
    delete[] num;
    delete[] numbers;

}
 