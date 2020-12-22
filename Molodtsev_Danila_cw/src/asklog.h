#ifndef ASKLOG_H
#define ASKLOG_H
#include "libs.h"

class Asklog : public QWidget{
    Q_OBJECT
public:
    explicit  Asklog(QWidget *parent = nullptr);
    QLineEdit* line;
    QLabel* label;
    QPushButton* ok;
signals:
    void myclose();
};

#endif // ASKLOG_H
