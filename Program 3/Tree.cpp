//
// Created by hoang on 2/23/2020.
//
#include <string>
#include <iostream>
#include "Tree.h"
//public:
Tree::Tree()
{
    root = nullptr;
}

Tree::~Tree()
{
    destruct(root);
}

void Tree::insert(const string& data)
{
    if (root == nullptr)
    {
        root = new Node(data);
        return;
    }
    if (search(data))
    {
        return;
    }
    Node* curr = root;
    while (true)
    {
        //if no children
        if (curr->left == nullptr && curr->middle == nullptr && curr->right == nullptr)
        {
            //if node only has one item fix.
            if (curr->large.empty())
            {
                if (data > curr->small)
                {
                    curr->large = data;
                }
                else
                {
                    curr->large = curr->small;
                    curr->small = data;
                }
                //full node
            }
            else
            {
                split(curr, data, nullptr, nullptr);
            }
            return;
        }
            //has children
        else
        {
            if (data < curr->small)
            {
                curr = curr->left;
                //if 3 node
            }
            else if (!(curr->large.empty()))
            {
                if (data < curr->large)
                {
                    curr = curr->middle;
                }
                else if (data > curr->large)
                {
                    curr = curr->right;
                }
            }
                //2 node
            else if (data > curr->large)
            {
                curr = curr->right;
            }
        }
    }
}

void Tree::preOrder() const
{
    preOrder(root);
    cout << endl;
}

void Tree::inOrder() const
{
    inOrder(root);
    cout << endl;
}

void Tree::postOrder() const
{
    postOrder(root);
    cout << endl;
}

void Tree::remove(const string& key)
{
    //not found
    if (!search(key))
    {
        return;
    }

    Node* curr = search(root, key);
    Node* swap = curr;

    //find the successor to find the inorder sucessor and if theres nothing else then its itself.  Move from node
    if (curr->middle != nullptr && curr->small == key)
    {
        //fins successor from middle and if not go right;
        swap = curr->middle;
    }
    else if (curr->right != nullptr)
    {
        swap = curr->right;
    }
    //move to find the inorder successor
    while (swap->left != nullptr || swap->middle != nullptr || swap->right != nullptr)
    {
        //keep moving left to find successor
        swap = swap->left;
    }
    if (curr->small == key)
    {
        //changes the keys
        curr->small = swap->small;
        //if it only holds one item, fix it
        if (swap->large.empty())
        {
            swap->small.clear();
            fix(swap, nullptr);
        }
        else
        {
            //if node has two nodes just delete the large one after swaping them
            swap->small = swap->large;
            swap->large.clear();
        }
    }
    else
        //change the large one
    {
        if (curr != swap)
        {
            curr->large = swap->small;
            if (swap->large.empty())
            {
                swap->small.clear();
                fix(swap, nullptr);
            }
            else
            {
                swap->small = swap->large;
                swap->large.clear();
            }
        }
        else
        {
            swap->large.clear();
        }
    }

}

void Tree::fix(Node* curr, Node* child) // basically rebalance
{
    if (curr == root)
    {
        if (curr->left != nullptr || curr->right != nullptr)
        {
            root = child;
            child->parent = nullptr;
        }
        else
        {
            root = nullptr;
        }
        delete  curr;
        return;
    }
    //no 3 node sibs
    if (curr->parent->left->large.empty() && curr->parent->right->large.empty())
    {
        //if its the left child
        if (curr->parent->left == curr) {
            curr = curr->parent;
            curr->left->small = curr->small;
            if (curr->large.empty()) {
                curr->left->large = curr->right->small;
                curr->small.clear();
                if (child != nullptr) {
                    curr->left->left = child;
                    child->parent = curr->left;
                    curr->left->middle = curr->right->left;
                    curr->left->middle->parent = curr->left;
                    curr->left->right = curr->right->right;
                    curr->left->right->parent = curr->left;
                }
                delete curr->right;
                curr->right = nullptr;
                fix(curr, curr->left);
            }
            else
            {
                curr->left->large = curr->middle->small;
                curr->small = curr->large;
                curr->large.clear();
                if (child != nullptr)
                {
                    curr->left->left = child;
                    child->parent = curr->left;
                    curr->left->middle = curr->middle->left;
                    curr->left->middle->parent = curr->left;
                    curr->left->right = curr->middle->right;
                    curr->left->right->parent = curr->left;
                }
                delete curr->middle;
                curr->middle = nullptr;
            }
        }
            //if parent right child
        else if (curr->parent->right == curr)
        {
            curr = curr->parent;
            if (curr->large.empty())
            {
                curr->left->large = curr->small;
                curr->small.clear();
                delete curr->right;
                curr->right = nullptr;
                if (child != nullptr)
                {
                    curr->left->middle = curr->left->right;
                    curr->left->middle->parent = curr->left;
                    curr->left->right = child;
                    child->parent = curr->left;
                }
                fix(curr, curr->left);
            }
            else
            {
                curr->right->large = curr->large;
                curr->large.clear();
                curr->right->small = curr->middle->small;
                if (child != nullptr)
                {
                    curr->right->right = child;
                    child->parent = curr->right;
                    curr->right->middle = curr->middle->right;
                    curr->right->middle->parent = curr->right;
                    curr->right->left = curr->middle->left;
                    curr->right->left->parent = curr->right;
                }
                delete curr->middle;
                curr->middle = nullptr;
            }
        }
            // its the middle child;
        else {
            curr = curr->parent;
            curr->left->large = curr->small;
            curr->small = curr->large;
            curr->large.clear();
            if (child != nullptr) {
                curr->left->middle = curr->left->right;
                curr->left->middle->parent = curr->left;
                curr->left->right = child;
                child->parent = curr->left;
            }
            delete curr->middle;
            curr->middle = nullptr;
        }
    }

        //the node has a 3 node sib then we want to redistribute
    else
    {
        //if node parent left child
        if (curr->parent->left == curr)
        {
            curr = curr->parent;
            curr->left->small = curr->small;
            if (curr->large.empty())
            {
                curr->small = curr->right->small;
                curr->right->small = curr->right->large;
                curr->right->large.clear();
                if (child != nullptr)
                {
                    curr->left->left = child;
                    child->parent = curr->left;
                    curr->left->right = curr->right->left;
                    curr->left->right->parent = curr->left;
                    curr->right->left = curr->right->middle;
                    curr->right->left->parent = curr->right;
                    curr->right->middle = nullptr;
                }
            }
            else
            {
                curr->small = curr->middle->small;
                if (curr->middle->large.empty())
                {
                    curr->middle->small = curr->large;
                    curr->large = curr->right->small;
                    curr->right->small = curr->right->large;
                    curr->right->large.clear();
                    if (child != nullptr)
                    {
                        curr->left->left = child;
                        child->parent = curr->left;
                        curr->left->right = curr->middle->left;
                        curr->left->right->parent = curr->left;
                        curr->middle->left = curr->middle->right;
                        curr->middle->left->parent = curr->middle;
                        curr->middle->right = curr->right->left;
                        curr->middle->right->parent = curr->middle;
                        curr->right->left = curr->right->middle;
                        curr->right->left->parent = curr->right;
                        curr->right->middle = nullptr;
                    }
                }
                else
                {
                    curr->middle->small = curr->middle->large;
                    curr->middle->large.clear();
                    if (child != nullptr)
                    {
                        curr->left->left = child;
                        child->parent = curr->left;
                        curr->left->right = curr->middle->left;
                        curr->left->right->parent = curr->left;
                        curr->middle->left = curr->middle->right;
                        curr->middle->left->parent = curr->middle;
                        curr->middle->right = curr->right->left;
                        curr->middle->right->parent = curr->middle;
                        curr->right->left = curr->right->middle;
                        curr->right->left->parent = curr->right;
                        curr->right->middle = nullptr;
                    }
                }
            }
        }
            //if node os parent right
        else if (curr->parent->right == curr)
        {
            curr = curr->parent;
            if (curr->large.empty())
            {
                curr->right->small = curr->small;
                curr->small = curr->left->large;
                curr->left->large.clear();
                if (child != nullptr)
                {
                    curr->right->right = child;
                    child->parent = curr->right;
                    curr->right->left = curr->left->right;
                    curr->right->left->parent = curr->right;
                    curr->left->right = curr->left->middle;
                    curr->left->right->parent = curr->left;
                    curr->left->middle = nullptr;
                }
            }
            else
            {
                curr->right->small = curr->large;
                if (curr->middle->large.empty())
                {
                    curr->large = curr->middle->small;
                    curr->middle->small = curr->small;
                    curr->small = curr->left->large;
                    curr->left->large.clear();
                    if (child != nullptr)
                    {
                        curr->right->right = child;
                        child->parent = curr->right;
                        curr->right->left = curr->middle->right;
                        curr->right->left->parent = curr->right;
                        curr->middle->right = curr->middle->left;
                        curr->middle->right->parent = curr->middle;
                        curr->middle->left = curr->left->right;
                        curr->middle->left->parent = curr->middle;
                        curr->left->right = curr->left->middle;
                        curr->left->right->parent = curr->left;
                        curr->left->middle = nullptr;
                    }
                }
                else
                {
                    curr->large = curr->middle->large;
                    curr->middle->large.clear();
                    if (child != nullptr)
                    {
                        curr->right->right = child;
                        child->parent = curr->right;
                        curr->right->left = curr->middle->right;
                        curr->right->left->parent = curr->right;
                        curr->middle->right = curr->middle->middle;
                        curr->middle->right->parent = curr->middle;
                        curr->middle->middle = nullptr;
                    }
                }
            }
        }
            //else node is parent's middle child
        else
        {
            curr = curr->parent;
            if (curr->right->large.empty())
            {
                curr->middle->small = curr->small;
                curr->small = curr->left->large;
                curr->left->large.clear();
                if (child != nullptr)
                {
                    curr->middle->right = child;
                    child->parent = curr->middle;
                    curr->middle->left = curr->left->right;
                    curr->middle->left->parent = curr->middle;
                    curr->left->right = curr->left->middle;
                    curr->left->right->parent = curr->left;
                    curr->left->middle = nullptr;
                }
            }
            else
            {
                curr->middle->small = curr->large;
                curr->large = curr->right->small;
                curr->right->small = curr->right->large;
                curr->right->large.clear();
                if (child != nullptr)
                {
                    curr->middle->left = child;
                    child->parent = curr->middle;
                    curr->middle->right = curr->right->left;
                    curr->middle->right->parent = curr->middle;
                    curr->right->left = curr->right->middle;
                    curr->right->left->parent = curr->right;
                    curr->right->middle = nullptr;
                }
            }
        }
    }

}

bool Tree::search(const string& key) const
{
    //return a node if true, false otherwise
    return search(root, key);
}


//private:
void Tree::destruct(Node* node) const
{
    if (node)
    {
        if (node->large.empty())//2 Node
        {
            destruct(node->left);
            destruct(node->right);
            delete  node;
        }
        else//3 Node
        {
            destruct(node->left);
            destruct(node->middle);
            destruct(node->right);
            delete node;
        }
    }
}

void Tree::preOrder(Node* node) const
{
    if (node != nullptr)
    {
        //node only has one item inside
        if (node->large.empty())
        {
            cout << node->small << ", ";
            preOrder(node->left);
            preOrder(node->right);
        }
        else
        {
            cout << node->small << ", ";
            preOrder(node->left);
            cout << node->large << ", ";
            preOrder(node->middle);
            preOrder(node->right);
        }
    }
}

void Tree::inOrder(Node* node) const
{
    if (node)
    {
        if (node->large.empty())
        {
            inOrder(node->left);
            cout << node->small << ", ";
            inOrder(node->right);
        }
        else
        {
            inOrder(node->left);
            cout << node->small << ", ";
            inOrder(node->middle);
            cout << node->large << ", ";
            inOrder(node->right);
        }
    }
}

void Tree::postOrder(Node* node)const
{
    if (node)
    {
        if (node->large.empty())
        {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->small << ", ";
        }
        else
        {
            postOrder(node->left);
            postOrder(node->middle);
            cout << node->small << ", ";
            postOrder(node->right);
            cout << node->large << ", ";
        }
    }
}

Node* Tree::search(Node* node, const string& key) const
{
    if (node)
    {
        //it equals
        if (key == node->small)
        {
            return node;
        }
        //go left no matter what
        if (key < node->small)
        {
            return search(node->left, key);
            //checks is two node
        }
        else if (node->large.empty())
        {
            return search(node->right, key);
            //means its a 3 node
        }
        else
        {
            if (key == node->large)
            {
                return node;
            }
            else if (key < node->large)
            {
                return search(node->middle, key);
            }
            else
            {
                return search(node->right, key);
            }
        }
    }
    //not found
    return nullptr;
}

void Tree::split(Node* curr, const string& key, Node* leftChild, Node* rightChild)
{
    string midValue;
    Node* leftNode;
    Node* rightNode;

    //find small, middle, and large value
    //key is mid
    if (key > curr->small&& key < curr->large)
    {
        midValue = key;
        leftNode = new Node(curr->small);
        rightNode = new Node(curr->large);
        //small is mid
    }
    else if (key < curr->small)
    {
        midValue = curr->small;
        leftNode = new Node(key);
        rightNode = new Node(curr->large);
        //large is mid
    }
    else
    {
        midValue = curr->large;
        leftNode = new Node(curr->small);
        rightNode = new Node(key);
    }
    //put mid in parent or create a new parent
    //if root
    if (curr->parent == nullptr)
    {
        root = new Node(midValue);
        root->left = leftNode;
        leftNode->parent = root;
        root->right = rightNode;
        rightNode->parent = root;
        //if parent is not a full node with 3 children
    }
    else if (curr->parent->large.empty())
    {
        //you can move the data into parent
        if (midValue > curr->parent->small)
        {
            curr->parent->large = midValue;
            //if inserting into parent with one and data is less than small
        }
        else
        {
            curr->parent->large = curr->parent->small;
            curr->parent->small = midValue;
        }
        //rotate left
        if (leftNode->small < curr->parent->small)
        {
            curr->parent->left = leftNode;
            curr->parent->middle = rightNode;
            //rotate right
        }
        else
        {
            curr->parent->middle = leftNode;
            curr->parent->right = rightNode;
        }
        //set parents
        leftNode->parent = curr->parent;
        rightNode->parent = curr->parent;
    }
    else
    {
        //if parent is full
        split(curr->parent, midValue, leftNode, rightNode);
    }
    //if curr was not leaf, connect the values
    if (curr->left != nullptr || curr->middle != nullptr || curr->right != nullptr)
    {
        if (leftChild->small < leftNode->small)
        {
            leftNode->left = leftChild;
            leftChild->parent = leftNode;
            leftNode->right = rightChild;
            rightChild->parent = leftNode;
            //the top part is for the extra data from the other nodes that had to be split
            rightNode->left = curr->middle;
            rightNode->left->parent = rightNode;
            rightNode->right = curr->right;
            rightNode->right->parent = rightNode;
        }
        else if (rightChild->small > rightNode->small)
        {
            leftNode->left = curr->left;
            leftNode->left->parent = leftNode;
            leftNode->right = curr->middle;
            leftNode->right->parent = leftNode;
            //bottom parts are extra data
            rightNode->left = leftChild;
            leftChild->parent = rightNode;
            rightNode->right = rightChild;
            rightChild->parent = rightNode;
        }
        else
        {
            leftNode->left = curr->left;
            leftNode->left->parent = leftNode;
            leftNode->right = leftChild;
            leftChild->parent = leftNode;
            rightNode->left = rightChild;
            rightChild->parent = rightNode;
            rightNode->right = curr->right;
            rightNode->right->parent = rightNode;
        }
    }
    delete curr;
}