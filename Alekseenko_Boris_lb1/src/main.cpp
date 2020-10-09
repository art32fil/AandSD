#include <iostream>
#include <fstream>
using namespace std;
#define ull unsigned long long


ull bci(ull m, int n, int depth)
{
    if ((m == 0 && n > 0) || (m == n && n >= 0)) return 1;
    if (m > n && n >= 0) return 0;
    return bci(m - 1, n - 1, depth + 1) + bci(m, n - 1, depth + 1);
}

int main()
{
    string fname;
    cout << "Enter input file's name: ";
    cin >> fname;
    ifstream fin(fname);
    if (!fin.is_open()) {
        cout << "ERROR";    
        return 0;
    }
    ofstream fout("out.txt");
    ull n, m;
    fin >> n >> m;
    int depth;
    fout << endl << bci(n, m, depth) << endl;
    fout << "Depth: " << depth;
    fin.close();
    fout.close();
    return 0;
}