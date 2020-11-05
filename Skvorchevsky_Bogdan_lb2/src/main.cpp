#include <iostream>
#include <fstream>
#include <sstream>
#include "lisp.h"
#include "list.h"

using namespace std;
using namespace h_list;

int main(){
    std::string input1, input2;
    std::ifstream in("input.txt");
    getline(in, input1);
    getline(in, input2);
    int n = 0;
    int f = input1.length();
    while(n < input2.length()){
        if(isalpha(input2[n])){
            for(int j = 0; j < f; j++){
                if(input1[j] == input2[n])
                    input1[j] = input2[n+2];
            }
        }
        n++;
    }
    std::istringstream stream(input1);
    std::cin.rdbuf(stream.rdbuf());
	lisp s1, s2;
	read_lisp(s1);
    std::istringstream str(input2);
    std::cin.rdbuf(str.rdbuf());
	read_lisp(s2);
	cout << "Введен список: " << endl;
    std::vector<char> arr;
    write_lisp(s1, &arr);
    for(char i : arr)
        cout << i;
	cout << endl;
    cout << "Значения переменных: " << endl;
    std::vector<char> mass;
    write_lisp(s2, &mass);
    for(char i : mass)
        cout << i;
    cout << endl;
    cout << "Вычисление:" << endl;
    list::Stack s;
    for (int i = 0; i < arr.size(); i++){
        if (arr[i] == '+')
            s.push(s.pop() + s.pop());
        if (arr[i] == '-' && !isdigit(arr[i+1]))
            s.push(s.pop() - s.pop());
        if (arr[i] == '/')
            s.push(s.pop() / s.pop());
        if (arr[i] == '*')
            s.push(s.pop() * s.pop());
        if (arr[i-1] != '-' && (arr[i] >= '0') && (arr[i] <= '9'))
            s.push(0);
        if (arr[i-1] == '-' && isdigit(arr[i])) {
            if(!isdigit(arr[i+1]))
                s.push('0' - arr[i]);
            else{
                s.push(0 - (10*(arr[i] - '0') + (arr[i+1] - '0')));
                i+=2;
            }
        }
        while (arr[i-1] != '-' && (arr[i] >= '0') && (arr[i] <= '9')){
            s.push(10 * s.pop() + (arr[i++] - '0'));
        }
    }

    cout << "Результат = " << s.pop() << endl;
    s.destroy();
}
