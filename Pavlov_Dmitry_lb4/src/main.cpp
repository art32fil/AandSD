#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>

template<typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vec) {
	out << '[';
	for (int i = 0; i < vec.size(); i++) {
		if (i == vec.size() - 1) {
			out << vec[i];
			break;
		}
		out << vec[i] << ", ";
	}
	out << ']';
	return out;
}

template<typename T>
void sortc(std::vector<T>& vec, std::ofstream& out){
	int size = vec.size();
	int count = 0;
	int step = size;
	while (step > 1) {
		count += 1;
		out << "This is " << count << " iteration of sorting" << '\n';
		step = std::max(1, step/= 1.247f);
		for (int i = 0; i + step < size;++i) {
			if (vec[i]  > vec[i + step] ) {
				out << "We will change this elements: " << vec[i] << "(" << i << ")" << " and " << vec[i + step] << "(" << i + step << ")" << '\n';
				std::swap(vec[i], vec[i + step]);
			}
		}

		out << vec << '\n';
	}

}

void checkStr(std::string& str) {
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i])&&str[i]!=' '&&str[i] != '-') {
			str.erase(i, 1);
			i -= 1;
		}
	}
}
int main() {
	std::string str1;
	std::vector<int> vec;
	std::vector<int> vecToCheck;
	std::ifstream fin("test.txt");
	std::ofstream out("result.txt");
	int value;
    fin>>std::noskipws;
    if(!fin){
        std::cout<<"Can't open this file!";
    }
    std::getline(fin, str1);
	checkStr(str1);
    //std::cout<<str1 << '\n';
	std::stringstream ss(str1);
	while (ss >> value) {
	    vec.push_back(value);
		if (ss.peek() == ' ') {
			ss.ignore();
		}
	}
	vecToCheck = vec;
	sortc(vec, out);
	out << "This is sorted array" << '\n';
    out << vec;
    out << '\n';
	std::sort(vecToCheck.begin(), vecToCheck.end());

	//Checking my Alogrothm with Algorithm in Lib
	std::cout << "Checking my Alogrothm with Algorithm in Lib\n";
    for (int i = 0; i < 100; i+=20) {
        std::cout << "\rCompleted " << i << "%   " << std::flush;
        sleep(1);
    }
    std::cout << "\rDone            " << std::endl;
	if (vec == vecToCheck) {
        std::cout << "They are identical" << std::endl;
	}
	else {
	    std::cout << "Incorrect!" << std::endl;
	}
	return 0;
}
