#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scaledpixmap.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel* text;
    ScaledPixmap* Image_widget;
    int image_width = 476;
    int image_height = 476;
    bool isDecoding = false;
    bool isCoding = false;
    bool isCodeMaking = true;

    QString algorithm;
    string line;
    string symbols;
    int* freq = nullptr;
    string* cipher = nullptr;
    int symbols_count = 0;
    QString codedMessage;
    QString decodedMessage;

    void readFile(const char*);
    void startCoding();
    void stringAnalys();
    void stringSort();
    void stringSort(int, int*, string*);
    void searchTreeFanoShenon(char, string &, int, int, QString&, int&, int, QString&);
    bool searchTreeHaffman(int, QString&, QString&);
    bool stringCoder();
    bool stringDecoder();

    void loadFile();
    void loadImage();
    void stringCheck();
    void isCloseCheck();
    void closeProgramm();
    void fullsize_decorator();
    void decorator();
    void checkClick();
    void checkFastClick();
    void inputText();
};
#endif // MAINWINDOW_H
