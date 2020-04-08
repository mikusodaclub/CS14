//
// Created by hoang on 2/13/2020.
//

#ifndef BST_NODE_H
#define BST_NODE_H

#include <iostream>

using namespace std;

class Node
{
private:
    string data;
    int counter;
public:
    Node* left;
    Node* right;
    Node();
    Node(string data);
    //should have a getter funtions and maybe some setter functions
    string getData() const;
    void setData(const string &);
    void incCount();
    void decCount();
    int getCounter() const;
    void setCounter(int);
};

#endif //BST_NODE_H
