#include <iostream>
#include <fstream>

using namespace std;

bool checker_(int* arr, int n, int i, int size) {
	for (int j = 1; j <= n; j++) {
		if ((n * i + j) > size) {
			continue;
		}
		else {
			if (arr[i] >= arr[n * i + j]) {
				bool cur = checker_(arr, n, n * i + j, size);
				if (!cur) {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}
}
void heap_sift(int* arr, int n, int start, int end) {
	int root = start;

	while (true) {
		int child = root * n + 1;
		if (child > end) {
			break;
		}

		int max = child;
		for (int i = 2; i < n + 1; i++) {
			int current = root * n + i;
			if (current > end) {
				break;
			}
			if (arr[current] > arr[max]) {
				max = current;
			}
		}
		if (arr[root] < arr[max]) {
			int cur = arr[root];
			arr[root] = arr[max];
			arr[max] = cur;
			root = max;
		}
		else {
			break;
		}
	}
}

void heap_trans(int* arr,int start, int end, int n) {
	for (int i = end; i >= start; i--) {
		heap_sift(arr, n, i, end);
	}
}

int main() {
	int* data;
	int n;
	int x;
	int size;
	string input_file;
	ifstream f;
	cout << "Enter a file name.\n";
	cin >> input_file;
	f.open(input_file);
	if (!f.is_open()) {
		cout << "Invalid file name.\n";
		return 1;
	}

	f >> n;
	f >> x;
	f >> size;
	data = new int[size];
	for (int i = 0; i < size; i++) {
		f >> data[i];
	}

	if (!(checker_(data, n, 0, size))) {
		cout << "it's not a heap";
		return 0;
	}
	else {
		if (x > data[0]) {
			data[0] = x;
			for (int i = 0; i < size; i++) {
				cout << data[i] << ' ';
			}
			return 0;
		}
		else {
			data[0] = x;
			heap_trans(data, 0, size - 1, n);
			for (int i = 0; i < size; i++) {
				cout << data[i] << ' ';
			}
		}
	}
	return 0;
}
