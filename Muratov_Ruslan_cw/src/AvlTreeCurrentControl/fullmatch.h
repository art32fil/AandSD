#ifndef FULLMATCH_H
#define FULLMATCH_H

#include <algorithm>

#include "icheckstrategy.h"

// --- Паттерн "Стратегия" ---
// --- Проверка ответа пользователя на полное совпадение с правильным ответом ---
class FullMatch : public ICheckStrategy {
public:
  FullMatch(std::string a);
  ~FullMatch() = default;

  std::pair<bool, int32_t> checkAnswer(std::string userAnswer) override;

private:
  std::string answer_;
};

#endif // FULLMATCH_H
