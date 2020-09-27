#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// brackets = A | B | (brackets brackets)

enum Error {
  FILE_NOT_OPEN,
  FILE_IS_EMPTY,
  INVALID_CHAR, // (brackets@
  INCOMPLETE_BRACKETS, // (brackets) or ()
  BRACKETS_NOT_CLOSE, // (brackets brackets
  EXTRA_CHAR // (brackets brackets)~
};

void passLineTail(ifstream& inFile);
void printIndent(uint16_t indent);
void getError(Error e, ostream& outFile);
bool areBrackets(ifstream& inFile, ofstream& outFile, char curSymbol, uint16_t recDepth);

int main() {
  bool result = false;
  char curChar = '\0';

  cout << "Please, enter an input file name:\n";
  string filePath;
  cin >> filePath;
  ifstream inFile(filePath);
  if (!inFile.is_open()) {
    getError(FILE_NOT_OPEN, cout);
    return 0;
  }

  cout << "Result was placed in \'result.txt\' file of current directory\n";
  cout << "Here is intermediate data what visualize computing process\n\n";
  ofstream outFile("./result.txt");

  if (inFile.peek() == EOF) {
    inFile.close();
    outFile.close();
    getError(FILE_IS_EMPTY, cout);
    return 0;
  }

  outFile << "Brackets analyzer\n\n";
  while (1) {
    inFile >> curChar;
    if (inFile.eof()) {
      break;
    }

    result = areBrackets(inFile, outFile, curChar, 0);

    if (result) {
      if ((curChar = inFile.get()) != '\n') {
        outFile << curChar;
        cout << curChar << '\n';
        getError(EXTRA_CHAR, outFile);
        outFile << "Input sequence is NOT brackets\n\n";
        passLineTail(inFile);
      } else {
        outFile << "\nInput sequence is brackets\n\n";
      }
    } else {
      outFile << "Input sequence is NOT brackets\n\n";
      inFile.unget();
      passLineTail(inFile);
    }
    cout << '\n';
  }

  inFile.close();
  outFile.close();

  return 0;
}

void printIndent(uint16_t indent) {
  for (uint16_t i = 0; i < indent; ++i)
    cout << "-";
}

void passLineTail(ifstream& inFile) {
  while (inFile.get() != '\n') {}
}

void getError(Error e, ostream& outFile) {
  switch (e) {
    case FILE_NOT_OPEN:
      outFile << "\nError: Can't open a file!\n";
      break;
    case FILE_IS_EMPTY:
      outFile << "\nError: File is empty!\n";
      break;
    case INVALID_CHAR:
      outFile << "\nError: There is an invalid char in sequence!\n";
      break;
    case INCOMPLETE_BRACKETS:
      outFile << "\nError: There is an incomplete brackets!\n";
      break;
    case BRACKETS_NOT_CLOSE:
      outFile << "\nError: Brackets isn't closed!\n";
      break;
    case EXTRA_CHAR:
      outFile << "\nError: There is extra characters after sequence!\n";
      break;
  }
}

bool areBrackets(ifstream& inFile, ofstream& outFile, char curSymbol, uint16_t recDepth) {
  outFile << curSymbol;
  printIndent(recDepth);
  cout << curSymbol << '\n';
  if ((curSymbol == '(') || (curSymbol == ')') ||
      (curSymbol == 'A') || (curSymbol == 'B')) {
    if ((curSymbol == 'A') || (curSymbol == 'B')) {
      return true;
    } else if (curSymbol == '(') {
      // brackets = (brackets brackets)
      if ((curSymbol = inFile.get()) != '\n') {
        if (areBrackets(inFile, outFile, curSymbol, recDepth + 1)) {
          // first "brackets" is valid
          if ((curSymbol = inFile.get()) != '\n') {
            if (areBrackets(inFile, outFile, curSymbol, recDepth + 1)) {
              // second "brackets" is valid
              if ((curSymbol = inFile.get()) != '\n') {
                outFile << curSymbol;
                printIndent(recDepth);
                cout << curSymbol << '\n';
                if (curSymbol == ')') {
                  return true;
                } else {
                  // Невалидный символ: #, $, % и т.д.
                  getError(INVALID_CHAR, outFile);
                  return false;
                }
              } else {
                // Незакрытая скобка: (AA\n or (AA*eof*
                getError(BRACKETS_NOT_CLOSE, outFile);
                return false;
              }
            } else {
              return false;
            }
          } else {
            // Незакрытая скобка: (A\n or ((BB)\n
            getError(BRACKETS_NOT_CLOSE, outFile);
            return false;
          }
        } else {
          return false;
        }
      } else {
        // Незакрытая скобка: (\n
        getError(BRACKETS_NOT_CLOSE, outFile);
        return false;
      }
    } else {
      // curSymbol == ')'
      // Неполная скобка, так как если скобка полная,
      // то алгоритм дойдет до конца и вернет true.
      // Если последовательность валидная,
      // то на вход функции никогда не придет символ ')'
      getError(INCOMPLETE_BRACKETS, outFile);
      return false;
    }
  } else {
    // Невалидный символ: #, $, % и т.д.
    getError(INVALID_CHAR, outFile);
    return false;
  }
}
