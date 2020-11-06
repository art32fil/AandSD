#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

void printFile(const std::string& fileName, std::ostream& os) {
  std::fstream file(fileName, std::ios_base::in);
  if (!file.is_open()) {
    os << "Can't open the file with name: " << fileName << std::endl;
    return;
  }
  char c;
  c = file.get();
  while (!file.eof()) {
    if (c != '\n')
      os << c;
    c = file.get();
  }
  os << std::endl;
  file.close();
}

bool isSeriesEnd(std::fstream& file) {
  auto pos = file.tellg();
  char x;
  file >> x;
  if (x == '|') {
    file.seekg(1, std::ios_base::cur);
    return true;
  } else {
    file.seekg(pos);
    return false;
  }
}

template<class T>
void naturalMergingSort(const std::string& fileName, std::ostream& os) {
  size_t iterCounter = 1;
  size_t s1 = 0;
  size_t s2 = 0;

  size_t fileSelect = 1;

  T curElem;
  T curElem2;

  std::fstream mergeFile;
  std::fstream supportFile1;
  std::fstream supportFile2;

  do {
    s1 = s2 = 0;
    fileSelect = 1;

    mergeFile.open(fileName, std::ios_base::in);
    if (!mergeFile.is_open()) {
      std::cerr << "Error: Can't open a merge file!" << std::endl;
      return;
    }

    supportFile1.open("/home/mur/Programing/QtProjects/AaDS/Sorting/series_holder_1.txt", std::ios_base::out);
    supportFile2.open("/home/mur/Programing/QtProjects/AaDS/Sorting/series_holder_2.txt", std::ios_base::out);

    mergeFile >> curElem;
    if (!mergeFile.eof()) {
      supportFile1 << curElem << " ";
      ++s1;
    }
    if (!mergeFile.eof()) {
      mergeFile >> curElem2;
      ++s2;
    }

    while (!mergeFile.eof()) {
      if (curElem2 < curElem) {
        switch (fileSelect) {
          case 1:
            fileSelect = 2;
            supportFile1 << "| ";
            ++s1;
            break;
          case 2:
            fileSelect = 1;
            supportFile2 << "| ";
            ++s2;
            break;
        }
      }
      if (fileSelect == 1) {
        supportFile1 << curElem2 << " ";
      } else {
        supportFile2 << curElem2 << " ";
      }

      curElem = curElem2;
      mergeFile >> curElem2;
    }

    if (s1 > 0 && fileSelect == 1) {
      supportFile1 << "|";
      ++s1;
    }
    if (s2 > 0 && fileSelect == 2) {
      supportFile2 << "|";
      ++s2;
    }

    if (s1 != 0) {
      --s1;
      if (s2 != 0)
        --s2;
    }

    mergeFile.close();
    supportFile1.close();
    supportFile2.close();

    os << "Intermediate state at iteration #" << iterCounter++ << ":\n";
    os << "mergeFile: ";
    printFile(fileName, os);
    os << "supportFile1: ";
    printFile("/home/mur/Programing/QtProjects/AaDS/Sorting/series_holder_1.txt", os);
    os << "supportFile2: ";
    printFile("/home/mur/Programing/QtProjects/AaDS/Sorting/series_holder_2.txt", os);
    os << "s1 = " << s1 << " " << "s2 = " << s2 << std::endl;

    mergeFile.open(fileName, std::ios_base::out);
    if (!mergeFile.is_open()) {
      std::cerr << "Error: Can't open a merge file!" << std::endl;
      return;
    }

    supportFile1.open("/home/mur/Programing/QtProjects/AaDS/Sorting/series_holder_1.txt", std::ios_base::in);
    if (!supportFile1.is_open()) {
      std::cerr << "Error: Can't open first support file!" << std::endl;
      return;
    }

    supportFile2.open("/home/mur/Programing/QtProjects/AaDS/Sorting/series_holder_2.txt", std::ios_base::in);
    if (!supportFile1.is_open()) {
      std::cerr << "Error: Can't open first support file!" << std::endl;
      return;
    }

    supportFile1 >> curElem;
    supportFile2 >> curElem2;

    bool seriesEnd1;
    bool seriesEnd2;

    while (!supportFile1.eof() && !supportFile2.eof()) {
      seriesEnd1 = seriesEnd2 = false;
      while (!seriesEnd1 && !seriesEnd2) {
        if (curElem <= curElem2) {
          mergeFile << curElem << " ";
          seriesEnd1 = isSeriesEnd(supportFile1);
          supportFile1 >> curElem;
        } else {
          mergeFile << curElem2 << " ";
          seriesEnd2 = isSeriesEnd(supportFile2);
          supportFile2 >> curElem2;
        }
      }
      while (!seriesEnd1) {
        mergeFile << curElem << " ";
        seriesEnd1 = isSeriesEnd(supportFile1);
        supportFile1 >> curElem;
      }
      while (!seriesEnd2) {
        mergeFile << curElem2 << " ";
        seriesEnd2 = isSeriesEnd(supportFile2);
        supportFile2 >> curElem2;
      }
    }

    seriesEnd1 = seriesEnd2 = false;
    while (!supportFile1.eof() && !seriesEnd1) {
      mergeFile << curElem << " ";
      seriesEnd1 = isSeriesEnd(supportFile1);
      supportFile1 >> curElem;
    }
    while (!supportFile2.eof() && !seriesEnd2) {
      mergeFile << curElem << " ";
      seriesEnd2 = isSeriesEnd(supportFile2);
      supportFile2 >> curElem;
    }

    mergeFile.close();
    supportFile1.close();
    supportFile2.close();

  } while (s1 > 1 && s2 > 0);

  os << "Final result: ";
  printFile(fileName, os);

  std::remove("/home/mur/Programing/QtProjects/AaDS/Sorting/series_holder_1.txt");
  std::remove("/home/mur/Programing/QtProjects/AaDS/Sorting/series_holder_2.txt");
}

//int main() {
//  std::ofstream resFile("/home/mur/Programing/QtProjects/AaDS/Sorting/result.txt");

//  std::string fileName;
//  std::cout << "Please, enter the input file name: " << std::endl;
//  std::cin >> fileName;

//  naturalMergingSort<int>(fileName, resFile);

//  std::cout << "If you entered a valid file's name, result saves in file result.txt" << std::endl;
//  return 0;
//}
