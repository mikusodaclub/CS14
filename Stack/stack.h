//
// Created by hoang on 2/4/2020.
//
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

const int MAX_SIZE = 20;

template<typename T>
class stack
{
    //Private data fields:
    //data: An array with maximum size of 20. (Declare a constant in stack.h called MAX_SIZE and set it to 20.)
    //size: stores the current number of elements in the stack.
private:
    T data[MAX_SIZE];
    int size;
    //Public interface:
    //stack(): constructs an empty stack.
    //push(T val): inserts a new element (val) of type T (T could be integer or string) into the data. If the data array is full, this function should throw an overflow_error exception with error message "Called push on full stack.".
    //pop(): removes the last element from data. If the data array is empty, this function should throw an outofrange exception with error message "Called pop on empty stack.".
    //top(): returns the top element of stack (last inserted element). If stack is empty, this function should throw an underflow_error exception with error message "Called top on empty stack.".
    //empty(): returns true if the stack is empty otherwise it returns false.
public:
    stack();
    void push(T val);
    void pop();
    T top();
    bool empty();
};

template<typename T>
stack<T>::stack() : size(0) {}

template<typename T>
void stack<T>::push(T val)
{
if(size == MAX_SIZE)
{
    throw overflow_error("Called push on full stack.");
} else
{
    data[size] = val;
    size++;
}
}

template<typename T>
void stack<T>::pop()
{
    if(empty())
    {
        throw out_of_range("Called pop on empty stack.");
    } else
    {
        size--;
    }
}

template<typename T>
T stack<T>::top()
{
    if(empty())
    {
        throw underflow_error("Called top on empty stack.");
    } else
    {
        return data[size-1];
    }
}

template<typename T>
bool stack<T>::empty()
{
    return size == 0;
}