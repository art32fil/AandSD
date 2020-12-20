#ifndef CURRENTCONTROL_H
#define CURRENTCONTROL_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QKeyEvent>
#include <QDebug>

#include <memory>
#include <algorithm>
#include <cctype>

#include "questiongenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CurrentControl; }
QT_END_NAMESPACE

class CurrentControl : public QMainWindow {
  Q_OBJECT

  using QuestionGeneratorPtr = std::shared_ptr<QuestionGenerator>;
  using QuestionAnswerPtr = std::shared_ptr<QuestionAnswer>;
  using PixmapPtr = std::shared_ptr<QPixmap>;
  using GraphicsItemPtr = std::shared_ptr<QGraphicsItem>;
public:
  CurrentControl(QWidget *parent = nullptr);
  ~CurrentControl();

  void keyPressEvent(QKeyEvent* event) override;

public slots:
  void newQuestion();
  void checkAnswer();

private:
  Ui::CurrentControl *ui;

  QGraphicsScene* gscene_ = new QGraphicsScene(this);
  PixmapPtr pixmap_ = nullptr;
  PixmapPtr pixmapFrame_ = nullptr;

  GraphicsItemPtr gitem_ = nullptr;
  GraphicsItemPtr gitemFrame_ = nullptr;

  QLabel* answerStatus_ = new QLabel("", nullptr);

  QuestionGeneratorPtr questionGen_ = std::make_shared<QuestionGenerator>();
  QuestionAnswerPtr qa_ = nullptr;
};
#endif // CURRENTCONTROL_H
