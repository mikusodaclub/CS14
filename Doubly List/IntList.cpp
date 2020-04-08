//
// Created by hoang on 1/14/2020.
//
#include <iostream>
#include "IntList.h"
using std::cout;
using std::endl;

IntList::IntList()
{
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    //Set the Next and Prev
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList()
{
        IntNode* node = dummyHead;
        IntNode* temp = dummyHead;
        while (node) {
            node = node->next;
            delete temp;
            temp = node;
        }
}

void IntList::push_front(int value)
{
        IntNode* add = new IntNode(value);
        dummyHead->next->prev = add;
        add->next = dummyHead->next;
        add->prev = dummyHead;
        dummyHead->next = add;

}

void IntList::push_back(int value)
{
    IntNode* add = new IntNode(value);
    dummyTail->prev->next = add;
    add->prev = dummyTail->prev;
    add->next = dummyTail;
    dummyTail->prev = add;
}

void IntList::pop_front()
{
    if(empty())
    {
        return;
    }
    else
    {
        IntNode* del = dummyHead->next;
        IntNode* afterDel = dummyHead->next->next;
        dummyHead->next = afterDel;
        afterDel->prev = dummyHead;
        delete del;
    }
}
void IntList::pop_back()
{
    if(empty())
    {
        return;
    }
    else
    {
        IntNode* del = dummyTail->prev;
        IntNode* beforeDel = dummyTail->prev->prev;
        dummyTail->prev = beforeDel;
        beforeDel->next = dummyTail;
        delete del;
    }

}
bool IntList::empty() const
{
    return dummyHead->next == dummyTail;
}

ostream &operator<<(ostream &out, const IntList &rhs)
{
    if(rhs.empty())
    {
        return out;
    }
    else
    {
        IntNode *curr = rhs.dummyHead->next;
        bool first = true;
        while (curr != rhs.dummyTail) {
            if (first) {
                out << curr->data;
                first = false;
                curr = curr->next;
            } else {
                out << " ";
                out << curr->data;
                curr = curr->next;
            }
        }
        return out;
    }
}

void IntList::printReverse() const
{
    if(empty())
    {
        return;
    }
    else
    {
        IntNode *curr = dummyTail->prev;
        bool first = true;
        while (curr != dummyHead) {
            if (first) {
                cout << curr->data;
                first = false;
                curr = curr->prev;
            } else {
                cout << " ";
                cout << curr->data;
                curr = curr->prev;
            }
        }
    }
}


