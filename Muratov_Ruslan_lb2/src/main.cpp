#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

namespace HList {
enum Type : uint8_t {
  ARG, PAIR, OPERATION
};

using Base = std::string;

struct SExpr;

struct Pair {
  SExpr* head;
  SExpr* tail;
};

struct SExpr {
//  SExpr() {};
//  ~SExpr() {};
  Type type;
  Pair pair;
  Base opOrArg;
};

using LogicalExpr = SExpr*;

LogicalExpr head(const LogicalExpr logExpr);
LogicalExpr tail(const LogicalExpr logExpr);

LogicalExpr construct(const LogicalExpr h, const LogicalExpr t);
LogicalExpr makeArg(Base a);
LogicalExpr makeOper(Base op);

bool isArg(const LogicalExpr le);
bool isOper(const LogicalExpr le);
bool isPair(const LogicalExpr le);
bool isNull(const LogicalExpr le);

void destroy(LogicalExpr le);

void print(const LogicalExpr logExpr, std::ostream& os);
void printSeq(const LogicalExpr logExpr, std::ostream& os);

void read(LogicalExpr& logExpr, std::istream& is);
void readSExpr(Base prev, LogicalExpr& logExpr, std::istream& is);
void readSeq(LogicalExpr& logExpr, std::istream& is);

bool check(LogicalExpr logExpr, std::ostream& os);
bool checkArgs(LogicalExpr logExpr, int8_t& counter, std::string opType, std::ostream& os);

LogicalExpr head(const LogicalExpr logExpr) {
  if (logExpr != nullptr) {
    if (!isArg(logExpr)) {
      return logExpr->pair.head;
    } else {
      std::cerr << "Error: head(Atom)\n";
      exit(1);
    }
  } else {
    std::cerr << "Error: head(nullptr)\n";
    exit(1);
  }
}

LogicalExpr tail(const LogicalExpr logExpr) {
  if (logExpr != nullptr) {
    if (!isArg(logExpr)) {
      return logExpr->pair.tail;
    } else {
      std::cerr << "Error: head(Atom)\n";
      exit(1);
    }
  } else {
    std::cerr << "Error: tail(nullptr)\n";
    exit(1);
  }
}

bool isArg(const LogicalExpr le) {
  return (!isNull(le)) && (le->type == ARG);
}

bool isNull(const LogicalExpr le) {
  return le == nullptr;
}

LogicalExpr construct(const LogicalExpr h, const LogicalExpr t) {
  if (isArg(t)) {
    std::cerr << "Error: construct(*, Atom)" << std::endl;
    exit(1);
  } else {
    LogicalExpr newHL = new SExpr;
    newHL->type = PAIR;
    newHL->pair.head = h;
    newHL->pair.tail = t;
    return newHL;
  }
}

LogicalExpr makeArg(Base a) {
  LogicalExpr newHL = new SExpr;
  newHL->type = ARG;
  newHL->opOrArg = a;
  return newHL;
}

void destroy(LogicalExpr le) {
  if (!isNull(le)) {
    if (le->type == PAIR) {
      destroy(head(le));
      destroy(tail(le));
    }
    delete le;
  }
}

void print(const LogicalExpr logExpr, std::ostream& os) {
  if (isNull(logExpr)) {
    os << "()";
  } else if (isArg(logExpr)) {
    os << logExpr->opOrArg;
  } else if (isOper(logExpr)) {
    os << logExpr->opOrArg;
//    os << "[" << hl->opOrArg << "]";
  } else {
    os << "(";
    printSeq(logExpr, os);
    os << ")";
  }
}

void printSeq(const LogicalExpr logExpr, std::ostream& os) {
  if (!isNull(logExpr)) {
    print(head(logExpr), os);
    printSeq(tail(logExpr), os);
  }
}

void read(LogicalExpr& logExpr, std::istream& is) {
  Base x;
  is >> x;
  readSExpr(x, logExpr, is);
}

void readSExpr(Base prev, LogicalExpr& logExpr, std::istream& is) {
  if (prev == ")") {
    std::cerr << "Error: prev == \')\'" << std::endl;
    exit(1);
  } else if (prev != "(") {
    if (prev == "AND" || prev == "OR" || prev == "NOT" || prev == "XOR")
      logExpr = makeOper(prev);
    else
      logExpr = makeArg(prev);
  } else {
    readSeq(logExpr, is);
  }
}

void readSeq(LogicalExpr& logExpr, std::istream& is) {
  Base x;
  is >> x;
//  std::string op;
  LogicalExpr le1, le2;
  if (is.eof()) {
    std::cerr << "Error: incorrect expression" << std::endl;
    exit(1);
  } else {
    if (x == ")") {
      logExpr = nullptr;
    }
    else {
      readSExpr(x, le1, is);
      readSeq(le2, is);
      logExpr = construct(le1, le2);
    }
  }
}

bool isCorrect(LogicalExpr logExpr) {
  if (isNull(logExpr)) {
    return false;
  } else if (isArg(logExpr)) {
    return true;
  } else
    if (head(logExpr)->type == ARG) {
      return true;
    } else {
      return false;
    }
}

bool check(LogicalExpr logExpr, std::ostream& os) {
  int8_t counter = 0;
  std::string opType;
  if (isPair(logExpr)) {
    LogicalExpr h = head(logExpr);
    if (isOper(h) && (h->opOrArg == "AND" || h->opOrArg == "OR" || h->opOrArg == "XOR" || h->opOrArg == "NOT")) {
      counter = 0;
      opType = h->opOrArg;
      return checkArgs(tail(logExpr), counter, opType, os);
    } else {
      os << "Invalid expression: There is missed one or more operations in the expression" << std::endl;;
      return false;
    }
  } else {
    os << "Invalid expression: There is no arguments or operations in the expression" << std::endl;
    return false;
  }
}

bool checkArgs(LogicalExpr logExpr, int8_t& counter, std::string opType, std::ostream& os) {
  int8_t oldVal = 0;
  if (isPair(logExpr)) {
    LogicalExpr h = head(logExpr);
    if (isPair(h)) { // Операция
      oldVal = counter + 1; // Учитываем аргумент, являющийся рез-том операции
      bool correctnessNextOp = check(h, os);
      counter = oldVal;
      return correctnessNextOp && checkArgs(tail(logExpr), counter, opType, os);
    } else if (h == nullptr) { // Пустые скобки
      os << "Invalid expression: There is an empty brackets" << std::endl;
      return false;
    } else { // Аргументы
      return checkArgs(tail(logExpr), ++counter, opType, os);
    }
  } else { // Достигнут конец списка аргументов
    if (opType == "AND" || opType == "OR" || opType == "XOR")
      if (counter > 1)
        return true;
      else {
        os << "Invalid expression: There is too few arguments for " << opType << std::endl;
        return false;
      }
    else {
      if (counter > 0)
        return true;
      else {
        os << "Invalid expression: There is too few arguments for NOT" << std::endl;
        return false;
    }
    }
  }
}

LogicalExpr makeOper(Base op) {
  LogicalExpr le = new SExpr;
  le->type = OPERATION;
  le->opOrArg = op;
  return le;
}


bool isOper(const LogicalExpr le) {
  return (!isNull(le)) && (le->type == OPERATION);
}

bool isPair(const LogicalExpr le) {
  return (!isNull(le)) && (le->type == PAIR);
}
}

int main() {
  HList::LogicalExpr logExpr = nullptr;

  std::string inFileName;
  std::cout << "Enter input file name: ";
  std::cin >> inFileName;

  std::fstream f(inFileName);
  if (!f.is_open()) {
    std::cerr << "Error: cannot open a file" << std::endl;
    exit(1);
  }
  std::ofstream outFile("out.txt");
  std::cout << "Result will be saved in out.txt" << std::endl;

//  HList::read(logExpr, f);
//  HList::print(logExpr, outFile);
//  outFile << '\n';
//  if (check(logExpr, outFile)) {
//    outFile << "CORRECT\n";
//  } else {
//    outFile << "INCORRECT\n";
//  }
//  destroy(logExpr);

  std::string line;

  while (1) {
    std::getline(f, line);
    line.push_back('\n');
    if (f.eof()) {
      break;
    }
    std::stringstream lineStream(line);
    HList::read(logExpr, lineStream);
    HList::print(logExpr, outFile);
    outFile << '\n';
    if (check(logExpr, outFile)) {
      outFile << "CORRECT\n";
    } else {
      outFile << "INCORRECT\n";
    }
    destroy(logExpr);
    logExpr = nullptr;
  }

  f.close();

  return 0;
}


