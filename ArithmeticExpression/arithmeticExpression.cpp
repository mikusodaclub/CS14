//
// Created by hoang on 2/11/2020.
//

#include "arithmeticExpression.h"
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;


//Remember you have a tree node and a string of the expression
arithmeticExpression::arithmeticExpression(const string &inputExpression)
{
    //Empty Tree and sets Expression//
    infixExpression = inputExpression;
    root = nullptr;
}

/* Implementation of destrucor is optional.
   The destructor should deallocate all the nodes in the tree. */
//~arithmeticExpression();

void arithmeticExpression::buildTree()
{
    string postfixExpression = infix_to_postfix();
    stack<TreeNode*> s;
    char c;
    int keyNum = 'a';
    for(unsigned i = 0; i < postfixExpression.size(); ++i) //iterates through the string and checks each character depending on if its an operator or operand
    {
        char currKey = (char)keyNum;
        keyNum++;
        c = postfixExpression.at(i);
        TreeNode* curr = new TreeNode(c,currKey);
        if(i == postfixExpression.size()-1) //if stack finally gets to the root.
        {
            root = curr;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/') // combines two tops if it gets to an operator.
        {
            curr->right = s.top();
            s.pop();
            curr->left = s.top();
            s.pop();
            s.push(curr);
        } else // it got to an operand
        {
            s.push(curr);
        }
    }
}

/* Calls the recursive infix function. */
void arithmeticExpression::infix()
{
    infix(root);
}

/* Calls the recursive prefix function. */
void arithmeticExpression::prefix()
{
    prefix(root);
}

/* Calls the recursive postfix function. */
void arithmeticExpression::postfix()
{
    postfix(root);
}


int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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


/* Helper function that outputs the infix notation of the arithmetic expression tree
   by performing the inorder traversal of the tree.
   An opening and closing parenthesis must be added at the
   beginning and ending of each expression. */
void arithmeticExpression::infix(TreeNode *currNode)
{
    if(currNode == nullptr) // check if its empty
    {
        return;
    } else {
        if (currNode->left == 0 && currNode->right == 0) { // check if its a leaf node
            cout << currNode->data;
        } else {
            //does this in inorder
            cout << '(';
            infix(currNode->left);
            cout << currNode->data;
            infix(currNode->right);
            cout << ')';
        }
    }
}

/* Helper function that outputs the prefix notation of the arithmetic expression tree
   by performing the preorder traversal of the tree. */
void arithmeticExpression::prefix(TreeNode *currNode)
{
    if(currNode == nullptr)
    {
        return;
    } else {
        if (currNode->left == 0 && currNode->right == 0) {
            cout << currNode->data;
        } else {
            cout << currNode->data;
            prefix(currNode->left);
            prefix(currNode->right);
        }
    }
}

/* Helper function that outputs the postfix notation of the arithmetic expression tree
   by performing the postorder traversal of the tree. */
void arithmeticExpression::postfix(TreeNode *currNode)
{
    if(currNode == nullptr)`
    {
        return;
    } else {
        if (currNode->left == 0 && currNode->right == 0) {
            cout << currNode->data;
        } else {
            postfix(currNode->left);
            postfix(currNode->right);
            cout << currNode->data;
        }
    }
}

/* Helper function for generating the dotty file. This is a recursive function. */
    void arithmeticExpression::visualizeTree(ofstream &outFS, TreeNode *Curr)
    {
        if(Curr->left == 0 && Curr->right == 0)
        {
            return;
        } else {
            outFS << "key" << Curr->key << " -> key" << Curr->left->key << ";" << endl;
            outFS << "key" << Curr->key << " -> key" << Curr->right->key << ";" << endl;
            visualizeTree(outFS, Curr->left);
            visualizeTree(outFS, Curr->right);
        }
    }