#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>

#define TYPE int

template < typename T >
void PrintVec(const std::vector<T>& v){
    for (int x : v){
        std::cout << x << " ";
    }
    std::cout << '\n';
}

template < typename T >
void SortVec(int& n, std::vector<T>& v){
    int i, j, step;
    int tmp;
    int counter = 1;
    for (step = n / 2; step > 0; step /= 2){
        for (i = step; i < n; i++) {
            tmp = v[i];
            for (j = i; j >= step; j -= step) {
                if (tmp < v[j - step]) {
                    v[j] = v[j - step];
                }
                else break;
            }
            v[j] = tmp;
            std::cout << "шаг " << counter << ": ";
            PrintVec(v);
            counter++;
        }
    }
}

bool isCorrect(const std::string str){
    size_t i = 0;
    if(str.at(0) == '-' && i != str.size()-1){
        i++;
    }
    while(i < str.size()){
        if(isdigit(str.at(i))){
            i++;
        }
        else {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<TYPE> v;
    std::string x;
    std::ifstream fin("input.txt");
    if (!fin){
        std::cout << "Не удаётся открыть файл на чтение!\n";
        return 1;
    }
    std::string tmp;
    getline(fin , tmp);
    if(tmp.length() < 1) {
        std::cout << "Введена неверная строка.\n";
        return 1;
    }
    std::cout << "Введена строка: " << tmp << " \n";
    std::istringstream stream(tmp);
    std::cin.rdbuf(stream.rdbuf());
    int i = 0;
    do {
        std::cin >> x;
        if(isCorrect(x)){
            v.push_back(atoi(x.c_str()));
            i++;
        }
    } while((tmp.find(x) + x.length()) != tmp.length());
    if(i == 0){
        std::cout << "Не удалось отсортировать данное выражение\n";
        return 0;
    }
    SortVec(i, v);

    return 0;
}