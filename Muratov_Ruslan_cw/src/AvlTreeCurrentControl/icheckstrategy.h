#ifndef ICHECKSTRATEGY_H
#define ICHECKSTRATEGY_H

#include <string>

// --- Интерфейс для паттерна "Стратегия" ---
class ICheckStrategy {
public:
  virtual ~ICheckStrategy() = default;

  // Функция проверяет, является ли правильным введенный ответ.
  // Если нет, то указывается, с какого места ответ неправильный.
  virtual std::pair<bool, int32_t> checkAnswer(std::string userAnswer) = 0;
};

#endif // ICHECKSTRATEGY_H
