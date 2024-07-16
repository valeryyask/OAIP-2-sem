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
        std::cerr << "Стек пуст." << std::endl;
        throw std::runtime_error("Стек пуст");
    }
    int data = stack.top();
    stack.pop();
    return data;
}

int Stack::peek() {
    if (stack.empty()) {
        std::cerr << "Стек пуст." << std::endl;
        throw std::runtime_error("Стек пуст");
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
        std::cerr << "Ошибка: Не удалось открыть файл для записи." << std::endl;
        throw std::runtime_error("Не удалось открыть файл для записи");
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
        std::cerr << "Ошибка: Не удалось открыть файл для чтения." << std::endl;
        throw std::runtime_error("Не удалось открыть файл для чтения");
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
    std::cout << "Элементы стека:\n";
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
            // Найден первый повторяющийся элемент
            found = true;
        }
        else {
            // Если элемент уникален или не было найдено повторений
            temp.push(top);
            seen.insert(top);
        }
    }

    // Восстанавливаем стек без первого повторяющегося элемента
    while (!temp.empty()) {
        stack.push(temp.top());
        temp.pop();
    }
}