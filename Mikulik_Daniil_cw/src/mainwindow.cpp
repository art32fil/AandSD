#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->checkButton, SIGNAL(clicked()), this, SLOT(GenerateTask()));
    connect(ui->checkAnswerButton, SIGNAL(clicked()), this, SLOT(CheckAnswer()));
}

void MainWindow::GenerateTask(){
    std::fstream fs;
    fs.open("conditions.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    BuildTree();
    QString line("Задача: \n");
    int type = rand()%2;
    if (type){
        line += "Пусть дано некоторое декартово дерево.\n";
        line += "Из заданного дерева удаляется элемент ";
        line += QString::number(n);
        line += ".\n";
        line += "Требуется вывести новое дерево, полученное в результате удаления из него элемента ";
        line += QString::number(n);
        line += ".\n";
        line += "Дерево вводится по следующему принципу:\nсначала вводится номер вершины-корня,\n затем поочередно вершины сначала 2 уровня, потом третьего и т.д.\n";
        line += "Номера вершин одного уровня выводятся в порядке слева направо.\n";
        line += "В любом случае результатом будет строка,\n которая описывает получившееся бинарное дерево.\n";
        fs << "Дано дерево: \n";
        fs << tree->printFile();
        tree->remove(n);
    }
    else{
        line += "Пусть дано некоторое декартово дерево.\n";
        line += "В заданное дерево вставляется элемент ";
        fs << "Дано дерево: \n";
        fs << tree->printFile();
        n = rand()%(tree->size + 1) + (tree->size * tree->size);
        tree->insert(n);
        prior = tree->findElem(n);
        line += QString::number(n) + "," + QString::number(prior);
        line += ".\n";
        line += "Требуется вывести новое дерево, полученное в результате вставки в него элемента ";
        line += QString::number(n);
        line += ".\n";
        line += "Дерево вводится по следующему принципу:\nсначала вводится номер вершины-корня,\n затем поочередно вершины сначала 2 уровня, потом третьего и т.д.\n";
        line += "Номера вершин одного уровня выводятся в порядке слева направо.\n";
        //line += "Все недостающие вершины на уровне требуется обозначить исмолом #.\n";
        line += "В любом случае результатом будет строка,\n которая описывает получившееся бинарное дерево.\n";
    }
    fs << "Task condition:\n";
    fs << line.toUtf8().toStdString();
    fs << "Correct answer:\n";
    cout << tree->correctAnswer() << endl;
    fs << tree->correctAnswer() << "\n";
    ui->taskLabel->setText(line);
}

void MainWindow::BuildTree()
{
    if(tree)
        delete tree;
    srand(time(NULL));
    tree = new Treap;
    std::pair<int, int> ans = tree->read();
    n = ans.first;
    prior = ans.second;
    tree->print();
    tree->visualize();
    ui->view->setScene(scene);
    ui->view->setRenderHint(QPainter::Antialiasing);

    scene->clear();

    item = scene->addPixmap(QPixmap("res.png"));
}

void MainWindow::CheckAnswer(){
    if (tree){
        std::string answer = (ui->lineEdit->text()).toStdString();
        std::string correctAnswer = tree->correctAnswer();
        QMessageBox* msg = new QMessageBox(this);
        if (answer == correctAnswer){
            msg->setText("Your answer is right!");
            ui->view->setScene(scene);
            ui->view->setRenderHint(QPainter::Antialiasing);
            scene->clear();
            tree->visualize();
            item = scene->addPixmap(QPixmap("res.png"));
        }
        else{
            msg->setText("Your answer is incorrect!");
        }
        msg->exec();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

