#include "fullmatch.h"

FullMatch::FullMatch(std::string a)
  : answer_(a) {}

std::pair<bool, int32_t> FullMatch::checkAnswer(std::string userAnswer) {
  // Удаление пробельных символов
  userAnswer.erase(std::remove(userAnswer.begin(), userAnswer.end(), ' '), userAnswer.end());

  // Правильная ли строка и индекс, начиная с которого строка является неправильной
  std::pair<bool, int32_t> correctness;

  correctness.first = userAnswer == answer_;
  if (!correctness.first) {
    if (userAnswer.length() > answer_.length()) {
      const auto& mismatchPos = std::mismatch(answer_.begin(), answer_.end(), userAnswer.begin());
      correctness.second = mismatchPos.first - answer_.begin();
    } else {
      const auto& mismatchPos = std::mismatch(userAnswer.begin(), userAnswer.end(), answer_.begin());
      correctness.second = mismatchPos.second - answer_.begin();
    }
  }
  return correctness;
}
