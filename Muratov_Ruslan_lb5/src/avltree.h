#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

#include "node.h"

template<class T>
class AvlTree {
  using NodePtr = std::shared_ptr<Node<T>>;
public:
  AvlTree() = default;
  ~AvlTree() = default;

  void insert(const T& key);
  void remove(const T& key);

  void printInfix(std::ofstream& outFile) const;
  void printToConsole() const;
  void printDot(std::ofstream& dotFile) const;

protected:
  uint8_t height(NodePtr node);
  int8_t balanceFactor(NodePtr node);
  void fixHeight(NodePtr node);

  NodePtr rotateLeft(NodePtr node);
  NodePtr rotateRight(NodePtr node);

  NodePtr balance(NodePtr node);

  NodePtr insertAux(NodePtr node, const T& key); // Вспомогательная функция для метода insert

  NodePtr findMin(NodePtr node); // Поиск узла с наименьшим ключом в дереве с корнем node
  NodePtr removeMin(NodePtr node); // Удаление узла с минимальным ключом из дерева с корнем node
  NodePtr removeAux(NodePtr node, const T& key); // Удаление ключа k из дерева с корнем node (вспомогательная функция для метода remove)

  void printInfixAux(NodePtr node, std::ofstream& outFile) const;
  void stepPrint(NodePtr node, uint8_t step) const;
  void printDotAux(NodePtr node, std::ofstream& dotFile) const;

private:
  NodePtr head_ = nullptr;
  std::map<T, size_t> nodeCounter;
};

#include "avltree.cpp"

#endif // AVLTREE_H


