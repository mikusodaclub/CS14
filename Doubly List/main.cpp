#include <iostream>
#include "IntList.h"
using std::cout;
using std::endl;

int main() {
    IntList one;
    cout << "Push Front" << endl;
    one.push_front(3);
    one.push_front(2);
    one.push_front(1);
    cout << one << endl;
    cout << "Push Back" << endl;
    one.push_back(4);
    one.push_back(5);
    one.push_back(6);
    cout << one << endl;
    cout << "Pop Front" << endl;
    one.pop_front();
    cout << one << endl;
    cout << "Pop Back" << endl;
    one.pop_back();
    cout << one << endl << endl;

    IntList two;
    two.push_front(5);
    two.push_front(4);
    two.push_front(3);
    two.push_front(2);
    two.push_front(1);
    cout << "Current List" << endl;
    cout << two << endl;
    cout << "Reverse List"<< endl;
    two.printReverse();
    cout << endl << endl;

    IntList three;
    cout << "Empty List Test----" << endl;
    cout << "Pop Front" << endl;
    three.pop_back();
    cout << "Pop Back" << endl;
    three.pop_front();
    return 0;
}