#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <ctime>
#include "treap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void BuildTree();
    ~MainWindow();
public slots:
    /*
     * GenerateTask method
     * Generates a condition for the current task
     */
    void GenerateTask();

    /*
     * CheckAnswer method
     * Checks the answer entered by the user and the correct answer
     */
    void CheckAnswer();


private:
    Ui::MainWindow *ui; //main form with buttons
    QGraphicsScene* scene; //main scene where treap displayed
    QGraphicsPixmapItem* item; //a treap pixmap
    Treap* tree = nullptr;
    int n = 0;
    int prior = 0;
};
#endif // MAINWINDOW_H
