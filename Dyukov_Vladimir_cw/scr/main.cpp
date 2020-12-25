#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "TreeList.h"

int button_get(std::string* buttons, int size) {

	int count = 0;

	while (1) {

		std::cout << '\r';

		for (int i = 0; i < size; i++) {

			if (i == count) std::cout << '<' << buttons[i] << '>' << '\t';
			else std::cout << ' ' << buttons[i] << ' ' << '\t';
		}

		unsigned char key = _getch();
		if (key == 224) key = _getch();

		switch (key) {
		case 75:
			count--;
			break;
		case 77:
			count++;
			break;
		case 13:
			return count + 1;
		case 27:
			return 0;
		}
		if (count > size - 1) count = 0;
		if (count < 0) count = size - 1;
	}
}

//

int main() {

	std::ifstream in;
	std::ofstream out;
	TreeList* huffman;
	std::string str;
	std::string empty[] = { "" };
	std::string coding[] = { "Encode", "Decode" };

	while (1) {

		huffman = nullptr;

		system("cls");
		std::cout << "Choose what you want to do:\n\n";
		int ch = button_get(coding, 2);

		if (ch == 1) huffman = new EncodeTreeList;
		if (ch == 2) huffman = new DecodeTreeList;

		if (huffman) {

			std::cout << "\n\nEnter the source data file:\n\n";
			std::cin >> str;
			in.open(str);
		}

		if (in.is_open()) {

			std::cout << "\n\nEnter the file where the result will be saved:\n\n";
			std::cin >> str;
			out.open(str);
		}

		while (huffman && in.is_open() && out.is_open()) {

			system("cls");
			huffman->drawTree();
			button_get(empty, 0);
			if (!huffman->add(in, out)) break;
		}

		if (huffman) delete huffman;
		if (in.is_open()) in.close();
		if (out.is_open()) out.close();

		std::cout << "\n\nPress 'Esc' to exit / 'Enter' to continue.\n";
		if (!button_get(empty, 0)) break;
	}

	return 0;
}