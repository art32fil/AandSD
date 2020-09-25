#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

bool Brackets(string &line, int& cur, int &len, int depth);
void PrettyPrint(int &len);
void Error();

int main(){
    string file_name;
    cout << "Enter the name of an input file: " << endl;
    getline(cin, file_name);
    ifstream input(file_name);
    if (!input){
        cout << "You haven't entered correct input file." << endl;
    }
    else{
        cout << "Parenthesis analyser: " << endl;
        string line;
        while(getline(input, line)){
            int len = line.length();
            int cur = 0;
            bool b = Brackets(line, cur, len, 1);
            if (b && (cur == (len - 1))){
                cout << "This is parenthesis: ";
                cout << line << endl;
            }
            else{
                cout << "This is not parenthesis: ";
                cout << line << endl;
            }
        }
    }
    return 0; 
}

bool Brackets(string &line, int& cur, int &len, int depth){
    //cout << depth << " ";
    PrettyPrint(depth);
    cout << "Start" << endl;
    bool res = false;
    if(cur < len){
        if (line[cur] == 'A'){
                PrettyPrint(depth);
                cout << "End" << endl;
                return true;   
        }
        else if (line[cur] == '('){
            cur++;
            if((cur) < len){
                if (line[cur] == 'B'){
                    cur++;
                    res = Brackets(line, cur, len, depth+1);
                    if (res){
                        cur++;
                        res = Brackets(line, cur, len, depth+1);
                    }
                    else{
                        Error();
                        PrettyPrint(depth);
                        cout << "End" << endl;
                        return false;
                    }
                    if (res){
                        cur++;
                        if (cur < len){
                            PrettyPrint(depth);
                            cout << "End" << endl;
                            return (line[cur] == ')');
                        }
                        else{
                            Error();
                            PrettyPrint(depth);
                            cout << "End" << endl;
                            return false;
                        }
                    }
                    else{
                        Error();
                        PrettyPrint(depth);
                        cout << "End" << endl;
                        return false;
                    }
                }
                else{
                    Error();
                    PrettyPrint(depth);
                    cout << "End" << endl;
                    return false;
                }
            }
            else{
                Error();
                PrettyPrint(depth);
                cout << "End" << endl;
                return false;
            }
        }
        else{
            Error();
            PrettyPrint(depth);
            cout << "End" << endl;
            return false;
        }
    }
    else{
        cout << "End" << endl;
        PrettyPrint(depth);
        Error();
        return false;
    }
    
}

void PrettyPrint(int &len){
    for (int i = 0; i < len; i++){
        cout << "!";
    }
}


void Error(){
    cout << "String contains extra- or incorrect characters!" << endl;
    cout << "Correct format of string is: brackets := A | B(brackets brackets)" << endl;
}