#include "node.hpp"

Node *Node::getParent() const
{
    return parent;
}

void Node::setParent(Node *value)
{
    parent = value;
}

Node *Node::getLeft() const
{
    return left;
}

void Node::setLeft(Node *value)
{
    left = value;
}

Node *Node::getRight() const
{
    return right;
}

void Node::setRight(Node *value)
{
    right = value;
}

QColor Node::getColor() const
{
    return color;
}

void Node::setColor(const QColor &value)
{
    this->setBrush(value);
    color = value;
}

int Node::getValue() const
{
    return value;
}

void Node::setValue(int value)
{
    this->value = value;
}

