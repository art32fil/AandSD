#include <iostream>
#include <fstream>
using namespace std;
#define ull unsigned long long


ull binomical(ull m, ull n, int& depth) {
    depth += 1;
    if ((m == 0 && n > 0) || (m == n && n >= 0)) return 1;
    if (m > n && n >= 0) return 0;
    return binomical(m - 1, n - 1, depth) + binomical(m, n - 1, depth);
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
    ull n;
    ull m;
    string str;
    while(1) {
        fin >> n >> m ;
        if (fin.eof()){
            break;
        }
        int depth = 0;
        fout << endl << binomical(n, m, depth) << endl;
        fout << "Depth: " << depth << endl;
   
    }
    fin.close();
    fout.close();
    return 0;
}