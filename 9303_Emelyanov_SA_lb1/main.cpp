#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

void PrettyPrint(int &len){
    for (int i = 0; i < len; i++){
        cout << "~";
    }
}

void Error(){
    cout << "String contains extra - or incorrect characters!\n";
} 

bool sign ( char c){
    return (c == '+' )|| (c == '*' )|| (c == '-');
}

bool SimpleExpression(string &line, int& cur, int depth){
    PrettyPrint(depth);
    cout << "Start" << endl;
    if (isalpha(line[cur])||line[cur] == '('|| line[cur] == ')'||(sign(line[cur])&&cur > 0)){
        if (cur>0){
            if((sign(line[cur])&&line[cur-1]== ')')||(sign(line[cur])&&isalpha(line[cur-1]))){
                PrettyPrint(depth);
                cout << "End" << endl;
                return true;
            }
        }
        if(isalpha(line[cur])){
            if (cur>0){
                if(isalpha(line[cur-1])&&isalpha(line[cur])){
                    PrettyPrint(depth);
                    cout << "End" << endl;
                    return false;
                }
            }
            PrettyPrint(depth);
            cout << "End" << endl;
            return true;        
        }
        else if(line[cur] == '('){
            cur++;
            if(SimpleExpression(line, cur, depth+1)){
                cur++;
                if(SimpleExpression(line, cur, depth+1)){
                    cur++;
                    if(SimpleExpression(line, cur, depth+1)){
                        cur++;
                        if (line[cur] == ')'){
                            PrettyPrint(depth);
                            cout << "End" << endl;
                            return true;
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
        Error();
        PrettyPrint(depth);
        cout << "End" << endl;
        return false;
    }

}

int main(){
    string file_name;
    cout << "Enter the name of an input file: " << endl;
    getline(cin, file_name);
    ifstream input(file_name);
    if (!input){
        cout << "You haven't entered correct input file." << endl;
    }
    else{
        cout << "Simple expression analyser: " << endl;
        string line;
        while(getline(input, line)){
            int len = line.length();
            int cur = 0;
            bool flag = SimpleExpression(line, cur, 1);
            if (flag && (cur == (len - 1))){
                cout << "This is simple expression: ";
                cout << line << endl;
                cout<<"-------------------------------------------------------------------------------------"<<endl; 
            }
            else if(line[cur] == ')'||cur == 0){
                Error();
                cout << "This is not simple expression: ";
                cout << line << endl;
                cout<<"простое_выражение::=простой_идентификатор|(простое_выражение знак_операции простое_выражение)\n";
                cout<<"простой_идентификатор::= буква\n";
                cout<<"знак_операции:: = – | + | *\n";
                cout<<"-------------------------------------------------------------------------------------"<<endl;               
            }
            else{
                cout << "This is not simple expression: ";
                cout << line << endl;
                cout<<"простое_выражение::=простой_идентификатор|(простое_выражение знак_операции простое_выражение)\n";
                cout<<"простой_идентификатор::= буква\n";
                cout<<"знак_операции:: = – | + | *\n";
                cout<<"-------------------------------------------------------------------------------------"<<endl; 
            }
        }
    }
    return 0; 
}




