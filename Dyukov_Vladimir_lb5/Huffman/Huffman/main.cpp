#include <fstream>
#include "TreeList.h"
#include <conio.h>

bool get_enter(std::string str) {

	std::cout << str;

	while (1) {

		unsigned char key = _getch();
		if (key == 224) key = _getch();
		if (key == 13) return true;
		else return false;
	}
}

//

int main() {

	std::ifstream in;
	std::ofstream out;
	sf::Font font;
	font.loadFromFile("C:\\GameRes\\fonts\\comic.ttf");
	sf::RenderWindow window;
	
	while (1) {

		system("cls");
		std::string str;
		std::cout << "Enter the name of the file you want to encode:\n\n";
		std::getline(std::cin, str);
		in.open(str);

		std::cout << "Enter the name of the file to which you want to save the code:\n\n";
		std::getline(std::cin, str);
		out.open(str);

		TreeList huffman;

		window.create(sf::VideoMode(1260, 900), "title");
		while (window.isOpen()) {

			sf::Event event;

			while (window.pollEvent(event)) {

				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {

					if (in.eof()) continue;
					char code;
					in >> code;
					huffman.add(code, out);
				}
			}

			window.clear(sf::Color(160, 200, 255, 255));
			huffman.drawTree(window, font, 1, *huffman.list.begin(), 0);
			huffman.drawList(window, font);
			window.display();
		}

		in.close();
		out.close();

		if (get_enter("Press 'enter' to exit.\n\n")) break;
	}

	return 0;
}