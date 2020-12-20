#include "oneof.h"

OneOf::OneOf(std::string a)
  : answer_(a) {}

std::pair<bool, int32_t> OneOf::checkAnswer(std::string userAnswer) {
  // Удаление пробельных символов
  userAnswer.erase(std::remove(userAnswer.begin(), userAnswer.end(), ' '), userAnswer.end());

  // Правильный ли ответ (второй параметр всегда равен 0)
  std::pair<bool, int32_t> correctness;
  correctness.second = 0;

  // Учитывается только первый символ введенной пользователем строки
  correctness.first = (answer_.find(userAnswer[0]) != std::string::npos);

  return correctness;
}
