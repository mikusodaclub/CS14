//
// Created by hoang on 2/23/2020.
//
#include <string>
#include "Node.h"

using namespace std;

Node::Node()
{
    small = "";
    large = "";
    left = nullptr;
    middle = nullptr;
    right = nullptr;
    parent = nullptr;
}

Node::Node(string data)
{
    small = data;
    large = "";
    left = nullptr;
    middle = nullptr;
    right = nullptr;
    parent = nullptr;
}