//
// Created by hoang on 2/13/2020.
//

#include "Node.h"

Node::Node()
{
    counter = 0;
    data = "";
    left = nullptr;
    right = nullptr;
}

Node::Node(string data)
{
    counter = 1;
    this->data = data;
    left = nullptr;
    right = nullptr;
}


string Node::getData() const
{
    return data;
}

void Node::setData(const string &newData)
{
    data = newData;
}

int Node::getCounter() const
{
    return counter;
}

void Node::setCounter(int newCounter)
{
    counter = newCounter;
}

void Node::incCount()
{
    counter++;
}

void Node::decCount()
{
    counter--;
}

