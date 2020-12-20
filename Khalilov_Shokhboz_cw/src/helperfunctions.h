#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#include "node.hpp"

void createForest(Node *&root, int *arr, int size);

bool isRed(Node *elem);

bool isBlack(Node *elem);

Node *Parent(Node *elem);

Node *GrandParent(Node *elem);

bool isLeft(Node *elem);

bool isRight(Node *elem);

Node *Brother(Node *elem);

Node *Uncle(Node *elem);

Node * Root(Node* elem);;

Node *findElem(Node *root, int key);

void free(Node *elem);

bool isLeaf(Node *elem);

bool isNotLeaf(Node *elem);

int CountElem(Node *elem, int key);

//int Show(Node *elem, QGraphicsScene *Scene, int x, int y );

#endif // HELPERFUNCTIONS_H
