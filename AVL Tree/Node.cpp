//
// Created by hoang on 2/13/2020.
//

#include "Node.h"

Node::Node(string d)
{
    data = d;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
}

string Node::getData()
{
    return data;
}

int Node::getHeight()
{
    return height;
}

void Node::setHeight(int h)
{
    height = h;
}

void Node::setLeft(Node* l)
{
    left = l;
}

void Node::setRight(Node* r)
{
    right = r;
}

Node* Node::getLeft()
{
    return left;
}

Node* Node::getRight()
{
    return right;
}