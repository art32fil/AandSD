#include <iostream>
#include <memory>
#include <cstring>
#include <queue>
#include <string>
#include <fstream>

template<class T>
struct Node {
  size_t left = 0;
  size_t right = 0;
  T data;
};

template<class T>
class Forest;

template<class T>
class BinTree {
  template<class U>
  friend std::ostream& operator<<(std::ostream& os, const BinTree<U>& binT);
  template<class U>
  friend std::istream& operator>>(std::istream& is, BinTree<U>& binT);
public:
  BinTree(size_t capacity, size_t root)
    : capacity_(capacity), size_(0), root_(root) {
    arr_ = new Node<T>[capacity];
    for (size_t i = 0; i < capacity_ - 1; ++i) {
      arr_[i].left = i + 1;
    }
    arr_[capacity_ - 1].left = 0;
  }

  ~BinTree() {
    delete [] arr_;
  }

  operator bool() const {
    return (size_ != 0);
  }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  size_t root() const { return root_; }
  const Node<T>* array() const { return arr_; }

  void readBT(std::istream& is, size_t index) {
    T x;
    passSpaces(x, is);

    arr_[index].data = x;
    ++size_;

    update(index);

    passSpaces(x, is);

    if (x == '(') {
      arr_[index].left = arr_[0].left;
      readBT(is, arr_[0].left);
      passSpaces(x, is);
      if (x == '(') {
        arr_[index].right = arr_[0].left;
        readBT(is, arr_[0].left);
        passSpaces(x, is);
      }
    } else if (x == '#') {
      passSpaces(x, is);
      arr_[index].right = arr_[0].left;
      readBT(is, arr_[0].left);
      passSpaces(x, is);
    }
  }

  void read(std::istream& is) {
    T x;
    passSpaces(x, is);
    if (x == '(') {
      readBT(is, root_);
    } else {
      std::cerr << "Error: unexpected symbol" << std::endl;
    }
  }


  void passSpaces(T& x, std::istream& is) {
    do {
      is >> x;
    } while (x == ' ');
  }

  Forest<T>* toForest() const {
    return new Forest<T>(*this);
  }

  void print(std::ostream& os, const Node<T>& node, std::string prefix) const {
    os << prefix << "->" << node.data << std::endl;
    if (!node.left && !node.right)
      return;
    if (prefix.back() == '+') {
      prefix.pop_back();
      prefix += " ";
    }
    if (node.left) {
      if (!node.right) {
        print(os, arr_[node.left], prefix + "  +");
        return;
      }
      else
        print(os, arr_[node.left], prefix + "  |");
    } else {
      os << prefix << "  |->#" << std::endl;
    }
    if (node.right) {
      print(os, arr_[node.right], prefix + "  +");
    } else {
      os << prefix << "  +->#" << std::endl;
    }
  }

  void resize() {
    size_t newCapacity = capacity_ + capacity_ / 2;
    Node<T>* newArr = new Node<T>[newCapacity];

    std::memcpy((void*)newArr, (void*)arr_, sizeof (Node<T>) * capacity_);

    newArr[0].left = capacity_;
    for (size_t i = capacity_; i < newCapacity - 1; ++i) {
      newArr[i].left = i + 1;
    }
    newArr[newCapacity - 1].left = 0;

    delete [] arr_;
    arr_ = newArr;
    capacity_ = newCapacity;
  }

  void update(size_t indexChange) {
    size_t temp = 0;
    while (1) {
      if (arr_[temp].left == indexChange) {
        arr_[temp].left = arr_[indexChange].left;
        arr_[indexChange].left = 0;
        if (arr_[temp].left == temp) {
          resize();
        }
        break;
      } else {
        temp = arr_[temp].left;
      }
    }
  }

private:
  Node<T>* arr_;
  size_t capacity_;
  size_t size_;
  size_t root_;
};

template<class U>
std::ostream& operator<<(std::ostream& os, const BinTree<U>& binT) {
  if (binT) {
    binT.print(os, binT.arr_[binT.root_], "");
  } else {
    os << "Binary tree is empty!" << std::endl;
  }
  return os;
}

template<class U>
std::istream& operator>>(std::istream& is, BinTree<U>& binT) {
  binT.read(is);
  return is;
}

//------------------------------------------

template<class T>
class Forest {
  template<class U>
  friend std::ostream& operator<<(std::ostream& is, const Forest<U>& frst);
public:
  Forest(const BinTree<T>& bt)
    : capacity_(bt.capacity()),
      size_(bt.size()),
      root_(bt.root()) {
    arr_ = new Node<T>[capacity_];
    std::memcpy((void*)arr_, (void*)bt.array(), sizeof (Node<T>) * capacity_);
  }

  ~Forest() {
    delete [] arr_;
  }

  operator bool() const {
    return (size_ != 0);
  }

  void printWide(std::ostream& os) const {
    if (*this) {
      std::queue<Node<T>> q;
      q.push(arr_[root_]);
      printWideRec(os, q);
    } else {
      os << "Forest is empty!" << std::endl;
    }
  }

  void printWideRec(std::ostream& os, std::queue<Node<T>>& nodeQueue) const {
    if (nodeQueue.empty()) {
      os << "\n";
      return;
    }
    Node<T> curNode = nodeQueue.front();
    os << curNode.data << " ";
    nodeQueue.pop();

    if (curNode.left)
      nodeQueue.push(arr_[curNode.left]);
    if (curNode.right)
      nodeQueue.push(arr_[curNode.right]);
    printWideRec(os, nodeQueue);
  }

  void printForest(std::ostream& os, const Node<T>& node) const {
    os << "\nTree:" << std::endl;
    os << "->" << node.data << std::endl;
    if (node.left) {
      printTree(os, arr_[node.left], "  ");
    }
    if (node.right) {
      printForest(os, arr_[node.right]);
    }
  }

  void printTree(std::ostream& os, const Node<T>& node, std::string prefix) const {
    prefix += (node.right == 0) ? '+' : '|';
    os << prefix << "->" << node.data << std::endl;
    if (node.left) {
      if (prefix.back() == '+') {
        prefix.pop_back();
        prefix += " ";
      }
      printTree(os, arr_[node.left], prefix + "  ");
    }
    if (node.right) {
      prefix.pop_back();
      printTree(os, arr_[node.right], prefix);
    }
  }

private:
  Node<T>* arr_ = nullptr;
  size_t capacity_ = 0;
  size_t size_ = 0;
  size_t root_ = 0;
};

template<class U>
std::ostream& operator<<(std::ostream& os, const Forest<U>& frst) {
  if (frst) {
    frst.printForest(os, frst.arr_[frst.root_]);
  } else {
    os << "Forest is empty!" << std::endl;
  }
  return os;
}

int main() {
  size_t startCap = 0;
  size_t root = 0;

  std::cout << "Enter start capacity (> 1): " << std::endl;
  std::cin >> startCap;
  std::cout << "Enter root index (0 < index < capacity): " << std::endl;
  std::cin >> root;

  if ((root < 1) || (root >= startCap)) {
    std::cout << "Incorrect input" << std::endl;
    return 1;
  }

  std::string fileName;
  std::cout << "Enter file name: ";
  std::cin >> fileName;

  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cout << "Can't open a file\n";
    return 1;
  }

  std::ofstream resFile("/home/mur/Programing/QtProjects/AaDS/Trees/result.txt");
  std::cout << "Result will be saved in result.txt" << std::endl;

  BinTree<char> bt(startCap, root);
  file >> bt;

  resFile << "1st task check:\n";
  std::shared_ptr<Forest<char>> fptr(bt.toForest());
  resFile << *fptr;

  resFile << "2nd task check:\n";
  resFile << bt;


  resFile << "3rd task check:\n";
  fptr->printWide(resFile);

  file.close();
  resFile.close();
  return 0;
}

