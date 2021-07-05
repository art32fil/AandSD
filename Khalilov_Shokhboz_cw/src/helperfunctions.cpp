#include "helperfunctions.h"

bool isRed(Node *elem)
{
    if (elem != nullptr)
        return elem->getColor() == RED;

    return false;
}

bool isBlack(Node *elem)
{
    if (elem != nullptr){

        return elem->getColor() == BLACK;
    }

    return true;
}

Node *Parent(Node *elem)
{
    // * Обратите внимание, что для корневого узла родительский элемент имеет значение null.
    return elem == nullptr ? nullptr : elem->getParent();
}

Node *GrandParent(Node *elem)
{
    // * Обратите внимание, что он вернет nullptr, если это root или дочерний элемент root
    return Parent(Parent(elem));
}

bool isLeft(Node *elem)
{
    if (Parent(elem))
        return Parent(elem)->getLeft() == elem;

    return false;
}

bool isRight(Node *elem)
{
    if (Parent(elem))
        return Parent(elem)->getRight() == elem;
    return false;
}

Node *Brother(Node *elem){
    // * Отсутствие родителя означает отсутствие брата или сестры.
    if (Parent(elem))
    {
        if (isLeft(elem))
        {
            return Parent(elem)->getRight();
        }
        else
        {
            return Parent(elem)->getLeft();
        }
    }

    return nullptr;
}

Node *Uncle(Node *elem)
{
    //* Отсутствие родителя означает отсутствие дяди
    return Brother(Parent(elem));
}

Node *Root(Node *elem){

    Node *root = elem;
    if(root){
        while (root->getParent())
        {
            root = root->getParent();
        }
    }
    return root;
}

Node *findElem(Node *root, int key)
{
    Node *tmp = root;
    while (tmp != nullptr)
    {
        if (tmp->getValue() == key)
        {
            return tmp;
        }
        if (tmp->getValue() > key)
        {
            tmp = tmp->getLeft();
        }
        else
        {
            tmp = tmp->getRight();
        }
    }
    return nullptr;
}

void free(Node *elem){

    if( isLeaf( elem )){

        return;
    }
    if( isLeft ( elem ) ) {

        Parent(elem )->setLeft(nullptr);
    }
    else if( isRight ( elem )  )
    {
        Parent(elem)->setRight(nullptr);
    }

    delete elem;
    elem = nullptr;
}

int CountElem(Node *elem, int key){

    int l = 0, r = 0;
    if(elem->getLeft())
        l = CountElem(elem->getLeft(), key);

    if(elem->getRight())
        r = CountElem(elem->getRight(), key);

    if( elem->getValue() == key ){
        return 1+l+r;
    }
    return l+r;
}

bool isNotLeaf(Node *elem){
    return elem != nullptr;
}

bool isLeaf(Node *elem){
    return elem == nullptr;
}


//int Show(Node *elem, QGraphicsScene *Scene, int x, int y){

//    int l = 0;
//    int r = 0;
//    if(elem == nullptr){
//        return 1;
//    }
//    Scene->addItem(elem);
//    l = Show(elem->getLeft(), Scene, x-50, y+50);
//    r = Show(elem->getRight(), Scene, x+50, y+50);

//    if( isLeft( elem ) ) {

//           elem->setPos(x-r*50, y);

//    }
//    else if( isRight(elem) ){

//        elem->setPos(x+l*50, y);
//    }
//    else {
//       elem->setPos(x, y);
//    }
//    return l>r? l : r;
//}
