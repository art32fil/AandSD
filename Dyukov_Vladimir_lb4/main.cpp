#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>

#define HEAD "Демонстрация работы функции сортировки пузырьком 'четно-нечетно'\nДюков Владимир гр. 9303\n\n"
#define FICO "Выберете способ ввода массива:\n\n"
#define COIN "Введите массив, которые надо отсортировать:\n\n"
#define FIIN "Введите имя файла:\n\n"
#define FIER "Ошибка ввода файла\n\n"

template<typename T>
void even_print(std::vector<T> data, std::ostream& out) {

    int n = (int)data.size();
    for (int i = 0; i < n; i++) {

        if ((i + 1) % 2 && i != n - 1) out << data[i] << "--";
        else out << data[i] << "  ";
    }
}

template<typename T>
void odd_print(std::vector<T> data, std::ostream& out) {

    int n = (int)data.size();
    for (int i = 0; i < n; i++) {

        if (i % 2 && i != n - 1) out << data[i] << "--";
        else out << data[i] << "  ";
    }
}

template<typename T>
std::vector<T> even_odd_sort(std::vector<T> data, std::ostream& out) {

    int n = (int)data.size();
    bool isSorted = 0;
    int k = 1;

    while (!isSorted) {
        isSorted = 1;

        out << "\nНечётное " << k << ":\t";
        odd_print(data, out);
        
        for (int i = 1; i < n - 1; i += 2) {
            if (data[i] > data[i + 1]) {
                T temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                isSorted = 0;
            }
        }

        out << "\n\t\t";
        odd_print(data, out);
        
        out << "\n\nЧётное   " << k << ":\t";
        even_print(data, out);

        for (int i = 0; i < n - 1; i += 2) {
            if (data[i] > data[i + 1]) {
                T temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                isSorted = 0;
            }
        }

        out << "\n\t\t";
        even_print(data, out);
        out << '\n';
        k++;
    }
    return data;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> data) {

    int n = (int)data.size();
    for (int i = 0; i < n; i++) out << data[i] << " ";
    return out;
}

int button_get(std::string* buttons, int size) {

    int count = 0;

    while (1) {

        std::cout << '\r';

        for (int i = 0; i < size; i++) {
            
            if (i == count) std::cout << '<' << buttons[i] << '>' << '\t';
            else std::cout << ' ' << buttons[i] << ' ' << '\t';
        }

        unsigned char key = _getch();
        if (key == 224) key = _getch();

        switch (key) {
        case 75:
            count--;
            break;
        case 77:
            count++;
            break;
        case 13:
            return count + 1;
        case 27:
            return 0;
        }
        if (count > size - 1) count = 0;
        if (count < 0) count = size - 1;
    }
}

typedef char vect_type;

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string ficoget[2] = { "Консоль", "Файл" };
    std::ofstream outfile("result.txt");

    while (1) {

        std::stringstream inputText("");
        int test_num = 0;

        system("cls");
        std::cout << HEAD;
        std::cout << FICO;

        int check_1 = button_get(ficoget, 2);
        system("cls");
        if (!check_1) break;
        if (check_1 == 1) {

            std::cout << HEAD;
            std::cout << COIN;
            std::string str;
            std::getline(std::cin, str);
            inputText << str;
            test_num++;
        }
        if (check_1 == 2) {

            std::cout << HEAD;
            std::cout << FIIN;
            std::string name;
            std::cin >> name;
            std::ifstream file(name);
            if (!file.fail()) {

                while (!file.eof()) {

                    std::getline(file, name);
                    inputText << name << '\n';
                    test_num++;
                }
                file.close();
            }
            else {

                std::cout << '\n' << FIER;
                system("pause");
                continue;
            }
        }

        inputText.seekg(0, inputText.beg);

        for (int i = 0; i < test_num; i++) {

            std::stringstream inputLine;
            std::vector<vect_type> arr;
            std::string str;
            std::getline(inputText, str);
            inputLine << str;

            while (!inputLine.eof()) {

                vect_type var;
                inputLine >> var;
                arr.push_back(var);
            }

            system("cls");
            std::cout << HEAD;
            std::cout << "Исходный массив " << i + 1 << ":\n" << arr << "\n";
            std::cout << "\nРезультат:\n" << even_odd_sort(arr, std::cout) << "\n\n";
            if (outfile.is_open()) outfile << "Исходный массив " << i + 1 << ":\n" << arr << "\n\n\n";
            if (outfile.is_open()) outfile << "\nРезультат:\n" << even_odd_sort(arr, outfile) << "\n\n\n";
            system("pause");
        }
    }

    if (outfile.is_open()) outfile.close();

    return 0;
}