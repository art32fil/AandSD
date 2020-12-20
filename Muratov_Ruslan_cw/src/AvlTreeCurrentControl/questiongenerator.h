#ifndef QUESTIONGENERATOR_H
#define QUESTIONGENERATOR_H

#include <QDebug>

#include <memory>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "avltree.h"
#include "questionanswer.h"
#include "icheckstrategy.h"
#include "fullmatch.h"
#include "oneof.h"

/*
Типы вопросов:
1) Как будет выглядеть дерево при вставке/удалении элемента N? Перечислите элементы полученного дерева в КЛП порядке.
2) Перечислите узлы, в которых нарушится баланс при вставке/удалении элемента N. Таких узлов может не оказаться.
3) Перечислите последовательность поворотов поддеревьев и их корень при вставке/удалении элемента N. Поворотов может и не произойти.
4) Как будет выглядеть дерево, если сначала вставить/удалить элемент N, а затем удалить/вставить элемент M? Перечислите элементы полученного дерева в КЛП порядке.
5) Какой элемент необходимо вставить(удалить) в(из) дерево(а), чтобы его каркас совпадал с тем, который изображен рядом?
*/

class QuestionGenerator {
  using AvlTreePtr = std::shared_ptr<AvlTree<char>>;
public:
  QuestionGenerator();
  ~QuestionGenerator();

  QuestionAnswer generateQA();

private:
  std::ofstream* qaFile_ = nullptr;
};

#endif // QUESTIONGENERATOR_H
