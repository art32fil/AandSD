#ifndef QUESTIONANSWER_H
#define QUESTIONANSWER_H

#include "avltree.h"
#include "icheckstrategy.h"

#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>

class QuestionAnswer {
public:
  QuestionAnswer(std::string q, std::string a,
                 std::shared_ptr<ICheckStrategy> checkStr,
                 int8_t graphNumber);
  QuestionAnswer() {}
  ~QuestionAnswer();

  // Функция проверяет, является ли правильным введенный ответ.
  // Если нет, то указывается, с какого места ответ неправильный.
  std::pair<bool, int32_t> checkAnswer(std::string userAnswer);

  std::vector<std::string> getGraphFilePath() const;

  int8_t getGraphNumber() { return graphNumber_; }

  const std::string& getQuestion() const { return question_; }
  const std::string& getAnswer() const { return answer_; }

private:
  std::string question_;
  std::string answer_;

  std::shared_ptr<ICheckStrategy> checkStrategy_ = nullptr;

  int8_t graphNumber_;
};

#endif // QUESTIONANSWER_H
