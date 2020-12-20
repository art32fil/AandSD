#include "currentcontrol.h"
#include "ui_currentcontrol.h"

CurrentControl::CurrentControl(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::CurrentControl) {
  ui->setupUi(this);

  this->showMaximized();

  ui->graphicsView->setScene(gscene_);

  ui->statusbar->addWidget(answerStatus_);

  connect(ui->checkButton, &QPushButton::clicked,
          this, &CurrentControl::checkAnswer);
  connect(ui->nextQuestionBtn, &QPushButton::clicked,
          this, &CurrentControl::newQuestion);

  newQuestion();
}

CurrentControl::~CurrentControl() {
  delete ui;
}

void CurrentControl::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Return) {
    ui->checkButton->click();
  }
}


void CurrentControl::newQuestion() {
  qa_ = std::make_shared<QuestionAnswer>(questionGen_->generateQA());

  // Нельзя перейти к следующему вопросу, пока нет правильного ответа на текущий
  ui->nextQuestionBtn->setEnabled(false);

  // Публикация вопроса
  ui->questionLabel->setText(qa_->getQuestion().c_str());

  // Возвращение к начальным значениям
  ui->answer->clear();
  answerStatus_->setText("");

  // Удаление изображения прошлого графа
  if (gitem_) {
    gscene_->removeItem(gitem_.get());
  }

  // Удаление изображения каркаса
  if (gitemFrame_) {
    gscene_->removeItem(gitemFrame_.get());
    gitemFrame_ = nullptr;
  }

  // Создание изображения нового графа
  pixmap_ = std::make_shared<QPixmap>(qa_->getGraphFilePath()[0].c_str());
  gitem_ = GraphicsItemPtr(gscene_->addPixmap(*pixmap_));

  switch (qa_->getGraphNumber()) {
  case 1: {
    gscene_->setSceneRect(0, 0, pixmap_->width(), pixmap_->height());
    // this->resize(2 * pixmap_->width(), 2 * pixmap_->height());
    break;
  }
  case 2: {
    pixmapFrame_ = std::make_shared<QPixmap>(qa_->getGraphFilePath()[1].c_str());
    gitemFrame_ = GraphicsItemPtr(gscene_->addPixmap(*pixmapFrame_));
    gitemFrame_->setPos(gitem_->pos() + QPointF(pixmap_->width() + 20, 0));
    gscene_->setSceneRect(0, 0, pixmap_->width() + pixmapFrame_->width() + 20, std::max(pixmap_->height(), pixmapFrame_->height()));
    // this->resize(pixmap_->width() + pixmapFrame_->width() + 100, pixmap_->height() + pixmapFrame_->height());
    break;
  }
  }
}

void CurrentControl::checkAnswer() {
  // Удаление старого статуса ответа
  answerStatus_->setText("");

  // Ответ, введенный пользователем
  std::string userAnswer = ui->answer->text().toStdString();

  // Проверка ответа
  auto status = qa_->checkAnswer(ui->answer->text().toStdString());
  if (!status.first) {
    answerStatus_->setText(QString::fromStdString("Ответ неверный: правильная часть Вашего ответа \"" + userAnswer.substr(0, status.second) + "\""));
  } else {
    // Можно переходить к следующему вопросу
    ui->nextQuestionBtn->setEnabled(true);
    answerStatus_->setText("Ответ правильный!");
  }
  // qDebug() <<  __PRETTY_FUNCTION__ << "status.first = " << status.first;
}

