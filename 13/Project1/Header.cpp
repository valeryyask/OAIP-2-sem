#include "Header.h"
#include <iostream>

// First hash function: h1(key) = key % size
int h1(int key, int size) {
    return key % size;
}

// Second hash function: h2(key) = 1 + (key % size)
int h2(int key, int size) {
    return 1 + (key % size);
}

// Combined hash function: h(key, i) = (h1(key) + i * h2(key)) % size
int combined_hash(int key, int size, int i) {
    return (h1(key, size) + i * h2(key, size)) % size;
}

Object create(int size, int(*getkey)(void*)) {
    return *(new Object(size, getkey)); // выделение памяти
}

Object::Object(int size, int(*getkey)(void*)) {
    N = 0;
    this->size = size;
    this->getKey = getkey;
    this->data = new void* [size];
    for (int i = 0; i < size; ++i)
        data[i] = NULL;
}

bool Object::insert(void* d) {
    bool b = false;
    if (N != size) {
        int key = getKey(d);
        int index = h1(key, size); // Start with the first hash function
        int i = 0;
        while (i < size && (data[index] != NULL && data[index] != DEL)) {
            index = combined_hash(key, size, ++i); // Use the combined hash function
        }
        if (data[index] == NULL || data[index] == DEL) {
            data[index] = d;
            N++;
            b = true;
        }
    }
    return b;
}

int Object::searchInd(int key) {
    int t = -1;
    bool b = false;
    if (N != 0) {
        int i = 0;
        int j = h1(key, size); // Start with the first hash function
        while (data[j] != NULL && i != size && !b) {
            if (data[j] != DEL && getKey(data[j]) == key) {
                t = j;
                b = true;
            }
            j = combined_hash(key, size, ++i); // Use the combined hash function
        }
    }
    return t;
}

void* Object::search(int key) {
    int t = searchInd(key);
    return (t >= 0) ? (data[t]) : (NULL);
}

void* Object::deleteByKey(int key) {
    int i = searchInd(key);
    void* t = data[i];
    if (t != NULL) {
        data[i] = DEL;
        N--;
    }
    return t;
}

bool Object::deleteByValue(void* d) {
    return (deleteByKey(getKey(d)) != NULL);
}

void Object::scan(void(*f)(void*)) {
    for (int i = 0; i < this->size; i++) {
        if (data[i] == NULL)
            std::cout << " Элемент " << i + 1 << " - Пусто!" << std::endl;
        else if (data[i] == DEL)
            std::cout << " Элемент " << i + 1 << " - Удален" << std::endl;
        else
            f(data[i]);
    }
}
