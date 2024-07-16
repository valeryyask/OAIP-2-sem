#include "stack.h"
#include <string>  
#include <sstream> 
#include <unordered_set>

Stack::Stack() {}

void Stack::push(int data) {
    stack.push(data);
}

int Stack::pop() {
    if (stack.empty()) {
        std::cerr << "���� ����." << std::endl;
        throw std::runtime_error("���� ����");
    }
    int data = stack.top();
    stack.pop();
    return data;
}

int Stack::peek() {
    if (stack.empty()) {
        std::cerr << "���� ����." << std::endl;
        throw std::runtime_error("���� ����");
    }
    return stack.top();
}

void Stack::clear() {
    while (!stack.empty()) {
        stack.pop();
    }
}

void Stack::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "������: �� ������� ������� ���� ��� ������." << std::endl;
        throw std::runtime_error("�� ������� ������� ���� ��� ������");
    }
    std::stack<int> temp = stack;
    while (!temp.empty()) {
        file << temp.top() << std::endl;
        temp.pop();
    }
    file.close();
}

void Stack::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "������: �� ������� ������� ���� ��� ������." << std::endl;
        throw std::runtime_error("�� ������� ������� ���� ��� ������");
    }
    std::vector<int> tempData; 
    int data;
    while (file >> data) {
        tempData.push_back(data); 
    }
    file.close();

    for (auto it = tempData.rbegin(); it != tempData.rend(); ++it) {
        stack.push(*it);
    }
}


void Stack::printStack() {
    std::cout << "�������� �����:\n";
    std::stack<int> temp = stack;
    while (!temp.empty()) {
        std::cout << temp.top() << std::endl;
        temp.pop();
    }
}

void Stack::removeFirstDuplicate() {
    std::stack<int> temp;
    std::unordered_set<int> seen;
    bool found = false;

    while (!stack.empty()) {
        int top = stack.top();
        stack.pop();

        if (!found && seen.find(top) != seen.end()) {
            // ������ ������ ������������� �������
            found = true;
        }
        else {
            // ���� ������� �������� ��� �� ���� ������� ����������
            temp.push(top);
            seen.insert(top);
        }
    }

    // ��������������� ���� ��� ������� �������������� ��������
    while (!temp.empty()) {
        stack.push(temp.top());
        temp.pop();
    }
}