#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "documentation.h"
#include "helperfunctions.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTimer Tm;
    int interval = 1000;
    void InsertRecurse(Node *current, Node *elem);
    void RotateLeft(Node *elem);
    void RotateRight(Node *elem);
    void fixProperties(Node *elem);
    void Insert(Node *&root, Node *elem);
    void makeGgaph(Node *elem, std::string  &str, int &n);
    std::string comments ="";
    std::list<Item*> items;
    QTextBrowser *TextEdit;
    QSlider *slider = nullptr;
public:
    QPushButton *ButtonAdd = nullptr;
    QPushButton *ButtonDoc = nullptr;
    QPushButton *genration = nullptr;
    QPushButton *Clean = nullptr;

    QSpinBox *lineEdit = nullptr;
    QSpinBox *lineEditTwo = nullptr;
    int count = 0;
    int counter = 0;
    int len = 0;
    int *Arr = nullptr;
    Node *Head = nullptr;
    MainWindow(QWidget *parent = nullptr);

    QGraphicsScene *Scene;
    QGraphicsView *View;
    QWidget* CentralWidget;
    ~MainWindow();
    void update(std::string str);
    void insertElem(int x);
    void setScene();
    void showing();
public slots:
    void clean();
    void generation();
    void add();
    void documentation();

};
#endif // MAINWINDOW_H
