#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

long long CNT = 0;

void sift_down(int* arr, int n, int start, int end) {
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
			CNT++;
		}
		else {
			break;
		}
	}
}

int find_max(int* arr,int cur, int n, int len) {
	if (cur * n + 1 >= len) {
		return cur;
	}

	int max = cur * n + 1;

	for (int i = 2; i <= n; i++) {
		if (cur * n + i > len) {
			break;
		}
		if (arr[cur * n + i] > arr[max]) {
			max = cur * n + i;
		}
	}
	return find_max(arr, max, n, len);
}

void sift_up(int* arr, int root, int n, int len) {
	if (root * n + 1 >= len) {
		return;
	}

	int cur = find_max(arr, root, n,len);

	while (arr[cur] < arr[root]) {
		cur = (cur - 1) / n;
	}
	int tmp = arr[cur];

	arr[cur] = arr[root];

	cur = (cur - 1) / n;

	while (cur > root) {
		int tmp2 = arr[cur];
		arr[cur] = tmp;
		tmp = tmp2;
		cur = (cur - 1) / n;
		CNT++;
	}

	arr[root] = tmp;
}

void sort_down(int* arr, int start, int end, int n) {
	for (int i = end; i >= start; i--) {
		sift_down(arr, n, i, end);
	}

	for (int i = 0; i < end + 1; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;

	int temp = end;

	for (int i = 0; i <= end; i++) {
		int cur = arr[0];
		arr[0] = arr[temp];
		arr[temp] = cur;
		for (int i = 0; i < end + 1; i++) {
			cout << arr[i] << ' ';
		}
		cout << endl;
		sift_down(arr, n, 0, temp - 1);
		temp--;
	}
	cout << "result: ";
	for (int i = 0; i < end + 1; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;

}


int main() {
	int* data;
	int n;
	int size;
	cout << "enter n: " << endl;
	cin >> n;
	cout << "enter array length: " << endl;
	cin >> size;

	data = new int[size];
	char s;
	char c;

	cout << "which case do you want to handle? " << endl;
	cout << "a - average/ w - worst" << endl;
	cin >> s;
	cout << "u - up/ d - down" << endl;
	cin >> c;
	if (s == 'a') {
		for (int i = 0; i < size; i++) {
			data[i] = rand() % 200;
		}
		cout << "input data: ";
		for (int i = 0; i < size; i++) {
			cout << data[i] << ' ';
		}
		cout << endl;

		if (c == 'd') {
			sort_down(data, 0, size - 1, n);
		}
		else if (c == 'u') {
			for (int i = size - 1; i >= 0; i--) {
				sift_up(data, i, n, size);
			}

			int* ans;
			ans = new int[size];

			for (int i = 0; i < size; i++) {
				ans[size - (i + 1)] = data[0];
				data[0] = data[size - (i + 1)];
				CNT++;
				sift_up(data, 0, n, size - (i + 1));
			}
			cout << "result: ";
			for (int i = 0; i < size; i++) {
				cout << ans[i] << ' ';
			}
			delete[] ans;
		}
		else {
			cout << "incorrect data entered" << endl;
			return 0;
		}
	 }
	else if (s == 'w') {
		 for (int i = 0; i < size; i++) {
			 data[i] = i + 1;
		 }
		 cout << "input data: ";
		 for (int i = 0; i < size; i++) {
			 cout << data[i] << ' ';
		 }
		 cout << endl;

		 if (c == 'd') {
		 	 sort_down(data, 0, size - 1, n);
		 }
		 else if (c == 'u') {
			 for (int i = size - 1; i >= 0; i--) {
				 sift_up(data ,i, n, size);
			 }

			 int* ans;
			 ans = new int[size];

			 for (int i = 0; i < size; i++) {
				 ans[size - (i + 1)] = data[0];
				 data[0] = data[size - (i + 1)];
				 CNT++;
				 sift_up(data, 0,n, size - (i + 1));
			 }
			 cout << "result: ";
			 for (int i = 0; i < size; i++) {
				 cout << ans[i] << ' ';
			 }
			 delete[] ans;
		 }
		 else {
			 cout << "incorrect data entered" << endl;
			 return 0;
		 }
	 }
	 else {
		cout << "incorrect data entered" << endl;
		return 0;
	 }

	cout << endl;
	cout << "num " << CNT << endl;

	delete[] data;

	return 0;
}
