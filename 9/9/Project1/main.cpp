#include <iostream>
#include "list.h"

using namespace std;

int main() {
    string s;
    int c;
    string dname;
    string fname;
    setlocale(LC_CTYPE, "Rus");
    Address* head = NULL;
    Address* last = NULL;
    short choose = 0;
    while (choose != 8) {
        cout << "¬ыберите действие:\n1 Ч ввод элемента;\n2 Ч вывод списка;\n3 Ч удаление элемента;\n4 Ч поиск элемента;"
            "\n5 Ч запись в файл;\n6 Ч чтение из файла;\n7 Ч добавление списка L в конец;\n8 Ч выход из программы.\n";

        do {
            getline(cin >> ws, s);
        } while (s.find_first_not_of(FOUND) != string::npos);

        c = stoi(s);

        switch (c) {
        case 1:
            insert(setElement(), &head, &last);
            break;
        case 2:
            outputList(&head, &last);
            break;
        case 3:
            do {
                cout << "¬ведите им€: ";
                getline(cin, dname);
                cin.ignore(cin.rdbuf()->in_avail());
                cin.clear();
            } while (dname.find_first_not_of(FOUND2) != string::npos);
            delet(dname, &head, &last);
            break;
        case 4:
            do {
                cout << "¬ведите им€: ";
                getline(cin, fname);
                cin.ignore(cin.rdbuf()->in_avail());
                cin.clear();
            } while (fname.find_first_not_of(FOUND2) != string::npos);
            find(fname, &head);
            break;
        case 5:
            writeToFile(&head);
            break;
        case 6:
            readFromFile(&head, &last);
            break;
        case 7:
            addLEnd(head, last);
            break;
        case 8:
            cout << "ƒо свидани€!\n";
            exit(0);
        }
    }
}
