#ifndef BIN_TREE_CPP
#define BIN_TREE_CPP

#include "avltree.h"

template<class T>
void AvlTree<T>::insert(const T& key) {
  head_ = insertAux(head_, key);
}

template<class T>
void AvlTree<T>::remove(const T& key) {
  head_ = removeAux(head_, key);
}

template<class T>
void AvlTree<T>::printInfix(std::ofstream& outFile) const {
  printInfixAux(head_, outFile);
}

template<class T>
void AvlTree<T>::printToConsole() const {
  stepPrint(head_, 0);
  std::cout << "-------------------\n";
}

template<class T>
void AvlTree<T>::printDot(std::ofstream& dotFile) const {
  dotFile << "digraph AVL_tree {\n";

  // Здесь позже можно настроить узлы и ребра

  if (!head_)
    dotFile << "\n";
  else if (!head_->left && !head_->right)
    dotFile << "  n [label = \"" << head_->key << " (" << nodeCounter.at(head_->key) << ")\"]" << ";\n";
  else
    printDotAux(head_, dotFile);

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
      node->right = rotateRight(node->right);
    }
    return rotateLeft(node);
  } else if (balanceFactor(node) == -2) { // h(right) - h(left) == -2
    if (balanceFactor(node->left) > 0) {
      node->left = rotateLeft(node->left);
    }
    return rotateRight(node);
  }
  return node; // Балансировка не нужна
}

template<class T>
typename AvlTree<T>::NodePtr AvlTree<T>::insertAux(NodePtr node, const T& key) {
  if (!node) {
    nodeCounter[key] = 1;
    return std::make_shared<Node<T>>(key);
  }
  if (key < node->key)
    node->left = insertAux(node->left, key);
  else if (key > node->key)
    node->right = insertAux(node->right, key);
  else // Если узел уже имеется в дереве, то учитываем это
    ++nodeCounter.at(key);
  return balance(node);
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
    if (--nodeCounter.at(key) == 0) { // Удаляем узел из дерева только тогда, когда его счетчик обнулился
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
void AvlTree<T>::printInfixAux(NodePtr node, std::ofstream& outFile) const {
  if (node) {
    printInfixAux(node->left, outFile);
    outFile << node->key << " ";
    printInfixAux(node->right, outFile);
  }
}

template<class T>
void AvlTree<T>::stepPrint(NodePtr node, uint8_t step) const {
  for (uint8_t i = 0; i < step; ++i)
    std::cout << "  ";
  if (node) {
    std::cout << node->key  << " (" << nodeCounter.at(node->key) << ")" << std::endl;
    stepPrint(node->left, step + 1);
    stepPrint(node->right, step + 1);
  } else {
    std::cout << "-" << std::endl;
  }
}

template<class T>
void AvlTree<T>::printDotAux(NodePtr node, std::ofstream& dotFile) const {
  static int counter = 0;
  if (!node) {
    dotFile << "  n" << ++counter << " [ shape = point ];\n";
    return;
  }

  std::tuple<int, int, int> indexes = {-1, -1, -1};
  dotFile << "  n" << ++counter << " [ label = " << "\"" << node->key << " (" << nodeCounter.at(node->key) << ")\" ];\n";

  std::get<0>(indexes) = counter;

  std::get<1>(indexes) = counter + 1;
  printDotAux(node->left, dotFile);

  std::get<2>(indexes) = counter + 1;
  printDotAux(node->right, dotFile);

  dotFile << "  n" << std::get<0>(indexes) << " -> {" <<
             ((std::get<1>(indexes) > 0) ? "n" + std::to_string(std::get<1>(indexes)) : "") << " " <<
             ((std::get<2>(indexes) > 0) ? "n" + std::to_string(std::get<2>(indexes)) : "") << "};\n";
}

#endif

