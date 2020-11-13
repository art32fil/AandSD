//((A)[B]) | A
//[[B](A)] | B
//
//[[[[B](A)]](((A)[B]))]
//
//[[[[[[B](A)]](((A)[B]))]](A)]
//
//[[B](A)] | B
//((A)[B]) | A

#include <iostream>

bool IsSquare(char*& ptr);
bool IsRound(char*& ptr);

using namespace std;

bool IsSquare(char* &ptr) {
    if (*ptr == 'B') { ptr++; return true; }
    else if (*ptr++ == '[') { 
        if (*ptr++ == '[') {
            if (IsSquare(ptr)) {
                if (*ptr++ == ']') {
                    if (*ptr++ == '(') {
                        if (IsRound(ptr)) {
                            if (*ptr++ == ')') { 
                                if (*ptr++ == ']') { 
                                    return true;
                                }
                                else
                                    cout << "Нет завершающей ]" << endl;
                            }
                            else
                                cout << "Нет завершающей )" << endl;
                        }
                        else
                            cout << "Круг ошибочен" << endl;
                    }
                    else
                        cout << "Нет (" << endl;
                }
                else
                    cout << "Нет ]" << endl;
            }
            else
                cout << "Квадрат ошибочен" << endl;
        }
        else
            cout << "Нет второй начинающей [" << endl;
    }
    else {
        cout << "Не [ и не B" << endl;
        cout << *ptr << endl;
    }
    return false;
}

bool IsRound(char*& ptr) {
    if (*ptr == 'A') { ptr++; return true; }
    else if (*ptr++ == '(') {
        if (*ptr++ == '(') { 
            if (IsRound(ptr)) { 
                if (*ptr++ == ')') { 
                    if (*ptr++ == '[') {
                        if (IsSquare(ptr)) { 
                            if (*ptr++ == ']') { 
                                if (*ptr++ == ')') { 
                                    return true;
                                }
                                else
                                    cout << "Нет завершающей )" << endl;
                            }
                            else
                                cout << "Нет завершающей ]" << endl;
                        }
                        else
                            cout << "Квадрат ошибочен" << endl;
                    }
                    else
                        cout << "Нет [" << endl;
                }
                else
                    cout << "Нет )" << endl;
            }
            else
                cout << "Круг ошибочен" << endl;
        }
        else
            cout << "Нет второй начинающей (" << endl;
    }
    else
        cout << "Не ( и не А" << endl;
    return false;
}

bool IsBracket(char* &ptr){
    bool a = false;
    if (*ptr == 'B' || *ptr == '[') a = IsSquare(ptr);  
    else if (*ptr == 'A' || *ptr == '(') a = IsRound(ptr); 
    else
        cout << "Hедопустимый начальный символ" << endl;
    if (a && *ptr != '\0') {
        cout << "Лишние символы" << endl;
        return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "rus");
    char str[256];;
    cout << "Введите предложение: " << endl;
    cin.getline(str, 256);
    char* ptr = str;
    bool a = false;

    if (*ptr != '\0') {
        if (IsBracket(ptr))
            cout << "ЭТО СКОБКИ" << endl;
        else
            cout << "ЭТО НЕ СКОБКИ" << endl;
    }
    else
        cout << "ПУСТО" << endl;
    return 0;
}