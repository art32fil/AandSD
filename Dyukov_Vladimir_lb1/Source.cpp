#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void startPrint(const int& depth, const int& value, ofstream* fout = nullptr) {

	if (fout) {

		*fout << depth << ">";
		for (int i = 0; i < depth; i++) *fout << "--";
		*fout << "Start of counting (" << value << ")" << endl;
	}
	else {

		cout << depth << ">";
		for (int i = 0; i < depth; i++) cout << "--";
		cout << "Start of counting (" << value << ")" << endl;
	}
}

void endPrint(const int& depth, const int& value, const int& sum, ofstream* fout = nullptr) {

	if (fout) {

		*fout << depth << ">";
		for (int i = 0; i < depth; i++) *fout << "--";
		*fout << "End of counting (" << value << ") = " << sum << endl;
	}
	else {

		cout << depth << ">";
		for (int i = 0; i < depth; i++) cout << "--";
		cout << "End of counting (" << value << ") = " << sum << endl;
	}
}

int counting(const int& value, const int& depth, ofstream* fout = nullptr) {

	int sum = 0;

	startPrint(depth, value, fout);

	for (int i = 2; i <= value; i++) sum += counting(value / i, depth + 1, fout);

	if (value == 1) sum = 1;

	endPrint(depth, value, sum, fout);

	return sum;
}

int sstoi(string s) {

	int temp = 0;
	int i = 0;
	while (s[i] >= 0x30 && s[i] <= 0x39)
	{
		temp = temp + (s[i] & 0x0F);
		temp = temp * 10;
		i++;
	}
	temp = temp / 10;
	return(temp);
}

int main() {

	int num_of_iter = 0;
	ifstream fin;

	cout << "Enter name of file:" << endl;
	while (1) {

		string fname;
		getline(cin, fname);
		fin.open(fname);
		if (!fin) {

			cout << "Wrong name of file. Please try again:" << endl;
			continue;
		}

		bool flag = false;
		while (!fin.eof()) {

			getline(fin, fname);
			if (fname != "") {

				flag = true;
				num_of_iter++;
			}
		}
		if (flag) break;

		cout << "File is empty. Please try again:" << endl;
		fin.close();
		num_of_iter = 0;
	}

	string* buffer = new string[num_of_iter];
	
	fin.clear();
	fin.seekg(0, fin.beg);

	for (int i = 0; i < num_of_iter; i++) {

		getline(fin, buffer[i]);
		if (buffer[i] == "") i--;
	}

	fin.close();

	ofstream fout("result.txt");

	for (int i = 0; true;) {

		if (i == -1) i = 0;
		if (i == num_of_iter) i = num_of_iter - 1;

		fout << "\nResult of counting number " << sstoi(buffer[i]) << ": " << counting(sstoi(buffer[i]), 1, &fout) << endl << endl;
		cout << "\nResult of counting number " << sstoi(buffer[i]) << ": " << counting(sstoi(buffer[i]), 1) << endl << endl;

		cout << "Do you want to see next or previous counting or to escape? 'n/p/e'" << endl;

		char sign = '0';

		while (sign != '1') {

			cin >> sign;
			switch (sign) {

			case 'n':
				i++;
				sign = '1';
				break;
			case 'p':
				i--;
				sign = '1';
				break;
			case 'e':
				delete[] buffer;
				fout.close();
				return 0;
			default:
				cout << "Wrong symbol. Please try again:" << endl;
			}
		}
	}
}