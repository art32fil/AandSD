#include <iostream>
#include <string>

using namespace std;


bool Brackets(string &input, int index) {
    index += 1;
    char c = input[index]; // for debug
    if (input[0] == 'B' && input.length() == 1) {
        return true;
    }

    if (input[0] == 'A' && input.length() == 1) {
        return true;
    }

    if((input[0] == '[' && input[input.length() - 1] != ']') || (input[0] == '(' && input[input.length() - 1] != ')'))
        return false;

    if(input[index] == '['){
        bool ans = Brackets(input, index);
        if(ans)
            return true;
        else
            return false;
    }

    if(input[index] == '('){
        bool ans = Brackets(input, index);
        if(ans)
            return true;
        else
            return false;
    }

    if(input[index] == ']'){
        if((index + 1) == input.length() && (input[index - 1] == ')' || input[index - 1] == 'A') ){
            return true;
        } else if(input[index - 1] != ')' && input[index - 1] != 'A')
            return false;
        else {
            bool ans = Brackets(input, index);
            if(ans)
                return true;
            else
                return false;
        }
    }

    if(input[index] == ')'){
        if((index + 1) == input.length() && (input[index - 1] == ']' || input[index - 1] == 'B') ){
            return true;
        } else if(input[index - 1] != ']' && input[index - 1] != 'B')
            return false;
        else {
            bool ans = Brackets(input, index);
            if(ans)
                return true;
            else
                return false;
        }
    }

    if(input[index] == 'A') {
        if(input[index - 1] == ']' ||
            input[index - 1] == '(' || input[index - 1] == 'B') {
            bool ans = Brackets(input, index);
            if(ans)
                return true;
            else
                return false;
        }
        else{
            return false;
        }
    }

    if(input[index] == 'B') {
        if(input[index - 1] == '[' ||
           input[index - 1] == ')' || input[index - 1] == 'A') {
            bool ans = Brackets(input, index);
            if(ans)
                return true;
            else
                return false;
        }
        else {
            return false;
        }
    }
}


int main() {
    string input;
    cin >> input;
    string A = "(()[])";
    string B = "[[]()]";
    bool ans = false;

    if(input[0] == '[' || input[0] == 'B' ||
            input[0] == '(' || input[0] == 'A'){
        ans = Brackets(input, -1);

    } else {
        cout << "Введена неверная строка" << endl;
        return 0;
    }

    if((input[0] == '(' || input[0] == 'A') && ans)
        cout << "Круглые скобки" << endl;
    else if((input[0] == '[' || input[0] == 'B') && ans)
        cout << "Квадратные скобки" << endl;


    if(!ans)
        cout << "Не скобки" << endl;

    return 0;
}
