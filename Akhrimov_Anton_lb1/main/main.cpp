#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void getValues(int&a, int&b) {
	while (true) {
		cin >> a >> b;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Invalid number. Try again.\n";
		}
		else {
			cin.ignore(32767, '\n');
			return;
		}
	}
}



class City
{
public:
	int number;
	vector<int> roadsToCitys;
	bool isMarked = false;

	bool checkRoad(int where) {
		for (int i = 0; i < roadsToCitys.size(); i++)
			if (roadsToCitys[i] == where)
				return true;
		return false;
	}
};

class ArrayOfCity
{
public:
	vector<City> data;
	int total = 0;
	int flag = 0;
	int numberRec = 0;
	ofstream out;

	ArrayOfCity(string filename = "output.txt") {
		out.open(filename);
	}

	~ArrayOfCity() {
		out.close();
	}

	void clearMark() {
		for (int i = 0; i < total; i++)
			data[i].isMarked = false;
		flag = 0;
		numberRec = 0;
	}

	void outputRecursion(int k, int from, string extra = "") {
		for (int i = 0; i < k; i++) {
			cout << " ";
			out << " ";
		}
		cout << from << " " + extra << endl;
		out << from << " " + extra << endl;
	}

	bool checkCity(int city) {
		for (int i = 0; i < total; i++) 
			if (data[i].number == city)
				return true;
		return false;
	}

	void addCity(int city) {
		if (!checkCity(city)) {
			City c;
			c.number = city;
			data.push_back(c);
			total += 1;
		}
	}

	City& getCity(int city) {
		for (int i = 0; i < total; i++)
			if (data[i].number == city)
				return data[i];
	}

	bool checkRoads(int from, int where) {
		int k = (numberRec += 1);
		string s = "Start function checkRoads(" + to_string(from) + ", " + to_string(where) + ")";
		outputRecursion(k, from, s);
		City& c = getCity(from);
		c.isMarked = true;
		if (c.checkRoad(where)) {
			s = "Finish function checkRoads(" + to_string(from) + ", " + to_string(where) + ")";
			outputRecursion(k, from, s);
			return true;
		}
		for (int i = 0; i < c.roadsToCitys.size(); i++) {
			if (!getCity(c.roadsToCitys[i]).isMarked) {
				if (checkRoads(getCity(c.roadsToCitys[i]).number, where))
					flag = 1;
			}
		}
	    s = "Finish function checkRoads(" + to_string(from) + ", " + to_string(where) + ")";
		outputRecursion(k, from, s);
		return flag;
	}
	
};


int main() {
	ArrayOfCity arr;
	int numberRoads, n;
	string filename;

	

	while (true) {
		cout << "Enter filename.\n";
		cin >> filename;
		ifstream in(filename);
		if (in.is_open()) {
			in >> n;
			cout << "Number city " << n << endl;
			arr.out << "Number city " << n << endl;
			in >> numberRoads;
			int buf_i, buf_j;
			for (int i = 0; i < numberRoads; i++) {
				in >> buf_i >> buf_j;
				cout << buf_i << " " << buf_j << endl;
				arr.out << buf_i << " " << buf_j << endl;
				arr.addCity(buf_i);
				arr.getCity(buf_i).roadsToCitys.push_back(buf_j);
				arr.addCity(buf_j);
				arr.getCity(buf_j).roadsToCitys.push_back(buf_i);
			}
			in.close();
			break;
		}
		else {
			cout << "Invalid filename. Try again.\n";
		}
	}
	


	char s;
	int flag = 1;

	while (flag) {
		cout << "Continue? y/n\n";
		cin >> s;
		switch (s)
		{
		case 'y':
			break;
		case 'n':
			flag = 0;
			break;
		}
		if (!flag) break;
		int from, where;
		cout << "Enter 2 citys.\n";
		getValues(from, where);
		if (arr.checkRoads(from, where)) {
			cout << "Road exist.\n";
			arr.out << "Road exist.\n";
		}
		else {
			cout << "Road don't exist.\n";
			arr.out << "Road don't exist.\n";
		}
		arr.clearMark();
	}
	return 0;
}
