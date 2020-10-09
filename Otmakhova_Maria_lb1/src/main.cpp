#include <iostream>
#include <vector>

using namespace std;

vector<int> concat(vector<int> a, vector<int> b) {
    vector<int> c;
    for (int i = 0; i < a.size(); i++) {
        c.push_back(a[i]);
    }

    for (int i = 0; i < b.size(); i++) {
        c.push_back(b[i]);
    }
    return c;
}

vector<int> print_vector(vector<int> a) {
    for ( int i = 0; i < a.size(); i++) {
        cout << a[i] << ' ';
    }
}

vector<int> phi(vector<int> alpha, int depth) {
    for (int i = 0; i < depth; i++) {
        cout << " ";
    }
    cout << "Phi called for vector: ";
    print_vector(alpha);
    cout << endl;

    if (alpha.size() <= 2) {
        return alpha;
    } else if (alpha.size() % 2 == 0) {
        vector<int> b;
        for (int i = 0; i < alpha.size() / 2; i++) {
            b.push_back(alpha[i]);
        }

        vector<int> y;
        for (int i = alpha.size() / 2; i < alpha.size(); i++) {
            y.push_back(alpha[i]);
        }

        return concat(phi(b, depth + 1), phi(y, depth + 1));
    } else {
        vector<int> b;
        for (int i = 0; i < alpha.size() / 2; i++) {
            b.push_back(alpha[i]);
        }

        vector<int> a = {alpha[alpha.size() / 2]};

        vector<int> y;
        for (int i = alpha.size() / 2 + 1; i < alpha.size(); i++) {
            y.push_back(alpha[i]);
        }

        return concat(
                phi(concat(b, a), depth + 1),
                phi(concat(a, y), depth + 1)
        );
    }
}


int main() {

    int n;
    cin >> n;

    vector<int> alpha;
    alpha.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> alpha[i];
    }

    vector<int> res = phi(alpha, 1);

    cout << "\nResult is: ";
    print_vector(res);

    return 0;
}
