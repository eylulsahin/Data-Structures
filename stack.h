#ifndef STACK_H
#define STACK_H

#include <iostream>


using namespace std;

template <class Type>
class Stack
{
private:
    Type head;

public:
    void push(Type input);
    void pop();
    bool isEmpty();
    Type top();
    Stack();
    ~Stack();
};
#endif
