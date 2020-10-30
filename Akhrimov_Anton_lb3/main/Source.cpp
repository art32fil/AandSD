
#include <fstream>
#include <string>
#include <iostream>

using namespace std;


template <typename T>
class Node
{
public:
	T data;
	int LSub = 0;
	int RSub = 0;
};

template <typename U>
class BinTree
{
public:
	//BinTree() {};
	~BinTree() {
		delete[] arr;
	}
	void resize(int newSize) {
		Node<U>* newArr = new Node<U>[newSize];
		memcpy(newArr, arr, sizeArray * sizeof(Node<U>));
		sizeArray = newSize;
		delete[] arr;
		arr = newArr;
	}
	void read(ifstream& in) {
		int index = 0;
		char buf;
		in.get(buf);
		if (buf == '(')
			root = readBinTree(in, buf, index);
	}


	int readBinTree(ifstream& in,char prev, int& index) {
		if (prev != '(')
			return -1;
		char buf;
		resize(sizeArray + 1);
		
		int currentIndex = index;
		in >> arr[currentIndex].data;
		in.get(buf);
		if (buf == '(') {
			arr[currentIndex].LSub = readBinTree(in, buf, index += 1);
			in.get(buf);
			if (buf == '(') {
				arr[currentIndex].RSub = readBinTree(in, buf, index += 1);
			}
		}
		else if (buf == '^') {
			in.get(buf);
			if(buf == '(')
				arr[currentIndex].RSub = readBinTree(in, buf, index += 1);
		}
		if (buf == ')')
			return currentIndex;
		in.get(buf);
		if (buf != ')'){ cerr << "Wrong tree!\n"; exit(1); }

		return currentIndex;	
	}
	void read() {
		int index = 0;
		char buf;
		cin.get(buf);
		if (buf == '(')
			root = readBinTree(buf, index);
	}


	int readBinTree(char prev, int& index) {
		if (prev != '(')
			return -1;
		char buf;
		resize(sizeArray + 1);
		int currentIndex = index;
		cin >> arr[currentIndex].data;
		cin.get(buf);
		if (buf == '(') {
			arr[currentIndex].LSub = readBinTree(buf, index += 1);
			cin.get(buf);
			if (buf == '(')
				arr[currentIndex].RSub = readBinTree(buf, index += 1);
		}
		else if (buf == '^') {
			cin.get(buf);
			if (buf == '(')
				arr[currentIndex].RSub = readBinTree(buf, index += 1);
		}
		if (buf == ')')
			return currentIndex;
		cin.get(buf);
		if (buf != ')') { cerr << "Wrong tree!\n"; exit(1); }

		return currentIndex;

	}

	void write() {
		if (sizeArray == 0) {
			cout << "()";
			return;
		}
		writeBinTree(root);
		cout << endl;
	}

	void writeBinTree(int index) {
		cout << "(" << arr[index].data;
		if (arr[index].LSub){
			writeBinTree(arr[index].LSub);
			if (arr[index].RSub)
				writeBinTree(arr[index].RSub);
		}
		else if (arr[index].RSub) {
			cout << "^";
			writeBinTree(arr[index].RSub);
		}
		cout << ")";
	}

	void view() {
		view(root, 1);
	}

	void view(const int& index, const int& level) {
		for (int i = 0; i < level; i++)
			cout << "  ";
		cout << arr[index].data << endl;
		if (arr[index].LSub)
			view(arr[index].LSub, level + 1);
		if (arr[index].RSub)
			view(arr[index].RSub, level + 1);
	}

	void writeLists() {
		int index = root;
		writeLists(index, 1);
	}

	void writeLists(int index, int k) {
		if (arr[index].LSub)
			writeLists(arr[index].LSub, k + 1);
		if (arr[index].RSub)
			writeLists(arr[index].RSub, k + 1);
		if (arr[index].LSub == 0 && arr[index].RSub == 0)
			cout << "level = " << k << " leaf data = " << arr[index].data << endl;
	}

	void numberNodes(const int& n) {
		int sum = 0;
		numberNodes(n, root, 1, sum);
		cout << "Number of nodes at level " << n << " = " << sum << endl;
	}

	void numberNodes(const int& n, int index, int currentLvl, int& sum) {
		cout << "Level = " << currentLvl << " data = " << arr[index].data << " sum = " << sum << endl;
		if (currentLvl == n) {
			sum++;
			return;
		}
		if (arr[index].LSub) 
			numberNodes(n, arr[index].LSub, currentLvl + 1, sum);
		if (arr[index].RSub)
			numberNodes(n, arr[index].RSub, currentLvl + 1, sum);
	}

private:
	Node<U>* arr;
	int sizeArray = 0;
	int root;
	
};


int main() {
	BinTree<char> binT;
	char buf;
	string s;
	ifstream f;
	cout << "Read from file?[y/n]\n";
	cin >> buf;
	switch(buf){
	case 'y':
		cout << "Enter a file name.\n";
		cin >> s;
		f.open(s);
		if (!f.is_open())
			return 1;
		binT.read(f);
		binT.write();
		f.close();
	case 'n':
		binT.read();
	}

	binT.view();
	cout << "Leafs data:\n";
	binT.writeLists();
	cout << "Enter a level\n";
	int n;
	cin >> n;
	binT.numberNodes(n);

}



