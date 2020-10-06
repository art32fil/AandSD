#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

int strToDigit(string s, int start, int end, int& err){
    int size = end - start + 1;
    int d = 0;
    string str;
    for (int i = 0; i<size; i++){
        str[i] = s[start];
        start++;
    }
    str[size] = '\0';

    try{
        d = stoi(str);
    }
    catch(out_of_range){
        cout << "Одно из введенных чисел превышает максимально допустимое значение типа int\n";
        err = 1;
        return 0;
    }
    catch(invalid_argument){
        cout << "Строка не соответствует константному выражению\n";
        err = 1;
        return 0;
    }
    return d;
}

void printSpace(int depth){
    for (int i = 0; i<depth; i++){
        cout << "  ";
    }
}

int calculate(string s, int ind, int depth, int& err){
    printSpace(depth);
    cout << "Вызов calculate(" << depth << "): Глубина рекурсии: " << depth << ".\n";
    int res = 0, d1 = 0, d2 = 0, countSym = 0, end = 0;

    for (int i = ind; i<s.length(); i++){
        if (s[i] == '+'){
            end = i-1;
            d1 = strToDigit(s, end - countSym + 1, end, err);

            if (err){
                return 0;
            }

            countSym = 0;
            d2 = calculate(s, i+1, depth+1, err);

            if ((d2 > 0 && d1 > INT_MAX - d2) || (d2 < 0 && d1 < INT_MIN - d2)){
                cout << "Во время вычислений произошло переполнение типа int\n";
                err = 1;
            }
            else{
                res = d1 + d2;
            }

            if (err){
                return 0;
            }

            printSpace(depth);
            cout << "Завершение calculate(" << depth << "). Получившееся выражение: " << d1 << " + " << d2 << " = " << res << '\n';
            return res;
        }
        if (s[i] == '-'){
            end = i-1;
            d1 = strToDigit(s, end - countSym + 1, end, err);

            if (err){
                return 0;
            }

            countSym = 0;
            d2 = calculate(s, i+1, depth+1, err);
            
            if ((d2 > 0 && d1 < INT_MIN + d2) || (d2 < 0 && d1 > INT_MAX + d2)){
                cout << "Во время вычислений произошло переполнение типа int\n";
                err = 1;
            }
            else{
                res = d1 - d2;
            }

            if (err){
                return 0;
            }

            printSpace(depth);
            cout << "Завершение calculate(" << depth << "). Получившееся выражение: " << d1 << " - " << d2 << " = " << res << '\n';
            return res;
        }
        if (s[i] == '*'){
            end = i-1;
            d1 = strToDigit(s, end - countSym + 1, end, err);

            if (err){
                return 0;
            }

            countSym = 0;
            d2 = calculate(s, i+1, depth+1, err);

            if (d1 != 0){
                if (d2 > 0){
                    if (d1 > INT_MAX/d2){
                        cout << "Во время вычислений произошло переполнение типа int\n";
                        err = 1;
                    }
                }
                else{
                    if (d2 < INT_MIN/d1){
                        cout << "Во время вычислений произошло переполнение типа int\n";
                        err = 1;
                    }
                }
            }

            if (err){
                return 0;
            }

            res = d1*d2;
            printSpace(depth);
            cout << "Завершение calculate(" << depth << "). Получившееся выражение: " << d1 << " * " << d2 << " = " << res << '\n';
            return res;
        }
        countSym++;
    }

    res = strToDigit(s, s.length()-countSym, s.length()-1, err);

    if (err){
        return 0;
    }

    printSpace(depth);
    cout << "Завершение calculate(" << depth << "). Получившееся выражение: " << res << '\n';
    return res;
}

int main(){
    int depth = 0, res = 0, err = 0;
    string s;
    ifstream fin("tests.txt");
    ofstream fout("results.txt");
    while (fin >> s){
        cout << "Константное выражение: " << s << '\n';
        res = calculate(s, 0, depth, err);
        if (err){
            cout << "При выполнении работы программы произошла ошибка\n\n";
            fout << "При выполнении работы программы произошла ошибка\n";
            err = 0;
            continue;
        }
        cout << "Результат вычислений: " << res << "\n\n";
        fout << "Результат вычислений: " << res << '\n';
    }
    return 0;
}