#include <iostream>
#include <fstream>
#include <string>
#include "list.h"

int main(){
    int inputFlag = 0;
    cout << "Enter 0 or 1, 0 means console input, 1 means file input: " << endl;
    cin >> inputFlag;
    cin.ignore(32767, '\n');

    string file_name;
    if (inputFlag == 1){
        cout << "Enter the name of an input file: " << endl;
        getline(cin, file_name);
        ifstream input(file_name);
        if (!input){
            cout << "You haven't entered correct input file." << endl;
        }
        else{
            cout << "Reverse list program: " << endl;
            string line;
            while(getline(input, line)){
                int len = line.length();
                int cur = 0;
                List* instance;
                readListFromFile(instance, line, cur, len);
                cout << "Result input:" << endl;
                writeList(instance);
                cout << "\n";
                List* reversed = instance -> reverse();
                cout << "Result reversed:" << endl;
                writeList(reversed);
                cout << "\n";
                destroy(reversed);
            }
        }
    }else if(inputFlag == 0){
        List* instance;
        cout << "Enter" << endl;
        readList(instance);
        cout << "Result input:" << endl;
        writeList(instance);
        cout << "\n";
        List* reversed = instance -> reverse();
        cout << "Result reversed:" << endl;
        writeList(reversed);
        cout << "\n";
        destroy(reversed);
    }
    else{
        cout << "Error" << endl;
    }
    return 0;
}