#include <iostream>
#include <string>
#include <fstream>
/*вещественное_число::= целое_число . целое_без_знака |
целое_число.целое_без_знакаЕцелое число |/
целое_числоЕцелое_число
целое_без_знака::=цифра | цифра целое_без_знака
целое_число::=целое_без_знака | + целое_без_знака | -целое_без_знака
*/
void printDepth(int depth)
{
    for (int i = 0; i < depth; i++)
        std::cout<<" ";
    std::cout << depth <<std::endl;
}
bool integer(std::string& str, int* count, int* depth)
{
    if (*depth == 0) std::cout<< "Начало рекурсии"<<std::endl;
    *depth += 1;
    printDepth(*depth);

        if (*count >= str.length() - 1)
        {
            bool err = (char)str[*count] > (char)'0' && str[*count] < (char)'9';
            std::cout << "Конец рекурсии"<< std::endl;
            return err;
        }

    if ((char)str[*count] == '.' || (char)str[*count] == 'E')
    {
        if (*count != 0 && ((char)str[*count - 1] != '.' && (char)str[*count - 1] != 'E'))
        {
            std::cout << "Конец рекурсии"<< std::endl;
            return true;
        }
        else
        {
            std::cout << "Конец рекурсии"<< std::endl;
            return false;
        }
    }
    bool err = (char)str[*count] > (char)'0' && str[*count] < (char)'9';
    *count += 1;
    if (err == false) std::cout << "Конец рекурсии"<< std::endl;
    return err && integer(str, count,depth);
}
bool cleverInteger(std::string& str, int* count, int* depth)
{
    if ((char)str[*count] == '-' || (char)str[*count] == '+')
        *count += 1;
    return integer(str, count, depth);

}
bool realNumber(std::string& str, int* count)
{
    bool x;
    int depth = 0;
    x = cleverInteger(str, count, &depth);
    if (str[*count] == '.')
    {
        depth = 0;
        *count += 1;
        x = x && integer(str, count, &depth);
    }
    if (str[*count] == 'E' && x)
    {
        depth = 0;
        *count += 1;

        x = x && cleverInteger(str, count, &depth);
    }
    return x;
}


int main()
{
    using namespace std;
    setlocale(LC_ALL, "Russian");
    ifstream fin;
    string str;
    fin.open("test.txt");
    if (!fin.is_open())
    {
        std::cout << "Ошибка открытия файла";
        return 0;
    }
    getline(fin, str);
    fin.close();
    if (str.length() == 0) { cout << "error:Пустая строка"; return 0; }
    int lin = 0;
    if (realNumber(str, &lin) && lin == (str.length() - 1))
        cout << ("Это вещественное число");
    else cout << "Это не вещественное число";
    return 0;
}