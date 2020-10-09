#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool check (string str, int depth);
string trim (string str);

int main(){
    string input_file;
    cout << "Введите название файла " << endl;
    getline(cin, input_file);
    ifstream input(input_file);

    if (!input) {
        cout << "Входной файл неверный." << endl;
    } else {
        string str;
        getline(input, str);

        if (check(str, 1)){
            cout << "Это логическое выражение: " << str << endl;
        } else {
            cout << "Это не логическое выражение ";
            cout << str << endl;
        }
    }
    return 0;
}

bool check(string str, int depth) {
    cout << depth << endl << str << endl;

    str = trim(str);

    if (str.length() == 0) {
        cout << "Строка пустая. " << endl;
        return false;
    }

    if (str == "TRUE" || str == "FALSE") {
        return true;
    } else if (str.length() == 1 && isalpha(str[0])) {
        return true;
    } else if (str.length() >= 3 && str.substr(0, 3) == "NOT") {
        str = trim(str.substr(3, str.length() - 3));

        if (str.length() < 2 || str[0] != '(' || str[str.length() - 1] != ')') {
            return false;
        }

        return check(str.substr(1, str.length() - 2), depth + 1);
    } else if ((str.length() >= 3 && str.substr(0, 3) == "AND") || (str.length() >= 2 && str.substr(0, 2) == "OR")) {
        if (str.substr(0, 2) == "OR") {
            str = trim(str.substr(2, str.length() - 2));
        } else {
            str = trim(str.substr(3, str.length() - 3));
        }

        if (str.length() < 2 || str[0] != '(' || str[str.length() - 1] != ')') {
            return false;
        }

        str = str.substr(1, str.length() - 2);

        string tmp = "";
        int balance = 0;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] != ',' || (str[i] == ',' && balance != 0)) {
                tmp += str[i];

                if (str[i] == '(') {
                    balance++;
                } else if (str[i] == ')') {
                    balance--;
                }
            } else if (balance == 0) {
                if (!check(tmp, depth + 1)) {
                    return false;
                }
                tmp = "";
            }
        }

        return check(tmp, depth + 1);
    }

    return false;
}

string trim(string str) {
    int l = 0;
    while (l < str.length() && str[l] == ' ') {
        l++;
    }

    int r = str.length() - 1;
    while (r >= 0 && str[r] == ' ') {
        r--;
    }

    string result = "";
    for (int i = l; i <= r; i++) {
        result += str[i];
    }
    return result;
}
