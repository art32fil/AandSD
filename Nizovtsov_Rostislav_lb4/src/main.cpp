#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

void OddEvenSortSeq(int* mas, int size, ofstream &outFile)
{
    int n = size;
    int temp = 0;
    for(int i = 0; i < n; i++){
        cout << mas[i] << " ";
        outFile << mas[i] << " ";
    }
    cout << endl;
    outFile << endl;
    for (int k = 0; k < n; k++){
        if (k % 2 == 0)
            for (int j = 0; j + 1 < size; j += 2){
                if (mas[j] > mas[j + 1]){
                    temp = mas[j];
                    mas[j] = mas[j + 1];
                    mas[j + 1] = temp;
                }
            }
        else
            for (int j = 1; j + 1 < size; j += 2){
                if (mas[j] > mas[j + 1]){
                    temp = mas[j];
                    mas[j] = mas[j + 1];
                    mas[j + 1] = temp;
                }
            }
        for(int i = 0; i < size; i++){
            cout << mas[i] << " ";
            outFile << mas[i] << " ";
        }
        cout << "  <-" << k+1 << " шаг" << endl;
        outFile << "  <-" << k+1 << " шаг" << endl;
    }
    cout << endl;
    outFile << endl;
}

int main(){
    srand(time(NULL));

    cout << "Result was saved in result.txt" << endl;
    ofstream outFile("/home/rostislav/result.txt");
    cout << "If you want create new array write Continue, else write End" << endl;

    string line;
    while(getline(cin, line)){
        if(line == "End")
            break;
        else if(line != "Continue")
            continue;

        int size = rand()%10 + 5;
        int* mas = new int[size];
        for(int i = 0; i < size; i++){
            mas[i] = rand()%100;
        }
        OddEvenSortSeq(mas, size, outFile);
        delete [] mas;
    }
    return 0;
}
