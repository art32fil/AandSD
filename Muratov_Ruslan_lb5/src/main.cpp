#include <iostream>
#include <vector>
#include <string>

#include "avltree.h"

enum InputSource {
  Console, File
};

int main() {
  int is;
  AvlTree<int> avlt;
  int elem;

  while (true) {
    std::cout << "Choose source of data (0 - console, 1 - file):" << std::endl;
    std::cin >> is;

    if (is == Console) {
      int num;
      std::cout << "Enter number of elements: ";
      std::cin >> num;
      std::cout << "Enter elements:\n";
      for (int i = 0; i < num; ++i) {
        std::cin >> elem;
        avlt.insert(elem);
      }
    } else if (is == File) {
      std::cout << "Enter file name: " << std::endl;
      std::string fileName;
      std::cin >> fileName;
      std::ifstream inFile(fileName);
      if (!inFile.is_open()) {
        std::cerr << "Cannot open a file!" << std::endl;
        return 1;
      }
      inFile >> elem;
      while (!inFile.eof()) {
        avlt.insert(elem);
        inFile >> elem;
      }
    } else {
      std::cerr << "Invalid input!" << std::endl;
      continue;
    }
    break;
  }

//  int choice;
//  bool flag = true;
//  while (flag) {
//    std::cout << "What do you want to do:\n1) Insert\n2) Remove\n3) Print\n4) Exit" << std::endl;
//    std::cin >> choice;
//    switch (choice) {
//      case 1:
//        std::cout << "Enter a element:" << std::endl;
//        std::cin >> elem;
//        avlt.insert(elem);
//        break;
//      case 2:
//        std::cout << "Enter a element:" << std::endl;
//        std::cin >> elem;
//        avlt.remove(elem);
//        break;
//      case 3:
//        avlt.printToConsole();
//        break;
//      case 4:
//        flag = false;
//        break;
//      default:
//        std::cout << "Incorrect input!" << std::endl;
//        break;
//    }
//  }

  std::ofstream outDotFile("output.gv");
  std::ofstream outTextFile("infix_print.txt");

  avlt.printDot(outDotFile);
  avlt.printInfix(outTextFile);

  return 0;
}
