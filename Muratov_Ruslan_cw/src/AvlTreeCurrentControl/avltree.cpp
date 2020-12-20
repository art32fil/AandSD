#ifndef BIN_TREE_CPP
#define BIN_TREE_CPP

#include "avltree.h"

template<class T>
AvlTree<T>::AvlTree(const AvlTree<T>& otherTree) {
  head_ = copyAux(otherTree.head_);

  nodeCounter_ = otherTree.nodeCounter_;
  lastBalancedNodes_ = otherTree.lastBalancedNodes_;
  lastRotations_ = otherTree.lastRotations_;
}

template<class T>
AvlTree<T>& AvlTree<T>::operator=(const AvlTree<T>& otherTree) {
  // Дерево не может присвоить саму себя
  if (this != &otherTree) {
    head_ = copyAux(otherTree.head_);

    nodeCounter_ = otherTree.nodeCounter_;
    lastBalancedNodes_ = otherTree.lastBalancedNodes_;
    lastRotations_ = otherTree.lastRotations_;
  }
  return *this;
}

template<class T>
void AvlTree<T>::insert(const T& key) {
  // Удаляем информацию, относящуюся к прошлому действию
  lastBalancedNodes_.clear();
  lastRotations_.clear();

  head_ = insertAux(head_, key);
}

template<class T>
void AvlTree<T>::remove(const T& key) {
  // Удаляем информацию, относящуюся к прошлому действию
  lastBalancedNodes_.clear();
  lastRotations_.clear();

  head_ = removeAux(head_, key);
}

template<class T>
bool AvlTree<T>::haveSameFrame(const AvlTree<T>& otherTree) const {
  return haveSameFrameAux(head_, otherTree.head_);
}

template<class T>
std::vector<T> AvlTree<T>::getPrefixOrder() const {
  std::vector<T> v;
  v = getPrefixOrderAux(head_, v);
  return v;
}

template<class T>
void AvlTree<T>::printInfix(std::ofstream& outFile) const {
  printInfixAux(head_, outFile);
}

template<class T>
void AvlTree<T>::printToFile(std::ofstream& outFile) const {
  printToFileAux(head_, outFile, 0);
}

template<class T>
void AvlTree<T>::printFrameToFile(std::ofstream& outFile) const {
  printFrameToFileAux(head_, outFile, 0);
}

template<class T>
void AvlTree<T>::printToConsole() const {
  stepPrint(head_, 0);
  std::cout << "-------------------\n";
}

template<class T>
void AvlTree<T>::printDot(std::fstream& dotFile) const {
  dotFile << "digraph AVL_tree {\n";

  // Здесь позже можно настроить узлы и ребра

  if (!head_)
    dotFile << "\n";
  else if (!head_->left && !head_->right)
    dotFile << "  n [label = \"" << head_->key << "\"]" << ";\n";
  else
    printDotAux(head_, dotFile);

  dotFile << "}\n";
}

template<class T>
void AvlTree<T>::printDotWithCount(std::fstream& dotFile) const {
  dotFile << "digraph AVL_tree {\n";

  // Здесь позже можно настроить узлы и ребра

  if (!head_)
    dotFile << "\n";
  else if (!head_->left && !head_->right)
    dotFile << "  n [label = \"" << head_->key << " (" << nodeCounter_.at(head_->key) << ")\"]" << ";\n";
  else
    printDotWithCountAux(head_, dotFile);

  dotFile << "}\n";
}

template<class T>
void AvlTree<T>::printFrameDot(std::fstream& dotFile) const {
  dotFile << "digraph AVL_tree {\n";

  // Здесь позже можно настроить узлы и ребра

  if (!head_)
    dotFile << "\n";
  else if (!head_->left && !head_->right)
    dotFile << "  n [label = \"#\"]" << ";\n";
  else
    printFrameDotAux(head_, dotFile);

  dotFile << "}\n";
}

template<class T>
uint8_t AvlTree<T>::height(NodePtr node) {
  return node ? node->height : 0;
}

template<class T>
int8_t AvlTree<T>::balanceFactor(NodePtr node) {
  return height(node->right) - height(node->left);
}

template<class T>
void AvlTree<T>::fixHeight(NodePtr node) {
  node->height = std::max(height(node->left), height(node->right)) + 1;
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::rotateLeft(NodePtr node) {
  NodePtr newHead(node->right);
  node->right = newHead->left;
  newHead->left = node;
  fixHeight(node);
  fixHeight(newHead);
  return newHead;
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::rotateRight(NodePtr node) {
  NodePtr newHead(node->left);
  node->left = newHead->right;
  newHead->right = node;
  fixHeight(node);
  fixHeight(newHead);
  return newHead;
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::balance(NodePtr node) {
  fixHeight(node);
  if (balanceFactor(node) == 2) { // h(right) - h(left) == 2
    if (balanceFactor(node->right) < 0) {
      lastRotations_.emplace_back('r', node->right->key);
      node->right = rotateRight(node->right);
    }
    lastRotations_.emplace_back('l', node->key);
    lastBalancedNodes_.push_back(node->key);
    return rotateLeft(node);
  } else if (balanceFactor(node) == -2) { // h(right) - h(left) == -2
    if (balanceFactor(node->left) > 0) {
      lastRotations_.emplace_back('l', node->left->key);
      node->left = rotateLeft(node->left);
    }
    lastRotations_.emplace_back('r', node->key);
    lastBalancedNodes_.push_back(node->key);
    return rotateRight(node);
  }
  return node; // Балансировка не нужна
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::insertAux(NodePtr node, const T& key) {
  if (!node) {
    nodeCounter_[key] = 1;
    return std::make_shared<Node<T>>(key);
  }
  if (key < node->key)
    node->left = insertAux(node->left, key);
  else if (key > node->key)
    node->right = insertAux(node->right, key);
  else // Если узел уже имеется в дереве, то учитываем это
    ++nodeCounter_.at(key);
  return balance(node);
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::copyAux(NodePtr otherNode) {
  NodePtr node = std::make_shared<Node<T>>(otherNode->key, otherNode->height);
  if (otherNode->left) {
    node->left = copyAux(otherNode->left);
  }
  if (otherNode->right) {
    node->right = copyAux(otherNode->right);
  }
  return node;
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::findMin(NodePtr node) {
  while (node->left)
    node = node->left;
  return node;
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::removeMin(NodePtr node) {
  if (!node->left) {
    return node->right;
  }
  node->left = removeMin(node->left);
  return balance(node);
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::removeAux(NodePtr node, const T& key) {
  if (!node)
    return nullptr;
  if (key < node->key) {
    node->left = removeAux(node->left, key);
  } else if (key > node->key) {
    node->right = removeAux(node->right, key);
  } else {
    if (--nodeCounter_.at(key) == 0) { // Удаляем узел из дерева только тогда, когда его счетчик обнулился
      if (!node->right)
        return node->left;
      NodePtr minElem = findMin(node->right);
      minElem->right = removeMin(node->right);
      minElem->left = node->left;
      return balance(minElem);
    }
  }
  return balance(node);
}

template<class T>
std::vector<T> AvlTree<T>::getPrefixOrderAux(AvlTree<T>::NodePtr node, std::vector<T>& vec) const {
  if (node) {
    vec.push_back(node->key);
    vec = getPrefixOrderAux(node->left, vec);
    vec = getPrefixOrderAux(node->right, vec);
  }
  return vec;
}

template<class T>
bool AvlTree<T>::haveSameFrameAux(NodePtr thisNode, NodePtr otherNode) const {
  if (thisNode && otherNode) {
    return haveSameFrameAux(thisNode->left, otherNode->left) &&
        haveSameFrameAux(thisNode->right, otherNode->right);
  } else if (thisNode || otherNode) {
    return false;
  } else { // thisNode == otherNode == nullptr
    return true;
  }
}

template<class T>
void AvlTree<T>::printToFileAux(NodePtr node, std::ofstream& outFile, uint8_t step) const {
  for (uint8_t i = 0; i < step; ++i)
    outFile << "  ";
  if (node) {
    outFile << node->key << std::endl;
    printToFileAux(node->left, outFile, step + 1);
    printToFileAux(node->right, outFile, step + 1);
  } else {
    outFile << "-" << std::endl;
  }
}

template<class T>
void AvlTree<T>::printFrameToFileAux(NodePtr node, std::ofstream& outFile, uint8_t step) const {
  for (uint8_t i = 0; i < step; ++i)
    outFile << "  ";
  if (node) {
    outFile << "#" << std::endl;
    printFrameToFileAux(node->left, outFile, step + 1);
    printFrameToFileAux(node->right, outFile, step + 1);
  } else {
    outFile << "-" << std::endl;
  }
}

template<class T>
void AvlTree<T>::printInfixAux(NodePtr node, std::ofstream& outFile) const {
  if (node) {
    printInfixAux(node->left, outFile);
    outFile << node->key  << " (" << nodeCounter_.at(node->key) << ")" << " ";
    printInfixAux(node->right, outFile);
  }
}

template<class T>
void AvlTree<T>::stepPrint(NodePtr node, uint8_t step) const {
  for (uint8_t i = 0; i < step; ++i)
    std::cout << "  ";
  if (node) {
    std::cout << node->key  << " (" << nodeCounter_.at(node->key) << ")" << std::endl;
    stepPrint(node->left, step + 1);
    stepPrint(node->right, step + 1);
  } else {
    std::cout << "-" << std::endl;
  }
}

template<class T>
void AvlTree<T>::printDotAux(NodePtr node, std::fstream& dotFile) const {
  static int counter = 0;
  if (!node) {
    dotFile << "  n" << ++counter << " [ shape = point ];\n";
    return;
  }

  std::tuple<int, int, int> indexes = {-1, -1, -1};
  dotFile << "  n" << ++counter << " [ label = " << "\"" << node->key << "\" ];\n";

  std::get<0>(indexes) = counter;

  std::get<1>(indexes) = counter + 1;
  printDotAux(node->left, dotFile);

  std::get<2>(indexes) = counter + 1;
  printDotAux(node->right, dotFile);

  dotFile << "  n" << std::get<0>(indexes) << " -> {" <<
             ((std::get<1>(indexes) > 0) ? "n" + std::to_string(std::get<1>(indexes)) : "") << " " <<
             ((std::get<2>(indexes) > 0) ? "n" + std::to_string(std::get<2>(indexes)) : "") << "};\n";
}

template<class T>
void AvlTree<T>::printDotWithCountAux(NodePtr node, std::fstream& dotFile) const {
  static int counter = 0;
  if (!node) {
    dotFile << "  n" << ++counter << " [ shape = point ];\n";
    return;
  }

  std::tuple<int, int, int> indexes = {-1, -1, -1};
  dotFile << "  n" << ++counter << " [ label = " << "\"" << node->key << " (" << nodeCounter_.at(node->key) << ")\" ];\n";

  std::get<0>(indexes) = counter;

  std::get<1>(indexes) = counter + 1;
  printDotAux(node->left, dotFile);

  std::get<2>(indexes) = counter + 1;
  printDotAux(node->right, dotFile);

  dotFile << "  n" << std::get<0>(indexes) << " -> {" <<
             ((std::get<1>(indexes) > 0) ? "n" + std::to_string(std::get<1>(indexes)) : "") << " " <<
             ((std::get<2>(indexes) > 0) ? "n" + std::to_string(std::get<2>(indexes)) : "") << "};\n";
}

template<class T>
void AvlTree<T>::printFrameDotAux(NodePtr node, std::fstream& dotFile) const {
  static int counter = 0;
  if (!node) {
    dotFile << "  n" << ++counter << " [ shape = point ];\n";
    return;
  }

  std::tuple<int, int, int> indexes = {-1, -1, -1};
  dotFile << "  n" << ++counter << " [ label = " << "\"#\" ];\n";

  std::get<0>(indexes) = counter;

  std::get<1>(indexes) = counter + 1;
  printFrameDotAux(node->left, dotFile);

  std::get<2>(indexes) = counter + 1;
  printFrameDotAux(node->right, dotFile);

  dotFile << "  n" << std::get<0>(indexes) << " -> {" <<
             ((std::get<1>(indexes) > 0) ? "n" + std::to_string(std::get<1>(indexes)) : "") << " " <<
             ((std::get<2>(indexes) > 0) ? "n" + std::to_string(std::get<2>(indexes)) : "") << "};\n";
}

#endif

