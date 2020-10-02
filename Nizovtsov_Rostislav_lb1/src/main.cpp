#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool functionF(ifstream& inFile, ofstream& outFile);

int main()
{
    string file_name;
    cout << "Enter the name of an input file: " << endl;
    cin >> file_name;
    ifstream inFile(file_name);
    if (!inFile.is_open()){
        cout << "Permission denied or wrong path";
        return 0;
    }
    cout << "Result was saved in result.txt" << endl;
    ofstream outFile("/home/rostislav/result.txt");
    int rowCount = 1;
    while(!functionF(inFile, outFile)){
        outFile << endl;
        cout << "Reading " << rowCount << "row" << endl;
        rowCount++;
    }
    cout << "End of work" << endl;
    inFile.close();
    outFile.close();
    return 0;
}

bool functionF(ifstream &inFile, ofstream &outFile){
    bool isEOF = false;
    string part = "";
    char currentChar = '\0';
    currentChar = inFile.get();
    while(currentChar != EOF && currentChar != '/' && currentChar != '\n'){
        part = part + currentChar;
        currentChar = inFile.get();
    }
    if(currentChar == '/'){
        isEOF = functionF(inFile, outFile);
    }
    outFile << part;
    if(isEOF || (currentChar == EOF))
        return true;
    return false;
}
