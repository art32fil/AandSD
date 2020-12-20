#include "questionanswer.h"

QuestionAnswer::QuestionAnswer(std::string q, std::string a,
                               std::shared_ptr<ICheckStrategy> checkStr,
                               int8_t graphNumber)
    : question_(q),
      answer_(a),
      checkStrategy_(checkStr),
      graphNumber_(graphNumber) {}

QuestionAnswer::~QuestionAnswer() {}

std::pair<bool, int32_t> QuestionAnswer::checkAnswer(std::string userAnswer) {
  return checkStrategy_->checkAnswer(userAnswer);
}

std::vector<std::string> QuestionAnswer::getGraphFilePath() const {
  std::vector<std::string> paths;

  // Создание изображения для первого графа
  std::system("Graphviz\\bin\\dot -Tpng -o graph.png graph.gv");
  paths.push_back("graph.png");

  if (graphNumber_ == 2) {
    std::system("Graphviz\\bin\\dot -Tpng -o graph_frame.png graph_frame.gv");
    paths.push_back("graph_frame.png");
  }
  return paths;
}

