//
// Created by hoang on 2/13/2020.
//

#ifndef BST_NODE_H
#define BST_NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node
{
private:
    string data;
    Node* left;
    Node* right;
    int height;
public:
    Node* parent;
    Node(string d);
    string getData();
    int getHeight();
    void setHeight(int);
    void setLeft(Node*);
    void setRight(Node*);
    Node* getLeft();
    Node* getRight();
};

#endif //BST_NODE_H
