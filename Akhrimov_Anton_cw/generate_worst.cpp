#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {
    int n;
    srand(static_cast<unsigned int>(time(0)));

    cin >> n;
    char buff;
    vector<char> a;
    int m;
    while (n > 0) {
        m = n % 95;
        if (m == 0) m = 1;
        for (int i = m; i >= 0; i--) {
            a.push_back((char)(i + 32));
        }
        n -= m;
    }

    for (int i = 0; i < a.size(); i++)
        cout << a[i];
    cout << endl;
    return 0;

}
