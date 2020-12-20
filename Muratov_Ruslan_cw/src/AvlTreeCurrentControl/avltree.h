#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

#include "node.h"

template<class T>
class AvlTree {
  // Умный указатель на узел
  using NodePtr = std::shared_ptr<Node<T>>;
  // Пара, в которой хранится информация о вращении и корне, вокруг которого оно происходит
  using RotPivot = std::pair<char, T>;
public:
  AvlTree() = default;
  ~AvlTree() = default;

  // Создание нового дерева на основе otherTree
  AvlTree(const AvlTree<T>& otherTree);
  AvlTree<T>& operator=(const AvlTree<T>& otherTree);

  // Вставка элемента key в дерево
  void insert(const T& key);
  // Удаление элемента key из дерева
  void remove(const T& key);

  // Проверка совпадения каркасов деревьев
  bool haveSameFrame(const AvlTree<T>& otherTree) const;

  // Получение элементов дерева в КЛП-порядке
  std::vector<T> getPrefixOrder() const;

  // Геттеры для полей класса
  const std::map<T, size_t>& getNodeCounter() const { return nodeCounter_; }
  const std::vector<T>& getLastBalancedNodes() const { return lastBalancedNodes_; }
  const std::vector<RotPivot>& getLastRotations() const { return lastRotations_; }

  // Печать элементов дерева в файл oufFile в ЛКП-порядке
  void printInfix(std::ofstream& outFile) const;
  // Печать дерева в файл в виде уступчатого списка
  void printToFile(std::ofstream& outFile) const;
  // Печать каркаса дерева в файл в виде уступчатого списка
  void printFrameToFile(std::ofstream& outFile) const;
  // Печать дерева в консоль
  void printToConsole() const;
  // Печать дерева (без количества повторений) в файл dotFile на языке DOT
  void printDot(std::fstream& dotFile) const;
  // Печать дерева (с количеством повторений) в файл dotFile на языке DOT
  void printDotWithCount(std::fstream& dotFile) const;
  // Печать каркаса дерева (то есть без указания элементов) в файл dotFile на языке DOT
  void printFrameDot(std::fstream& dotFile) const;

protected:
  // Высота узла node
  uint8_t height(NodePtr node);
  // Разность высот правого и левого поддеревьев узла node
  int8_t balanceFactor(NodePtr node);
  // Восстановление актуальности поля height узла node
  void fixHeight(NodePtr node);

  // Вращения налево и направо вокруг узла node
  NodePtr rotateLeft(NodePtr node);
  NodePtr rotateRight(NodePtr node);

  // Балансировка узла node
  NodePtr balance(NodePtr node);

  // Вспомогательная функция для метода insert
  NodePtr insertAux(NodePtr node, const T& key);

  // Вспомогательная функция для конструктора копирования и оператора присваивания
  NodePtr copyAux(NodePtr otherNode);

  // Поиск узла с наименьшим ключом в дереве с корнем node
  NodePtr findMin(NodePtr node);
  // Удаление узла с минимальным ключом из дерева с корнем node
  NodePtr removeMin(NodePtr node);
  // Удаление ключа k из дерева с корнем node (вспомогательная функция для метода remove)
  NodePtr removeAux(NodePtr node, const T& key);

  // Элементы дерева в КЛП-порядке
  std::vector<T> getPrefixOrderAux(NodePtr node, std::vector<T>& vec) const;

  // Вспомогательная функция для метода haveSameFrame
  bool haveSameFrameAux(NodePtr thisNode, NodePtr otherNode) const;

  // Вспомогательная функция для метода printToFile
  void printToFileAux(NodePtr node, std::ofstream& outFile, uint8_t step) const;
  // Вспомогательная функция для метода printFrameToFile
  void printFrameToFileAux(NodePtr node, std::ofstream& outFile, uint8_t step) const;
  // Вспомогательная функция для метода printInfix
  void printInfixAux(NodePtr node, std::ofstream& outFile) const;
  // Вспомогательная функция для метода printToConsole
  void stepPrint(NodePtr node, uint8_t step) const;

  // Вспомогательные функции для методов printDot,
  // printDotWithCountAux и printFrameDotAux соответственно
  void printDotAux(NodePtr node, std::fstream& dotFile) const;
  void printDotWithCountAux(NodePtr node, std::fstream& dotFile) const;
  void printFrameDotAux(NodePtr node, std::fstream& dotFile) const;

private:
  // Указатель на голову дерева
  NodePtr head_ = nullptr;

  // Счетчик количества повторении элемента в дереве (для поддержания повторяющихся ключей)
  std::map<T, size_t> nodeCounter_;

  // Сбалансированные узлы после последней проведенной операции (вставка или удаление)
  std::vector<T> lastBalancedNodes_;

  // Направления вращения и узлы, вокруг которых они произошли после последней
  // проведенной операции (вставка или удаление)
  std::vector<RotPivot> lastRotations_;
};

#include "avltree.cpp"

#endif // AVLTREE_H


