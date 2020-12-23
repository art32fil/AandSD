#include "asklog.h"

Asklog::Asklog(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *ly = new QVBoxLayout();
    setFixedSize(200, 300);
    label = new QLabel("Enter a password:");
    line = new QLineEdit();
    ok= new QPushButton("&Ok",this);
    ly->addWidget(label);
    ly->addWidget(line);
    ly->addWidget(ok);
    setLayout(ly);
    connect(ok, &QPushButton::clicked, [=](){
            emit myclose();
    });
}
