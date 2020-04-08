//
// Created by hoang on 2/13/2020.
//

#include "BSTree.h"
/* Constructors */
/* Default constructor */
BSTree::BSTree()
{
    root = nullptr;
}

BSTree::~BSTree()
{
    deconstructor(this->root);
}

/* Mutators */

void BSTree::insert(const string &newString)
{
    if(!root){
        root = new Node(newString);
        return;
    }
    Node* curr = root;
    while(curr){
        if(newString < curr->getData()){
            if(!curr->left){
                Node* newNode = new Node(newString);
                curr->left = newNode;
                curr = nullptr;
            }
            else{
                curr = curr->left;
            }
        }
        else if(newString > curr->getData()){
            if(!curr->right){
                Node* newNode = new Node(newString);
                curr->right = newNode;
                curr = nullptr;
            }
            else{
                curr = curr->right;
            }
        }
        else{
            curr->incCount();
            return;
        }
    }
}

void BSTree::remove(const string &key)
{
    Node* parent = nullptr;
    Node* curr = root;
    while(curr){
        if(curr->getData() == key){
            if(curr->getCounter() > 1){
                curr->decCount();
                return;
            }
            if(!parent)
            {
                if(!curr->left && !curr->right)
                {
                    delete root;
                    root = nullptr;
                } else if(curr->left && !curr->right)
                {
                    Node* temp = root->left;
                    delete root;
                    root = temp;
                    return;
                } else if(curr->right && !curr->left)
                {
                    Node* temp = root->right;
                    delete root;
                    root = temp;
                    return;
                } else
                {
                    Node *successor = root->left;
                    while (successor->right != nullptr) {
                        successor = successor->right;
                    }
                    string successorData = successor->getData();
                    int sucCounter = successor->getCounter();
                    remove(successor->getData());
                    root->setData(successorData);
                    root->setCounter(sucCounter);
                    return;
                }
            } else if(!curr->left && !curr->right) {
                if(!parent){
                    delete root;
                    root = nullptr;
                }
                else if(parent->left == curr){
                    parent->left = nullptr;
                }
                else{
                    parent->right = nullptr;
                }
            }
            else if(curr->left) {
                    Node *successor = curr->left;
                    while (successor->right) {
                        successor = successor->right;
                    }
                    string successorData = successor->getData();
                    remove(successor->getData());
                    curr->setData(successorData);
            }
            else if(curr->right)
            {
                    Node *successor = curr->right;
                    while (successor->left) {
                        successor = successor->left;
                    }
                    string successorData = successor->getData();
                    remove(successor->getData());
                    curr->setData(successorData);
            }
            return;
        }
        else if(curr->getData() < key){
            parent = curr;
            curr = curr->right;
        }
        else{
            parent = curr;
            curr = curr->left;
        }
    }
    return;
    }

/* Accessors */

bool BSTree::search(const string &key) const
{
    Node* foundNode = search(this->root, key);
    return foundNode != nullptr;
}


/* Find and return the largest value in the tree. Return an empty string if the tree is empty */
string BSTree::largest() const {
    Node *temp = this->root;
    if (temp == nullptr) {
        return "";
    } else {
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp->getData();
    }
}
/* Find and return the smallest value in the tree. Return an emtpy string if the tree is empty */
string BSTree::smallest() const
{
    Node *temp = this->root;
    if (temp == nullptr) {
        return "";
    } else {
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp->getData();
    }
}

/* Compute and return the height of a particular string in the tree.
   The height of a leaf node is 0 (count the number of edges on the longest path).
   Return -1 if the string does not exist.
 */
int BSTree::height(const string& key) const
{
    Node* foundNode = search(this->root, key);
    if(foundNode)
    {
        return height(foundNode) - 1;
    } else
    {
        return -1;
    }
}

/* Printing */
/* For all printing orders, each node should be displayed as follows:
   <string> (<count>)
   e.g. goodbye(1), Hello World(3)
   */
void BSTree::preOrder() const
{
    preOrder(this->root);
}

void BSTree::postOrder() const
{
    postOrder(this->root);
}

void BSTree::inOrder() const
{
    inOrder(this->root);
}

//Private Helper Functions

void BSTree::preOrder(Node* curr) const
{
    if(curr != nullptr)
    {
        if(curr->left == nullptr && curr->right == nullptr)
        {
            cout << curr->getData() << "(" << curr->getCounter() << "), ";
        } else {
            //print
            cout << curr->getData() << "(" << curr->getCounter() << "), ";
            //children are next to check
            preOrder(curr->left);
            preOrder(curr->right);
        }
    }
}

void BSTree::inOrder(Node* curr) const
{
    if(curr != nullptr)
    {
        if(curr->left == nullptr && curr->right == nullptr)
        {
            cout << curr->getData() << "(" << curr->getCounter() << "), ";
        } else {
            inOrder(curr->left);
            cout << curr->getData() << "(" << curr->getCounter() << "), ";
            inOrder(curr->right);
        }
    }
}

void BSTree::postOrder(Node* curr) const
{
    if(curr != nullptr)
    {
        if(curr->left == nullptr && curr->right == nullptr)
        {
            cout << curr->getData() << "(" << curr->getCounter() << "), ";
        } else {
            postOrder(curr->left);
            postOrder(curr->right);
            cout << curr->getData() << "(" << curr->getCounter() << "), ";
        }
    }
}

void BSTree::insert(Node* curr, const string&data)
{
    if(curr == nullptr)
    {
        //means its empty
        Node *newNode = new Node(data);
        this->root = newNode;
    } else
    {
        if(curr->getData() == data)
        {
            curr->incCount();
        } else if (curr->getData() < data) {
            if (curr->right == nullptr) {
                Node *newNode = new Node(data);
                curr->right = newNode;
            } else {
                insert(curr->right, data);
            }
        } else
        {
                if(curr->left == nullptr)
                {
                    Node* newNode = new Node(data);
                    curr->left = newNode;
                } else
                {
                    insert(curr->left, data);
                }
        }
    }
}

void BSTree::deconstructor(Node* root)
{
    if(root)
    {
        deconstructor(root->left);
        deconstructor(root->right);
        delete root;
    }
}

int BSTree::height(Node* curr) const
{
    if(curr!= nullptr)
    {
        if(curr->left == nullptr && curr->right == nullptr)
        {
            return 1;
        } else
        {
            int left_height = height(curr->left);
            int right_height = height(curr->right);
            if(left_height > right_height)
            {
                return 1 + left_height;
            } else
            {
                return 1 + right_height;
            }
        }
    }
    return -1;
}


Node* BSTree::search(Node* curr ,const string &key) const
{
    if(!curr)
    {
        //if empty
        return nullptr;
    } else if (curr->getData() == key)
    {
        //if found
        return curr;
    } else if (curr->getData() > key)
    {
        //means what we want is less than the current node
        return search(curr->left, key);
    } else
    {
        //means the other situation
        return search(curr->right, key);
    }
}
