#include "queue.h"
#include <iostream>

void initQueue(Queue& queue, int capacity) {
    queue.capacity = capacity;
    queue.items = new char[capacity];
    queue.front = 0;
    queue.rear = -1;
    queue.size = 0;
    queue.hasEtalon = false;
}

void destroyQueue(Queue& queue) {
    delete[] queue.items;
}

bool isEmpty(const Queue& queue) {
    return queue.size == 0;
}

bool isFull(const Queue& queue) {
    return queue.size == queue.capacity;
}

void enqueue(Queue& queue, char item) {
    if (isFull(queue)) {
        std::cerr << "Очередь заполнена." << std::endl;
        return;
    }
    queue.rear = (queue.rear + 1) % queue.capacity;
    queue.items[queue.rear] = item;
    queue.size++;
    if (item == queue.etalon) {
        queue.hasEtalon = true;
    }
}

char dequeue(Queue& queue) {
    if (isEmpty(queue)) {
        std::cerr << "Очередь пуста." << std::endl;
        return '\0';
    }
    char item = queue.items[queue.front];
    queue.front = (queue.front + 1) % queue.capacity;
    queue.size--;
    if (item == queue.etalon) {
        // Check if etalon still exists in the queue
        queue.hasEtalon = false;
        for (int i = 0; i < queue.size; i++) {
            if (queue.items[(queue.front + i) % queue.capacity] == queue.etalon) {
                queue.hasEtalon = true;
                break;
            }
        }
    }
    return item;
}

int getSize(const Queue& queue) {
    return queue.size;
}

void printQueue(const Queue& queue) {
    if (isEmpty(queue)) {
        std::cout << "Очередь пуста." << std::endl;
        return;
    }
    std::cout << "Содержимое очереди: ";
    int i = queue.front;
    do {
        std::cout << queue.items[i] << " ";
        i = (i + 1) % queue.capacity;
    } while (i != (queue.rear + 1) % queue.capacity);
    std::cout << std::endl;
}

void clearQueue(Queue& queue) {
    queue.front = 0;
    queue.rear = -1;
    queue.size = 0;
    queue.hasEtalon = false;
}

char removeElement(Queue& queue) {
    return dequeue(queue);
}

void enqueueAndPrint(Queue& queue, char item) {
    enqueue(queue, item);
    printQueue(queue);
}

void displayQueue(const Queue& queue) {
    printQueue(queue);
}
