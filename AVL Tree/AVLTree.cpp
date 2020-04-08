//
// Created by hoang on 2/20/2020.
//

#include "AVLTree.h"
// main functions-------------------------------------------
void AVLTree::insert(const string& key)
{
    if(!root)
    {
        root = new Node(key);
        return;
    }
    Node* find = root;
    while(find)
    {
        if(key < find->getData())
        {
            find = find->getLeft();
        } else if (key > find->getData())
        {
            find = find->getRight();
        }
        else if(find->getData() == key)
        {
            return;
        }
    }
    Node* newNode = new Node(key);
    Node* curr = root;
    while(curr)
    {
        if(key < curr->getData())
        {
            if(!curr->getLeft())
            {
                curr->setLeft(newNode);
                newNode->parent = curr;
                //to break out of while loop
                curr = nullptr;
            } else
            {
                curr = curr->getLeft();
            }
        } else
        {
            if(!curr->getRight())
            {
                curr->setRight(newNode);
                newNode->parent = curr;
                curr = nullptr;
            } else
            {
                curr = curr->getRight();
            }
        }
    }
    Node* node = newNode->parent;
    while(node)
    {
        treeRebalance(node);
        node = node->parent;
    }
}

int AVLTree::balanceFactor(Node* node)
{
    if(node == nullptr)
    {
        return -1;
    }
    int lHeight = -1;
    if(node->getLeft())
    {
        lHeight = node->getLeft()->getHeight();
    }
    int rHeight = -1;
    if(node->getRight())
    {
        rHeight = node->getRight()->getHeight();
    }
    return lHeight-rHeight;
}

void AVLTree::printBalanceFactors()
{
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream &outFS, Node* node)
{
    if(node)
    {
        if(node->getLeft())
        {
            visualizeTree(outFS,node->getLeft());
            outFS << node->getData() << " -> " << node->getLeft()->getData() << ";" << endl;
        }
        if(node->getRight())
        {
            visualizeTree(outFS, node->getRight());
            outFS << node->getData() << " -> " << node->getRight()->getRight() << ";" << endl;
        }
    }
}

//helper functions------------------------------------------

int AVLTree::max(int x, int y)
{
    return (x > y ? x:y);
    //if x > y return x if else then return y;
}

void AVLTree::updateHeight(Node *node)
{
    int lHeight = -1;
    if(node->getLeft())
    {
        lHeight = node->getLeft()->getHeight();
    }
    int rHeight = -1;
    if(node->getRight())
    {
        rHeight = node->getRight()->getHeight();
    }
    node->setHeight(max(lHeight,rHeight) + 1);
}


Node* AVLTree::treeRebalance(Node* node)
{
    updateHeight(node);
    int balance = balanceFactor(node);
    int lBalance = balanceFactor(node->getLeft());
    int rBalance = balanceFactor(node->getRight());
    if(balance == -2)
    {
        if(rBalance == 1)
        {
            rightRotate(node->getRight());
        }
        leftRotate(node);
    } else if (balance == 2)
    {
        if(lBalance == -1)
        {
            leftRotate(node->getLeft());
        }
        rightRotate(node);
    }
    return node;
}

void AVLTree::printBalanceFactors(Node* node)
{
    if(node != nullptr)
    {
        printBalanceFactors(node->getLeft());
        cout << node->getData() << "(" << balanceFactor(node) << "), ";
        printBalanceFactors(node->getRight());
    }
}

Node* AVLTree::rightRotate(Node* node)
{
    Node* leftRightChild = node->getLeft()->getRight();
    if(node->parent)
    {
        treeReplaceChild(node->parent, node , node->getLeft());
    } else
    {
        root = node->getLeft();
        root->parent = nullptr;
    }
    treeSetChild(node->getLeft(), "right", node);
    treeSetChild(node, "left", leftRightChild);
    return root;
}

Node* AVLTree::leftRotate(Node* node)
{
    Node* rightLeftChild = node->getRight()->getLeft();
    if(node->parent)
    {
        treeReplaceChild(node->parent, node , node->getRight());
    } else
    {
        root = node->getRight();
        root->parent = nullptr;
    }
    treeSetChild(node->getRight(), "left", node);
    treeSetChild(node, "right", rightLeftChild);
    return root;
}

bool AVLTree::treeSetChild(Node* parent, string whichChild, Node* child)
{
    if(whichChild != "left" && whichChild != "right")
    {
        return false;
    }
    if(whichChild == "left")
    {
        parent->setLeft(child);
    } else
    {
        parent->setRight(child);
    }
    if(child)
    {
        child->parent = parent;
    }
    updateHeight(parent);
    return true;
}

bool AVLTree::treeReplaceChild(Node* parent, Node* currentChild, Node* newChild)
{
    if(parent->getLeft() == currentChild)
    {
        return treeSetChild(parent, "left", newChild);
    } else if (parent->getRight() == currentChild)
    {
        return treeSetChild(parent, "right", newChild);
    }
    return false;
}