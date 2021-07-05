//! 1
//* Каждый узел промаркирован красным или чёрным цветом
//! 2
//* Корень и конечные узлы (листья) дерева - чёрные
//! 3
//* У красного узла родительский узел - черный
//! 4
//* Все простые пути из любого узла х до листьев содержат одинокавое количества чёрных узлов
//! 5
//* Чёрный узел может иметь чёрного родителя


#ifndef NODE_HPP
#define NODE_HPP
#include "libs.h"

#define DIGRAPH "digraph G {\n"
#define ENDGRAPH "\n}"
#define BLACKTREE  " [ shape = circle, style=filled, fillcolor=black];\n"
#define REDTREE " [ shape = circle, style=filled, fillcolor=red];\n"
#define CURRENTTREE " [ shape = doublecircle, style=filled, color = blue, fillcolor=red];\n"
#define NILL " [shape = square, style=filled, fillcolor=black ];\n"
#define NODESTYLE "node[ color = white, fontcolor=white];\n";

#define RED Qt::red
#define BLACK Qt::black



struct Item {

    std::string path;
    std::string comment;
    Item(std::string p, std::string c):path(p), comment(c){}
};


class Node : public QGraphicsEllipseItem
{
private:
    int value;
    QColor color = RED;
    Node *parent;
    Node *left;
    Node *right;
public:
    Node(int val, QColor cl): value(val), color(cl){

        parent = left = right = nullptr;
        setRect(0, 0, 50, 50);
    }
    Node *getParent() const;
    void setParent(Node *value);

    Node *getLeft() const;
    void setLeft(Node *value);

    Node *getRight() const;
    void setRight(Node *value);

    QColor getColor() const;
    void setColor(const QColor &value);

    int getValue() const;
    void setValue(int value);

    ~Node(){
        if( left) delete left;
        if( right ) delete right;
    }
};




#endif // NODE_HPP
