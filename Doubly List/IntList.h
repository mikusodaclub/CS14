//
// Created by hoang on 1/14/2020.
//

#ifndef __INTLIST_H__
#define __INTLIST_H__

#include <iostream>


using std::cout;
using std::endl;
using std::ostream;
struct IntNode
{
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class IntList
{
private:
    IntNode* dummyHead;
    IntNode* dummyTail;
public:
    IntList();
    ~IntList();
    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void pop_back();
    bool empty() const;
    friend ostream &operator<<(ostream &out, const IntList &rhs);
    void printReverse() const;
};

#endif //_INTLIST_H
