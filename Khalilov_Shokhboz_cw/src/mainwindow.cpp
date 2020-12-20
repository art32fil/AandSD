#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    CentralWidget = new QWidget();
    setScene();
    setMinimumSize(800, 600);
    setCentralWidget(CentralWidget);

    ButtonAdd = new QPushButton("Add");
    ButtonDoc = new QPushButton("Documentation");
    genration = new QPushButton("Generation");
    Clean = new QPushButton("Clean");
    TextEdit = new QTextBrowser();
    TextEdit->setReadOnly(true);

    lineEdit = new QSpinBox();
    lineEditTwo = new QSpinBox();

    slider = new QSlider(this);
    slider->setTickInterval(100);
    slider->setMaximum(5000);
    slider->setMinimum(1000);
    slider->setFixedSize(60, 150);

    QHBoxLayout *main_Layout = new QHBoxLayout();
    QVBoxLayout *VBLayout = new QVBoxLayout();
    QHBoxLayout *HBLayout = new QHBoxLayout();
    QHBoxLayout *HBLayout2 = new QHBoxLayout();
    QHBoxLayout *HBLayout3 = new QHBoxLayout();

    QVBoxLayout *VBLayout2 = new QVBoxLayout();
    QHBoxLayout *HBLayout4 = new QHBoxLayout();

    ButtonAdd->setFixedSize(270, 50);
    ButtonDoc->setFixedSize(270, 50);
    genration->setFixedSize(270, 50);
    Clean->setFixedSize(270, 50);
    lineEdit->setFixedSize(270, 50);
    lineEditTwo->setFixedSize(270, 50);
    TextEdit->setFixedWidth(600);

    VBLayout2->addItem(HBLayout);
    VBLayout2->addItem(HBLayout2);
    VBLayout2->addItem(HBLayout3);
    HBLayout4->addWidget(slider);
    HBLayout4->addItem(VBLayout2);


    HBLayout->addWidget(lineEdit);
    HBLayout->addWidget(ButtonAdd);

    HBLayout2->addWidget(lineEditTwo);
    HBLayout2->addWidget(genration);

    HBLayout3->addWidget(ButtonDoc);
    HBLayout3->addWidget(Clean);

    VBLayout->addWidget(TextEdit);
    VBLayout->addItem(HBLayout4);

    HBLayout2->setContentsMargins(0, 0, 0,0);
    HBLayout->setContentsMargins(0, 0, 0,0);
    main_Layout->setContentsMargins(0, 0, 0,0);
    VBLayout->setContentsMargins(0, 0, 0,0);
    HBLayout4->setContentsMargins(0, 0, 0,0);
    VBLayout2->setContentsMargins(0, 0, 0,0);

    main_Layout->addWidget(View);
    main_Layout->addItem(VBLayout);

    showMaximized();
    connect(ButtonAdd, &QPushButton::clicked, this, &MainWindow::add);
    connect(Clean, &QPushButton::clicked, this, &MainWindow::clean);
    connect(genration, &QPushButton::clicked, this, &MainWindow::generation);
    connect(ButtonDoc, &QPushButton::clicked, this, &MainWindow::documentation);
    connect(slider, &QSlider::valueChanged, this, [&](){
        interval = slider->value();
        Tm.setInterval(interval);
    });
    View->show();
    Tm.setInterval(interval);
    connect(&Tm, &QTimer::timeout, this, [&](){
       showing();
    });
    CentralWidget->setLayout(main_Layout);
    setStyleSheet("QPushButton{                                    "
               "   background-color: #242240;                      "
               "   color: white;                                   "
               "   height: 50px;                                   "
               "   width: 300px;                                   "
               "   margin: 1px 1px;                                "
               "   border-radius: 0;                               "
               "   border: 2px;                                    "
               "   font-size: 18pt;                                "
               "}                                                  "
               "QPushButton:hover {                                "
               "   background-color: rgb(255, 69, 0);              "
               "}                     "
               "QTextBrowser{"
                  "font-size: 14pt;"
                  ""
               "}"
                  ".QSlider::groove:horizontal {"
                  "border: 1px solid #999999;"
                  "height: 8px;"
                  "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                  "margin: 2px 0;"
            "  }"
            ".QSlider::handle:horizontal {"
"                  background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
"                  border: 1px solid #5c5c5c;"
"                 width: 18px;"
"                  margin: -2px 0; "
              "   border-radius: 3px;"
              "}");

}


void MainWindow::documentation() {

    Documentation doc;
    doc.exec();
}

MainWindow::~MainWindow()
{
    if( Head ) delete Head;
    if( !items.empty() ){
        system("rm *.png");
        system("rm *.dot");
    }
}



void MainWindow::update(std::string str)
{
    int nn=0;
    std::string grap = "";
    makeGgaph(Head, grap, nn);
    std::ofstream graphic("tree.dot");
    graphic << DIGRAPH;
    graphic << NODESTYLE;
    graphic <<grap;
    graphic << ENDGRAPH;
    graphic.close();

    std::string fileName = "tree"+std::to_string(count++)+".png";
    std::string sysComand = "dot tree.dot -o "+fileName+" -Tpng";
    system(sysComand.c_str());

    items.push_back(new Item( "./"+fileName, str));
}

void MainWindow::insertElem(int x){

    if(findElem(Head, x)){
        update("<p>В структуре этот элемент [ "+ std::to_string(x) + " ] уже существует</p>\n");
        return;
    }

    update("<h3>Добавить элемент [ "+std::to_string(x)+" ]</h3>\n");

    Insert(Head, new Node( x, RED));

}



void MainWindow::showing(){

    if(counter == count ){

        Tm.stop();
        return;
    }

    std::list<Item*>::iterator it = items.begin() ;

    std::advance(it, counter++);
    QImage image(QString::fromStdString((*it)->path));
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    comments += (*it)->comment +"\n";
    Scene->clear();
    Scene->addItem(item);
    View->update();

    TextEdit->setHtml(QString::fromStdString(comments));
    TextEdit->verticalScrollBar()->setValue(TextEdit->verticalScrollBar()->maximum());
}

void MainWindow::clean()
{
    if( Head ) delete Head;
    Head = nullptr;
    comments = "";
    TextEdit->setText(QString::fromStdString(comments));
    count = 0;
    counter = 0;
    items.clear();
    Scene->clear();
    system("rm *.png");
    system("rm *.dot");
}

void MainWindow::generation()
{
    int len;
    if(lineEditTwo->value() <= 0){
        len = 10;
    }else {
        len = lineEditTwo->value();
    }
    lineEditTwo->clear();
     Tm.start();
    srand(time(0));
    for (int i = 0; i < len ; i++ ) {
         insertElem(rand()%100);
    }
}

void MainWindow::add()
{
    if(lineEdit->value() <= 0)
        return;

    int tmp = lineEdit->value();
    lineEdit->clear();
    if(findElem(Head, tmp)){
        update("<p>В структуре этот элемент [ "+ std::to_string(tmp) + " ] уже существует</p>\n");
        return;
    }
    Insert(Head, new Node(tmp, RED));
    update("<h3>Добавить элемент [ "+std::to_string(tmp)+" ]</h3>\n");
    Tm.start();
}


void MainWindow::setScene()
{
    Scene = new QGraphicsScene(CentralWidget);
    Scene->setBackgroundBrush(Qt::white);
    View = new QGraphicsView(Scene);
}

void MainWindow::InsertRecurse(Node *current, Node *elem)
{
    //? Рекурсивно спускайтесь по дереву до тех пор, пока не будет найден лист.
    if (current != nullptr)
    {
        //? если текущее значение больше чем новое значение, то слева от этого
        if (current->getValue() > elem->getValue())
        {
            //? если левая сторона узла не пуста
            if (current->getLeft() != nullptr)
            {
                //* Рекурсивно спускаться влево-вниз
                InsertRecurse(current->getLeft(), elem);

                return;
            }

            //? если левая сторона узла пуста
            //* присваивать значение на левом узле
            current->setLeft(elem);


        }
        else //? если текущее значение меньше чем новое значение, то справа от этого
        {
            //? если правая сторона узла не пуста
            if (current->getRight() != nullptr)
            {
                //* Рекурсивно спускаться право-вниз
                InsertRecurse(current->getRight(), elem);


                return;
            }

            //? если правая сторона узла пуста
            //* присваивать значение на правом узле
            current->setRight(elem);


        }
    }
    //* сделать текущий элемент родительским для нового элемента
    elem->setParent(current);


}

void MainWindow::fixProperties(Node *elem)
{
    std::string comment ="";

    if (!Parent(elem))
    {
        comment = "<h4>[ см. Случай 1 ]</h4>";
        comment +="<p>Элемент [ "+ std::to_string(elem->getValue()) + " ] стал корнем дерева</p>";
        update(comment);
        elem->setColor(BLACK);
        return;
    }
    else if (isBlack(Parent(elem)))
    {
        comment = "<h4>[ см. Случай 2 ]</h4>";
        comment +="<p>У элемента [ "+ std::to_string(elem->getValue()) + " ] родитель [ "+std::to_string(Parent(elem)->getValue()) +" ] чёрный, "
       "поэтому ничего не меняется, так как свойство не нарушается</p>";
        update(comment);
        return;
    }
    else if (Uncle(elem) != nullptr && isRed(Uncle(elem)))
    {
        comment = "<h4>[ см. Случай 3 ]</h4>";
        comment += "<p>У элемента [ "+ std::to_string(elem->getValue()) + " ] родитель [ "+std::to_string(Parent(elem)->getValue()) +" ] красный, есть дядя [ "+std::to_string(Uncle(elem)->getValue()) +" ] и он тоже красный "
"Поэтому родитель [ "+std::to_string(Parent(elem)->getValue()) +" ] и дядя [ "+std::to_string(Uncle(elem)->getValue()) +" ] окрашиваются в черный, а дедушка [ "+std::to_string(GrandParent(elem)->getValue()) +" ] "
"становится красным и вызывается повторная проверка с дедушкой</p>";

        update(comment);

        Parent(elem)->setColor(BLACK);
        Uncle(elem)->setColor(BLACK);
        GrandParent(elem)->setColor(RED);
        fixProperties(GrandParent(elem));

        return;
    }
    else if (isRight(elem) && isLeft(Parent(elem)))
    {
        comment = "<h4>[ см. Случай 4 ]</h4>";
        comment += "<p>Элемент [ "+ std::to_string(elem->getValue()) + " ] является левым, а родитель [ "+std::to_string(Parent(elem)->getValue()) +" ] является\n"
"правым элементом, поэтому делаем поворот направо вокруг родителя [ "+std::to_string(Parent(elem)->getValue()) +" ]</p>";

        update(comment);

        RotateLeft(Parent(elem));
        elem = elem->getLeft();

    }
    else if (isLeft(elem) && isRight(Parent(elem)))
    {
        comment = "<h4>[ см. Случай 4 ]</h4>";
        comment +="<p>Элемент [ "+ std::to_string(elem->getValue()) + " ] является правым, а родитель [ "+std::to_string(Parent(elem)->getValue()) +" ] является "
"левым элементом, поэтому делаться поворот налево вокруг родителя [ "+std::to_string(Parent(elem)->getValue()) +" ]</p>";

update(comment);
        RotateRight(Parent(elem));
        elem = elem->getRight();
    }

    comment = "<h4>[ см. Случай 5 ]</h4>";
    comment +="<p>Родитель [ "+std::to_string(Parent(elem)->getValue()) +" ] элемента [ "+std::to_string(elem->getValue()) + " ], окрашивается в черный, а дедушка [ "+std::to_string(GrandParent(elem)->getValue()) +" ] в красный</p>";

    update(comment);
    Parent(elem)->setColor(BLACK);
    GrandParent(elem)->setColor(RED);

    if (isLeft(elem) && isLeft(Parent(elem)))
    {
        comment ="<p>Элемент [ "+ std::to_string(elem->getValue()) + " ] является левым узлом. Родитель [ "+std::to_string(elem->getValue()) + " ] также является левым узлом, поэтому делаться поворот направо вокруг дедушки [ "+std::to_string(GrandParent(elem)->getValue()) +" ]</p>";

        RotateRight(GrandParent(elem));
    }
    else
    {
        comment ="<p>Элемент [ "+ std::to_string(elem->getValue()) + " ] является правым узлом. Родитель [ "+std::to_string(elem->getValue()) + " ] также является правым узлом, поэтому делаться поворот налево вокруг дедушки [ "+std::to_string(GrandParent(elem)->getValue()) +" ]</p>";

        RotateLeft(GrandParent(elem));
    }
}

void MainWindow::Insert(Node *&root, Node *elem)
{
    //* Вставить новый узел в текущее дерево.
    InsertRecurse(root, elem);

    //* Восстановите дерево в случае нарушения какого-либо из красно-черных свойств.
    fixProperties(elem);
    //* Найти новый корень для возврата.
    root = elem;
    while (root->getParent())
    {
        root = root->getParent();
    }
}

void MainWindow::makeGgaph(Node *elem, std::string &str, int &n){

    if( elem == nullptr ){
         str += "n"+std::to_string(n)+NILL;
         return;
    }
    if(isRed(elem)){
        str += std::to_string(elem->getValue())+REDTREE;
    }
    else {
        str += std::to_string(elem->getValue())+BLACKTREE;
    }

    if(isNotLeaf(elem->getLeft())){

        str += std::to_string(elem->getValue())+" -> "+std::to_string(elem->getLeft()->getValue())+"\n";
        makeGgaph(elem->getLeft(), str, n);
    }
    else{
        n++;
        str += std::to_string(elem->getValue())+" -> n"+std::to_string(n)+"\n";
        str += "n"+std::to_string(n)+NILL;
    }

    if( isNotLeaf(elem->getRight()) ){
       str += std::to_string(elem->getValue())+" -> "+std::to_string(elem->getRight()->getValue())+"\n";
        makeGgaph(elem->getRight(), str, n);
    }
    else{
        n++;
        str += std::to_string(elem->getValue())+" -> n"+std::to_string(n)+"\n";
        str +="n"+ std::to_string(n)+NILL;
    }
}


void MainWindow::RotateLeft(Node *elem)
{
    std::string comment = "<h4>[ поворот налево ] по элементу [ "+std::to_string( elem->getValue()) +" ]</h4>"
                                                                                                     "<h3>[ см. Повернуть влево ]</h3>";
    update(comment);
    Node *Son = elem->getRight();
    Node *parent = Parent(elem );
    Son->setParent( parent ); //* при этом, возможно, Son становится корнем дерева

    if ( parent )
    {
        if (isLeft(elem))
        {
            parent->setLeft( Son );
        }
        else
        {
            parent->setRight( Son );
        }
    }

    elem->setRight( Son->getLeft() );
    if (Son->getLeft())
    {
        Son->getLeft()->setParent( elem );
    }
    elem->setParent( Son );
    Son->setLeft( elem );
}

void MainWindow::RotateRight(Node *elem)
{

    std::string comment = "<h4>[ поворот направо ] по элементу [ "+std::to_string( elem->getValue()) +" ]</h4>"
                                                                                                "<h3>[ см. Повернуть влево ]</h3>";;
    Node *Son = elem->getLeft();
    Node *parent = Parent(elem );
    update(comment);
    Son->setParent( parent ); //* при этом, возможно, Son становится корнем дерева

    if (parent)
    {
        if (isLeft(elem))
        {
            parent->setLeft( Son );
        }
        else
        {
            parent->setRight( Son );
        }
    }
    elem->setLeft( Son->getRight() );
    if ( Son->getRight() ){
        Son->getRight()->setParent( elem );
    }
    elem->setParent( Son );
    Son->setRight( elem );
}
