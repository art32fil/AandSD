#ifndef ONEOF_H
#define ONEOF_H

#include <algorithm>

#include "icheckstrategy.h"

// --- Паттерн "Стратегия" ---
// --- Проверка ответа пользователя на вхождение в набор правильных ответов ---
class OneOf : public ICheckStrategy {
public:
  OneOf(std::string a);
  ~OneOf() = default;

  std::pair<bool, int32_t> checkAnswer(std::string userAnswer) override;

private:
  std::string answer_;
};

#endif // ONEOF_H
