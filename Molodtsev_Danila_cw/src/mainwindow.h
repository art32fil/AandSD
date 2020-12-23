#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libs.h"
#include "facade.h"
#include "asklog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void WriteTaskText(); //method writes text of task to label
    void WriteFile();	//method writes task and answer to file
    void VizualizeTree();	//method calls dot and pace picture to QGraphicsScene
    ~MainWindow();

private slots:
    void on_Generate_Task_clicked(); //method generates task
    void Password();	//slot that checks password
    void on_CheckButton_clicked(); //slot checks answer

    void on_pushButton_clicked();	//slot starts dialog window which asks password

private:
    Ui::MainWindow *ui;	//qt form
    Asklog* ask;	//dialog window
    std::fstream file;	//file which contains questions and answers
    Facade* facade=nullptr;
    QString task="";	//string of generated task
    QGraphicsScene* scene;	//pointer to Graphics scene
    QGraphicsPixmapItem* item=nullptr;	//picture of tree
    int aim_ind=-1;		//integer answer
    int curr_type=0;	//type of generated task
};

#endif // MAINWINDOW_H
