#include "../Headers/BinTree.h"
#include <algorithm>
using namespace std;

string PostfixToPrefix(string postfix){
    string stack[50];
    int count = 0;
    string answer = "";
    string operators = "+-*";
    for (int i = 0; i < postfix.length(); i++){
        if (operators.find(postfix[i]) != -1){
            if (count >= 1){
                string op1 = stack[--count];
                stack[count--] = "";
                string op2 = stack[count];
                stack[count++] = postfix[i] + op2 + op1;
            } else {
                cerr << "Error: Wrong size" << endl;
                exit(1);
            }
        } else {
            stack[count++] = postfix[i];
        }
    }
    for (int i = 0; i < count; i++){
        answer += stack[i];
    }
    return answer;
}

string ClearSymbols(string line){
    for (int i = 0; i < line.length(); i++){
        if ((line[i] == ' ') || (line[i] == '\t')) {
            line.erase(i, 1);
            i--;
        }
    }
    return line;
}


int main(){
    string input;
    ifstream inputfile;
    ofstream outputfile;
    inputfile.open("input.txt");
    outputfile.open("output.txt", std::fstream::out | std::fstream::app);
    if (inputfile.is_open() && outputfile.is_open()){
        while(getline(inputfile, input)){
            cout << "Checking - " << input << endl;
            BinTree *bintree = new BinTree;
            if (input[0] == '('){
                string line = ClearSymbols(input);
                cout << line << endl;
                bintree->FunctionRead(bintree, line, 0, line.length()-1);
            } else {
                string line = PostfixToPrefix(input);
                reverse(line.begin(), line.end());
                bintree->ReadTree(bintree, line);
            }
            bintree->Display(bintree, 0);
            bintree->Diff(bintree);
            cout << "Postfix output - ";
            bintree->PostfixPrint(bintree);
            cout << endl;
            string res;
            cout << "Infix output - ";
            bintree->FunctionPrint(bintree, res);
            cout << res << endl;
            outputfile << res << endl;
            bintree->Destroy(bintree);
        }
        inputfile.close();
        outputfile.close();
    } else {
        cout << "Can't open file" << endl;
    }
    return 0;
}
