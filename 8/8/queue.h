#ifndef QUEUE_H
#define QUEUE_H

struct Queue {
    int capacity;
    char* items;
    int front;
    int rear;
    int size;
    bool hasEtalon;
    char etalon; 
};

void initQueue(Queue& queue, int capacity);
void destroyQueue(Queue& queue);
bool isEmpty(const Queue& queue);
bool isFull(const Queue& queue);
void enqueue(Queue& queue, char item);
char dequeue(Queue& queue);
int getSize(const Queue& queue);
void printQueue(const Queue& queue);
void clearQueue(Queue& queue);
char removeElement(Queue& queue);
void enqueueAndPrint(Queue& queue, char item);
void displayQueue(const Queue& queue);

#endif
