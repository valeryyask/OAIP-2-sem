#include "list.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
using namespace std;

void insert(Address* e, Address** phead, Address** plast) {
    Address* p = *plast;
    if (*plast == NULL) {
        e->next = NULL;
        e->prev = NULL;
        *plast = e;
        *phead = e;
    }
    else {
        p->next = e;
        e->next = NULL;
        e->prev = p;
        *plast = e;
    }
}

Address* setElement() {
    string cho1, cho2;
    Address* temp = new  Address();
    if (!temp) {
        cerr << "Ошибка выделения памяти.\n";
        return NULL;
    }

    do {
        cout << "Введите имя: ";
        getline(cin, cho1);
        cin.ignore(cin.rdbuf()->in_avail());
        cin.clear();
    } while (cho1.find_first_not_of(FOUND2) != string::npos);
    temp->name = cho1;

    do {
        cout << "Введите город: ";
        getline(cin, cho2);
        cin.ignore(cin.rdbuf()->in_avail());
        cin.clear();
        if (cho2.find_first_not_of(FOUND1) != string::npos) {

        }
    } while (cho2.find_first_not_of(FOUND1) != string::npos);
    temp->city = cho2;

    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void outputList(Address** phead, Address** plast) {
    if (*phead == nullptr) {
        cout << "Список пуст.\n";
        return;
    }

    Address* t = *phead;
    while (t) {
        cout << "Имя: " << t->name << ' ' << "Город: " << t->city << '\n';
        t = t->next;
    }
    cout << endl;
}


void delet(string name, Address** phead, Address** plast) {
    Address* current = *phead;
    bool found = false;
    while (current) {
        if (name == current->name) {
            found = true;
            Address* toDelete = current;

            if (toDelete == *phead) {
                *phead = toDelete->next;
                if (*phead)
                    (*phead)->prev = NULL;
                else
                    *plast = NULL;
            }
            else {
                toDelete->prev->next = toDelete->next;
                if (toDelete != *plast)
                    toDelete->next->prev = toDelete->prev;
                else
                    *plast = toDelete->prev;
            }

            current = current->next;
            delete toDelete;
        }
        else {
            current = current->next;
        }
    }

    if (!found) {
        cerr << "Имя не найдено.\n" << endl;
    }
    else {
        cout << "Элементы с именем " << name << " удалены.\n" << endl;
    }
}

void find(string name, Address** phead) {
    Address* current = *phead;
    bool found = false;
    while (current) {
        if (name == current->name) {
            found = true;
            cout << "Имя: " << current->name << ", Город: " << current->city << endl;
        }
        current = current->next;
    }

    if (!found) {
        cerr << "Имя не найдено.\n" << endl;
    }
}


void writeToFile(Address** phead) {
    Address* t = *phead;
    ofstream file1("Lip.txt");
    if (file1.fail()) {
        cerr << "Файл не открывается" << endl;
        exit(1);
    }
    cout << "Сохранение в файл" << endl;
    while (t) {
        file1 << t->name << " " << t->city << endl;
        t = t->next;
    }
    file1.close();
}

void readFromFile(Address** phead, Address** plast) {
    // Очистка списка перед чтением из файла
    while (*phead) {
        *plast = (*phead)->next;
        delete* phead;
        *phead = *plast;
    }
    *phead = *plast = nullptr;

    string name, city;
    ifstream file1("Lip.txt");
    if (!file1.is_open()) {
        cerr << "Ошибка открытия файла" << endl;
        exit(1);
    }

    while (file1 >> name >> city) {
        Address* t = new Address;
        t->name = name;
        t->city = city;
        t->prev = *plast;
        t->next = nullptr;

        if (*plast == nullptr) {
            *phead = t;
        }
        else {
            (*plast)->next = t;
        }

        *plast = t;
    }

    file1.close();
}

void addLEnd(Address*& head, Address*& tail) {
    // Create a new list L within this function
    Address* listLHead = nullptr;
    Address* listLTail = nullptr;
    Address* temp = nullptr;
    char more;

    do {
        // Create a new element
        temp = setElement();
        if (!temp) {
            cerr << "Ошибка выделения памяти.\n";
            return;
        }

        // Insert the element into the new list L
        if (listLHead == nullptr) {
            listLHead = temp;
            listLTail = temp;
        }
        else {
            listLTail->next = temp;
            temp->prev = listLTail;
            listLTail = temp;
        }

        cout << "Добавить еще один элемент в список L? (y/n): ";
        cin >> more;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

    } while (more == 'y' || more == 'Y');

    if (listLHead == nullptr) {
        cout << "Список L пуст.\n";
        return;
    }

    // Append list L to the main list
    if (head == nullptr) {
        head = listLHead;
        tail = listLTail;
    }
    else {
        tail->next = listLHead;
        listLHead->prev = tail;
        tail = listLTail;
    }
}
