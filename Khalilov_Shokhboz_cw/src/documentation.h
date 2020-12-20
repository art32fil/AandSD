#ifndef DOCUMENTATION_H
#define DOCUMENTATION_H

#include "libs.h"

class Documentation : public QDialog
{
    Q_OBJECT
private:
    QPushButton *close;
    QGridLayout *grid_layout;
    QScrollArea *ScrolArea;
    QTextBrowser *info;

public:
    Documentation(QWidget *parent = 0);
    ~Documentation();
};

#endif // DOCUMENTATION_H
