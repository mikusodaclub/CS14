//
// Created by hoang on 2/20/2020.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>
#include <string>
#include <fstream>

#include "Node.h"

class AVLTree
{
private:
    Node* root;
public:
    AVLTree() {root = nullptr;};
    void insert(const string &);
    int balanceFactor(Node*);
    void printBalanceFactors();
    void visualizeTree(const string &);
private:
//    Node* findUnbalancedNode(Node*);
    int max(int x, int y);
    void updateHeight(Node* node);
    Node* treeRebalance(Node* node);
    void printBalanceFactors(Node* n);
    void visualizeTree(ofstream &, Node* );
    Node* rightRotate(Node* r);
    Node* leftRotate(Node* l);
    bool treeSetChild(Node*, string, Node*);
    bool treeReplaceChild(Node*, Node*, Node*);
};


#endif //AVLTREE_AVLTREE_H
