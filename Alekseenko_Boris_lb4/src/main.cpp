#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void shakersort(int* left, int* right) {
	int sz = right - left;
	if (sz <= 1) return;
	bool b = true;
	int* beg = left - 1;
	int* end = right - 1;
	while (b) {
		b = false;
		beg++;
		for (int* i = beg; i < end; i++) {
			if (*i > * (i + 1)) {
				cout << "swap: " << *i << " & " << *(i + 1) << endl;
				swap(*i, *(i + 1));
				b = true;
			}
		}
		if (!b) break;
		end--;
		cout << "Move another way" << endl;
		for (int* i = end; i > beg; i--) {
			if (*i < *(i - 1)) {
				cout << "swap: " << *i << " & " << *(i + 1) << endl;
				swap(*i, *(i - 1));
				b = true;
			}
		}
	}
}

int main() {
	int* data;
	string name_;
	ifstream f;
	cout << "Enter a file name.\n";
	cin >> name_;
	f.open(name_);
	if (!f.is_open()) {
		cout << "Invalid file name.\n";
		return 1;
	}
	while (!f.eof()) {
		int size;
		f >> size;
		data = new int[size];

		for (int i = 0; i < size; i++) {
			f >> data[i];
		}
		cout << "Non sorted array: " << endl;
		for (int i = 0; i < size; i++)
			cout << data[i] << " ";
		cout << endl;
		shakersort(&data[0], &data[size]);

		cout << "Sorted array:\n";
		for (int i = 0; i < size; i++)
			cout << data[i] << " ";
		delete[] data;
	}
	return 0;
}