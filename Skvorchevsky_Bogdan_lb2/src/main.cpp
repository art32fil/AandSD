#include <iostream>
#include <fstream>
#include <cctype>
#include "list.h"

using namespace std;
using namespace list;

int main () {
	char a[100];
	ifstream fin("input.txt");
	fin >> noskipws;
	if (!fin ) {
		cout << "Не удаётся открыть файл на чтение!\n";
		return 1;
	}
	int n1 = 100;
	int n = 0;
	cout << "Вы ввели: ";
	char sline[50];
    char tmp[100];
	while (n < n1 && fin >> tmp[n]) {
        cout << tmp[n];
	    n++;
    }

    cout << '\n';
	int len = n;
	n = 0;
	int k = 0;
	int f = 0;
	while(n < len && tmp[n] != '\n'){
        a[n] = tmp[n];
        f++;
        n++;
	}
	n++;
	while(n < len){
        sline[k] = tmp[n];
        k++;
        n++;
	}
    sline[k] = '\0';
	n = 0;
	while(n < (len - f)){
	    if(isalpha(sline[n])){
	        for(int j = 0; j < f; j++){
	            if(a[j] == sline[n])
	                a[j] = sline[n+2];
	        }
	    }
	    n++;
	}
    cout << '\n';

	cout << "Вычисление:" << endl;
	Stack s;
	n = f;
	for (int i = 0; i < n; i++){
		if (a[i] == '+')
			s.push(s.pop() + s.pop());
        if (a[i] == '-' && !isdigit(a[i+1]))
            s.push(s.pop() - s.pop());
        if (a[i] == '/')
            s.push(s.pop() / s.pop());
		if (a[i] == '*')
			s.push(s.pop() * s.pop());
		if (a[i-1] != '-' && (a[i] >= '0') && (a[i] <= '9'))
			s.push(0);
        if (a[i-1] == '-' && isdigit(a[i]))
            s.push('0' - a[i]);
		while (a[i-1] != '-' && (a[i] >= '0') && (a[i] <= '9')){
			s.push(10 * s.pop() + (a[i++] - '0'));
		}
	}

	cout << "Результат = " << s.pop() << endl;
	s.destroy();
	return 0;
}