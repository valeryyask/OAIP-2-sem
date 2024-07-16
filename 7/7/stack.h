#pragma once
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept> 

struct Stack {
    Stack();

    void push(int data);
    int pop();
    int peek();
    void clear();
    void saveToFile(const std::string& filename);
    void readFromFile(const std::string& filename);
    void removeFirstDuplicate();
    void printStack();

private:
    std::stack<int> stack;
};

#endif
