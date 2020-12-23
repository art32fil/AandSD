#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    srand(time(0));
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->CheckButton->setEnabled(false);
    connect(ui->Text_of_Answer,&QLineEdit::textChanged,this,[&](){
        ui->CheckButton->setEnabled(!ui->Text_of_Answer->text().isEmpty());
    });
}

MainWindow::~MainWindow(){
    if(facade!=nullptr){
        delete facade;
    }
    delete ui;
}

void MainWindow::on_Generate_Task_clicked(){
    QString str="qwertyuiopasdfghjklzxcvbnm,.!?";
    ui->Generate_Task->setEnabled(false);
    int len=rand() % 30 + 10;
    for (int i=0;i<len;i++) {
        int j = rand() % 30;
        task[i]=str[j];
    }
    curr_type=rand() % 6+1;
    facade= new Facade(task.toStdString());
    facade->CountFrequency(facade->GetTaskStr());
    facade->Sort();
    if(curr_type<4){
        facade->MakeHead();
        facade->CreateTreeByFano(facade->GetTree());
        facade->CodingByFano();
        facade->Decoding(facade->GetTree(),facade->GetTree());
    }else{
        facade->CreateHaffmanNodes();
        facade->CreateTreeByHaffman();
        facade->CodingByHaffman(facade->GetHaffman_());
        facade->CodingByFano();
        facade->Decoding(facade->GetHaffman_(),facade->GetHaffman_());
    }
    WriteTaskText();
}

void MainWindow::WriteTaskText(){
    switch (curr_type) {
    case 1:
        ui->Text_of_exersize->setText("Имеется следующее сообщение:\n   " + task
                                      +"\nТребуется закодировать его методом Фано-Шеннона\n"
                                       "и ввести закодированное сообщение\n"
                                       "Пробел, запятая, точка, а также восклицательные \nи вопросительные знаки "
                                       "тоже кодируются вместе с буквами.");
        break;
    case 2:
        ui->Text_of_exersize->setText("Имеется некоторое сообщение."
                                      "\nТребуется декодировать его методом Фано-Шеннона\nпо следующей частоте встреч:\n"
                                        + facade->BuildFrequencyStr() +
                                      "Пробел, запятая, точка, а также восклицательные \nи вопросительные знаки\n"
                                      "тоже кодируются вместе с буквами.");
        break;
    case 3:
        aim_ind = 30;
        ui->Text_of_exersize->setText("Имеется следующее сообщение:\n   " + task
                                      +"\nТребуется закодировать его методом Фано-Шеннона\n"
                                       "И ввести длину кода символа:\n  "
                                      + QString::fromStdString(facade->GetArr()[aim_ind].c) +
                                       "\nПробел, запятая, точка, а также восклицательные \nи вопросительные знаки "
                                       "тоже кодируются вместе с буквами.");
        break;
    case 4:
        ui->Text_of_exersize->setText("Имеется следующее сообщение:\n   " + task
                                      +"\nТребуется закодировать его методом Хаффмана\n"
                                       "и ввести закодированное сообщение\n"
                                       "Пробел, запятая, точка, а также восклицательные \nи вопросительные знаки "
                                       "тоже кодируются вместе с буквами.");
        break;
    case 5:
        ui->Text_of_exersize->setText("Имеется некоторое сообщение.\n"
                                      "\nТребуется декодировать его методом Хаффмана\nпо следующей частоте встреч:\n"
                                        + facade->BuildFrequencyStr() +
                                      "Пробел, запятая, точка, а также восклицательные \nи вопросительные знаки\n"
                                      "тоже кодируются вместе с буквами.");
        break;
    case 6:
        aim_ind = 30;
        ui->Text_of_exersize->setText("Имеется следующее сообщение:\n   " + task
                                      +"\nТребуется закодировать его методом Фано-Шеннона\n"
                                       "И ввести длину кода символа:\n  "
                                      + QString::fromStdString(facade->GetArr()[aim_ind].c) +
                                       "\nПробел, запятая, точка, а также восклицательные \nи вопросительные знаки "
                                       "тоже кодируются вместе с буквами.");
        break;
    }
}

void MainWindow::WriteFile(){
    file.open("QandA.txt",  std::fstream::in | std::fstream::out | std::fstream::app);
    file<<ui->Text_of_exersize->text().toStdString();
    file<<"\nAnswer:\n";
    switch (curr_type) {
        case 1:
            file<<facade->coded_str;
            break;
        case 2:
            file<<facade->decoded_str;
            break;
        case 3:
            file<<facade->GetAnswerInt();
            break;
        case 4:
            file<<facade->coded_str;
            break;
        case 5:
            file<<facade->decoded_str;
            break;
        case 6:
            file<<facade->GetAnswerInt();
            break;
    }
    file<<"\n\n";
    file.close();
}

void MainWindow::on_CheckButton_clicked(){
    switch (curr_type) {
    case 1:
        if(ui->Text_of_Answer->text()==QString::fromStdString(facade->coded_str)){
            QMessageBox::about(this,"Answer","Your answer is right!");
            ui->Generate_Task->setEnabled(true);
        }else{
            QMessageBox::about(this,"Answer","Your answer is wrong!");
        }
        break;
    case 2:
        if(ui->Text_of_Answer->text()==QString::fromStdString(facade->decoded_str)){
            QMessageBox::about(this,"Answer","Your answer is right!");
            ui->Generate_Task->setEnabled(true);
        }
        else{
            QMessageBox::about(this,"Answer","Your answer is wrong!");
        }
        break;
    case 3:
        if(ui->Text_of_Answer->text().toInt()==facade->GetAnswerInt()){
            QMessageBox::about(this,"Answer","Your answer is right!");
            ui->Generate_Task->setEnabled(true);
        }else{
            QMessageBox::about(this,"Answer","Your answer is wrong!");
        }
        break;
    case 4:
        if(ui->Text_of_Answer->text()==QString::fromStdString(facade->coded_str)){
            QMessageBox::about(this,"Answer","Your answer is right!");
            ui->Generate_Task->setEnabled(true);
        }else{
            QMessageBox::about(this,"Answer","Your answer is wrong!");
        }
        break;
    case 5:
        if(ui->Text_of_Answer->text()==QString::fromStdString(facade->decoded_str)){
            QMessageBox::about(this,"Answer","Your answer is right!");
            ui->Generate_Task->setEnabled(true);
        }
        else{
            QMessageBox::about(this,"Answer","Your answer is wrong!");
        }
        break;
    case 6:
        if(ui->Text_of_Answer->text().toInt()==facade->GetAnswerInt()){
            QMessageBox::about(this,"Answer","Your answer is right!");
            ui->Generate_Task->setEnabled(true);
        }else{
            QMessageBox::about(this,"Answer","Your answer is wrong!");
        }
        break;
    }
    WriteFile();
}

void MainWindow::on_pushButton_clicked(){
    scene->clear();
    ask = new Asklog();
    ask->show();
    connect(ask, &Asklog::myclose,this,&MainWindow::Password);
}

void MainWindow::Password(){
       if(ask->line->text() == "0990" && ui->Text_of_exersize->text()!=""){
            facade->BuildTreeFile();
            ask->close();
            item= scene->addPixmap(QPixmap("res.png"));
    }else{
        QMessageBox::about(this,"Error!","Wrong password or no generated trees!\n You cannot see a tree!");
    }
}

