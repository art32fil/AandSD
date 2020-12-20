#include "questiongenerator.h"

QuestionGenerator::QuestionGenerator() {
  // Инициализировать генератор текущим временем
  std::srand(std::time(nullptr));

  // Файл, в котором будут хранится вопросы и ответы
  qaFile_ = new std::ofstream("./qa.txt");
}

QuestionGenerator::~QuestionGenerator() {
  if (qaFile_->is_open())
    qaFile_->close();
  delete qaFile_;
}

QuestionAnswer QuestionGenerator::generateQA() {

  // Создание дерева для вопроса
  AvlTree<char> avlTree;

  // Элементы дерева, которые в нем имеются
  std::vector<bool> elems(26);

  // Количество элементов в дереве выбирается рандомно (от 5 до 15)
  int n = 5 + rand() % 11;
  // Сгенерированный символ
  char c;
  for (int i = 0; i < n; ++i) {
    do { // Если элемент уже есть в дереве, то выбираем другой
      c = (97 + rand() % 25);
    } while (elems[c - 97]);
    elems[c - 97] = true;
    avlTree.insert(c);
  }

  // Создание файла с описанием графа
  std::fstream dotFile("./graph.gv", std::ios_base::out);

  // Сохранение исходного дерева в файл
  avlTree.printDot(dotFile);
  dotFile.close();

  // Дерево, которое будет получено после выполнения операции
  AvlTree<char> avlTreeNext(avlTree);

  // Вставляемый элемент
  char insertElem;
  do { // Если элемент уже есть в дереве, то выбираем другой
    insertElem = (97 + rand() % 25);
  } while (elems[insertElem - 97]);

  // Удаляемый элемент (из тех, которые имеются в дереве)
  char removeElem;
  do { // Если элемента нет в дереве, то выбираем другой
    removeElem = (97 + rand() % 25);
  } while (!elems[removeElem - 97]);

  // Объект, в котором будет храниться формулировка вопроса и ответ на него
  QuestionAnswer qa;

  // Строки с вопросом и ответом
  std::string question;
  std::string answer;

  // Рандомно выбирается тип вопроса (10 типов вопросов)
  switch (rand() % 10 + 1) {
  // Как будет выглядеть дерево при вставке элемента N?
  case 1: {
    avlTreeNext.insert(insertElem);

    // Формулировка вопроса
    question = "Как будет выглядеть дерево при вставке \'";
    question += insertElem;
    question += "\'?\nПеречислите элементы полученного дерева в КЛП-порядке.";

    // Формирование ответа
    for (auto& e : avlTreeNext.getPrefixOrder())
      answer += e;
    qa = QuestionAnswer(question, answer,
                        std::make_shared<FullMatch>(answer), 1);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево:\n";
    avlTree.printToFile(*qaFile_);

    break;
  }
  // Как будет выглядеть дерево при удалении элемента N?
  // Перечислите элементы полученного дерева в КЛП-порядке
  case 2: {
    avlTreeNext.remove(removeElem);

    // Формулировка вопроса
    question = "Как будет выглядеть дерево при удалении \'";
    question += removeElem;
    question += "\'?\nПеречислите элементы полученного дерева в КЛП-порядке.";

    // Формирование ответа
    for (auto& e : avlTreeNext.getPrefixOrder())
      answer += e;
    qa = QuestionAnswer(question, answer,
                        std::make_shared<FullMatch>(answer), 1);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево:\n";
    avlTree.printToFile(*qaFile_);

    break;
  }
  // Перечислите узлы, в которых нарушится баланс при вставке элемента N.
  case 3: {
    avlTreeNext.insert(insertElem);

    // Формулировка вопроса
    question = "Перечислите узлы, в которых нарушится баланс при вставке элемента \'";
    question += insertElem;
    question += "\'?\nУкажите эти элементы в порядке возрастания. (Таких элементов может не оказаться)";

    // Формирование ответа
    auto lbn = avlTreeNext.getLastBalancedNodes();
    std::sort(lbn.begin(), lbn.end());

    for (auto& elem : lbn)
      answer.push_back(elem);

    qa = QuestionAnswer(question, answer,
                        std::make_shared<FullMatch>(answer), 1);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево:\n";
    avlTree.printToFile(*qaFile_);

    break;
  }
  // Перечислите узлы, в которых нарушится баланс при удалении элемента N.
  case 4: {
    avlTreeNext.remove(removeElem);

    // Формулировка вопроса
    question = "Перечислите узлы, в которых нарушится баланс при удалении элемента \'";
    question += removeElem;
    question += "\'?\nУкажите эти элементы в порядке возрастания. (Таких элементов может не оказаться)";

    // Формирование ответа
    auto lbn = avlTreeNext.getLastBalancedNodes();
    std::sort(lbn.begin(), lbn.end());

    for (auto& elem : lbn)
      answer.push_back(elem);

    qa = QuestionAnswer(question, answer,
                        std::make_shared<FullMatch>(answer), 1);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево:\n";
    avlTree.printToFile(*qaFile_);

    break;
  }
  // Перечислите в хронологическом порядке последовательность вращений поддеревьев и их корень при вставке элемента N.
  // Причемание: вращении может и не быть.
  case 5: {
    avlTreeNext.insert(insertElem);

    // Формулировка вопроса
    question = "Перечислите в хронологическом порядке последовательность вращений поддеревьев и их корень при вставке \'";
    question += insertElem;
    question += "\'.\nФормат ответа: направление_вращения (l или r) корень.\n"
                "Например, если произошел большой поворот налево вокруг узла p (q - его правый сын), то необходимо написать: r q l p.\n"
                "Примечание: вращений может и не быть";

    // Формирование ответа
    for (auto& p : avlTreeNext.getLastRotations()) {
      answer.push_back(p.first);
      answer.push_back(p.second);
    }
    qa = QuestionAnswer(question, answer,
                        std::make_shared<FullMatch>(answer), 1);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево:\n";
    avlTree.printToFile(*qaFile_);

    break;
  }
  // Перечислите в хронологическом порядке последовательность вращений поддеревьев и их корень при удалении элемента N.
  // Причемание: вращении может и не быть.
  case 6: {
    avlTreeNext.remove(removeElem);

    // Формулировка вопроса
    question = "Перечислите в хронологическом порядке последовательность вращений поддеревьев и их корень при удалении \'";
    question += removeElem;
    question += "\'.\nФормат ответа: направление_вращения (l или r) корень.\n"
                "Например, если произошел большой поворот налево вокруг узла p (q - его правый сын), то необходимо написать: r q l p.\n"
                "Примечание: вращений может и не быть";

    // Формирование ответа
    for (auto& p : avlTreeNext.getLastRotations()) {
      answer.push_back(p.first);
      answer.push_back(p.second);
    }
    qa = QuestionAnswer(question, answer,
                        std::make_shared<FullMatch>(answer), 1);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево:\n";
    avlTree.printToFile(*qaFile_);

    break;
  }
  // Как будет выглядеть дерево, если сначала вставить элемент N, а затем удалить элемент M?
  // Перечислите элементы полученного дерева в КЛП-порядке.
  case 7: {
    avlTree.insert(insertElem);
    avlTree.remove(removeElem);

    // Формулировка вопроса
    question = "Как будет выглядеть дерево, если сначала вставить \'";
    question += insertElem;
    question += "\', а затем удалить \'";
    question += removeElem;
    question += "\'?\nПеречислите элементы полученного дерева в КЛП-порядке.";

    // Формирование ответа
    for (auto& e : avlTreeNext.getPrefixOrder())
      answer += e;
    qa = QuestionAnswer(question, answer,
                        std::make_shared<FullMatch>(answer), 1);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево:\n";
    avlTree.printToFile(*qaFile_);

    break;
  }
  // Как будет выглядеть дерево, если сначала удалить элемент N, а затем вставить элемент M?
  // Перечислите элементы полученного дерева в КЛП-порядке.
  case 8: {
    avlTree.remove(removeElem);
    avlTree.insert(insertElem);

    // Формулировка вопроса
    question = "Как будет выглядеть дерево, если сначала удалить \'";
    question += removeElem;
    question += "\', а затем вставить \'";
    question += insertElem;
    question += "\'?\nПеречислите элементы полученного дерева в КЛП-порядке.";

    // Формирование ответа
    for (auto& e : avlTreeNext.getPrefixOrder())
      answer += e;
    qa = QuestionAnswer(question, answer,
                        std::make_shared<FullMatch>(answer), 1);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево:\n";
    avlTree.printToFile(*qaFile_);

    break;
  }
  // Какой элемент необходимо вставить в дерево, чтобы его каркас совпадал с тем, который изображен рядом?
  // Если несколько возможных элементов, введите любой из них (один элемент).
  case 9: {
    // Создание файла с описанием каркаса графа
    std::fstream frameDotFile("./graph_frame.gv", std::ios_base::out);

    AvlTree<char> avlTreeFrame(avlTree);
    avlTreeFrame.insert(insertElem);

    elems[insertElem - 97] = true;

    // Сохранение каркаса нового дерева в файл
    avlTreeFrame.printFrameDot(frameDotFile);
    frameDotFile.close();

    // Формулировка вопроса
    question = "Какой элемент необходимо вставить в дерево, чтобы его каркас совпадал с тем, который изображен рядом?\n"
               "Если несколько возможных элементов, введите любой из них (один элемент).";

    // Формирование ответа
    answer.push_back(insertElem);

    for (char c = 'a'; c <= 'z'; ++c) {
      if (!elems[c - 97]) {
        avlTreeNext.insert(c);
        elems[c - 97] = true;

        // Если при вставке элемента получается дерево с тем же каркасом, то запоминаем его
        if (avlTreeFrame.haveSameFrame(avlTreeNext))
          answer.push_back(c);

        // Возвращение исходного дерева
        avlTreeNext = avlTree;
      }
    }

    qa = QuestionAnswer(question, answer,
                        std::make_shared<OneOf>(answer), 2);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево и его каркас после некоторой операции:\n";
    avlTree.printToFile(*qaFile_);
    avlTreeFrame.printFrameToFile(*qaFile_);

    break;
  }
  // Какой элемент необходимо удалить из дерева, чтобы его каркас совпадал с тем, который изображен рядом?
  // Если несколько возможных элементов, введите любой из них (один элемент).
  case 10: {
    // Создание файла с описанием каркаса графа
    std::fstream frameDotFile("./graph_frame.gv", std::ios_base::out);

    AvlTree<char> avlTreeFrame(avlTree);
    avlTreeFrame.remove(removeElem);

    elems[removeElem - 97] = false;

    // Сохранение каркаса нового дерева в файл
    avlTreeFrame.printFrameDot(frameDotFile);
    frameDotFile.close();

    // Формулировка вопроса
    question = "Какой элемент необходимо удалить из дерева, чтобы его каркас совпадал с тем, который изображен рядом?\n"
               "Если несколько возможных элементов, введите любой из них (один элемент).";

    // Формирование ответа
    answer.push_back(removeElem);

    for (char c = 'a'; c <= 'z'; ++c) {
      if (elems[c - 97]) {
        avlTreeNext.remove(c);
        elems[c - 97] = false;

        // Если при удалении элемента получается дерево с тем же каркасом, то запоминаем его
        if (avlTreeFrame.haveSameFrame(avlTreeNext))
          answer.push_back(c);

        // Возвращение исходного дерева
        avlTreeNext = avlTree;
      }
    }

    qa = QuestionAnswer(question, answer,
                        std::make_shared<OneOf>(answer), 2);

    // Запись условия вопроса
    *qaFile_ << "Дано АВЛ-дерево и его каркас после некоторой операции:\n";
    avlTree.printToFile(*qaFile_);
    avlTreeFrame.printFrameToFile(*qaFile_);

    break;
  }
  }

  // Запись вопроса и ответа в файл
  *qaFile_ << "Q: " << question << std::endl;
  *qaFile_ << "A: " << answer << '\n' << std::endl;

  qDebug() << "Question: " << qa.getQuestion().c_str();
  qDebug() << "Answer:" << qa.getAnswer().c_str();

  return qa;
}
