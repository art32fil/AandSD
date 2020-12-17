#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    int n;
    cin >> n;
    char buff;
    vector<char> a;
    for (int i = 0; i < n; i++) {
        buff = (char)rand() % 122;
        while (buff < 62 || buff > 122) {
            buff = (char)rand() % 122;
            }
            a.push_back(buff);
        }
    for (int i = 0; i < a.size(); i++)
        cout << a[i];
    cout << endl;
    return 0;

}
