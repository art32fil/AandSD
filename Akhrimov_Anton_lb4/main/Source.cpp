#include <iostream>
#include <fstream>
#include <string>


using namespace std;

template <typename T>
int binSearch(T* data, T el, int l, int r) {
	int m = (l + r) / 2;
	while (l < r - 1) {
		int middle = (l + r) / 2;
		if (el > data[middle]) {
			l = middle;
		}
		else {
			r = middle;
		}
	}
	if (l < m)
		return l;
	else
		return r;
}

template<typename T>
void sort(T*& data, size_t size){
	T* copy = new T[size];
	int m = (size - 1) / 2;
	int k;
	int l = m;
	int r = m;
	copy[m] = data[0];
	cout << copy[m] << endl;
	for (int i = 1; i < size; i++) {
		k = binSearch<T>(copy, data[i], l - 1 , r + 1);
		if ((k - l) <= (r - k)) {
			for (int j = l - 1; j < k; j++)
				copy[j] = copy[j + 1];
			l -= 1;
			copy[k] = data[i];
		}
		else if (r == (size - 1)) {
			for (int j = l - 1; j < k - 1; j++)
				copy[j] = copy[j + 1];
			l -= 1;
			copy[k - 1] = data[i];
		}
		else {
			for (int j = r + 1; j > k; j--)
				copy[j] = copy[j - 1];
			r += 1;
			copy[k] = data[i];
		}
		
		for (int i = l; i <= r; i++)
			cout << copy[i] << " ";
		cout << endl;
	}
	delete[] data;
	data = copy;
}


int main() {
	int* data;
	string filename;
	ifstream f;
	cout << "Enter a file name.\n";
	cin >> filename;
	f.open(filename);
	if (!f.is_open()) {
		cout << "Invalid file name.\n";
		return 1;
	}
	int size;
	f >> size;
	data = new int[size];
	for (int i = 0; i < size; i++) {
		f >> data[i];
	}
	sort<int>(data, size);
	cout << "Sorted array:\n";
	for (int i = 0; i < size; i++)
		cout << data[i] << " ";
	delete[] data;
	return 0;
}