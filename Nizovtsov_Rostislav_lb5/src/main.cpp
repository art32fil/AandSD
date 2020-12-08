#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

void stringSort(string &symbols, int *freq){
    int n = symbols.length();
    int temp = 0;
    char ctemp;
    for (int k = 0; k < n; k++){
        for (int j = k % 2; j + 1 < n; j += 2){
            if (freq[j] < freq[j + 1]){
                temp = freq[j];
                freq[j] = freq[j + 1];
                freq[j + 1] = temp;
                ctemp = symbols[j];
                symbols[j] = symbols[j + 1];
                symbols[j + 1] = ctemp;
            }
        }
    }
}

void searchTree (string &symbols, int *freq, char lastCodeElem, string &code, int start, int end, string* &cipher)
{
    double totalSum = 0;
    int i, currSum = 0;
    string currCode = "";
    if(lastCodeElem != '\0')
        currCode = code + lastCodeElem;
    else
        currCode = code;

    if (start==end)
    {
        cipher[start] = currCode;
        if(symbols[start] == ' ')
            cout << "space (" << freq[start] << ") --- " << currCode << endl;
        else
            cout << symbols[start] << " (" << freq[start] << ") --- " << currCode << endl;
        return;
    }
    for (i=start;i<=end;i++)
        totalSum+=freq[i];
    totalSum/=2;
    i=start+1;
    currSum +=freq[start];
    while (fabs(totalSum-(currSum+freq[i])) < fabs(totalSum-currSum) && (i<end))
    {
        currSum+=freq[i];
        i++;
    }
    searchTree(symbols, freq, '0', currCode , start, i-1, cipher);
    searchTree(symbols, freq, '1', currCode , i, end, cipher);
}

void stringCoder(string &line, string* &cipher, string &symbols, ofstream &outFile){
    size_t pos;
    int size = line.length();
    cout << "Coded message: ";
    for(int i = 0; i < size; i++){
        pos = symbols.find(line[i]);
        cout << cipher[pos];
        outFile << cipher[pos];
    }
    cout << endl << endl;
    outFile << endl;
}

void stringAnalys(string &line, string &symbols, ofstream &outFile){
    int size = 0;
    int start_size = line.length();
    size_t pos;
    int* freq = new int[size];
    for(int i = 0; i < start_size; i++){
        pos = symbols.find(line[i]);
        if(pos == string::npos){
            symbols+=line[i];
            int *freq1 = new int[++size];
            for(int j = 0; j < size - 1; j++)
                freq1[j] = freq[j];
            freq1[size-1] = 1;
            delete[] freq;
            freq = freq1;
        }
        else{
            freq[pos]++;
        }
    }
    string* cipher = new string[size];
    cout << "Unique symbols:" << endl << symbols << endl;
    string code = "";
    stringSort(symbols, freq);
    searchTree(symbols, freq, '\0', code, 0, size - 1, cipher);
    stringCoder(line, cipher, symbols, outFile);
}

int main() {
    string file_name;
    cout << "Enter the name of an input file: " << endl;
    cin >> file_name;
    ifstream inFile(file_name);
    if (!inFile.is_open()){
        cout << "Permission denied or wrong path" << endl;
        return 0;
    }
    cout << "Result was saved in result.txt" << endl << endl;
    ofstream outFile("result.txt");
    string line;

    while(getline(inFile, line)){
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        cout << "Input line:" << endl << line << endl;
        outFile << line << endl;
        string symbols;
        stringAnalys(line, symbols, outFile);
    }
    cout << "End of work" << endl;
    inFile.close();
    outFile.close();
    return 0;
}
