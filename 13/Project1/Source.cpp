#include "Header.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <cctype> // Для использования функции isdigit
using namespace std;

struct AAA {
    int key;
    char* mas;
    AAA(int k, char* z) {
        key = k;  mas = z;
    }
    AAA() {}
};

int key(void* d) {
    AAA* f = (AAA*)d;
    return f->key;
}

void AAA_print(void* d) {
    cout << " ключ " << ((AAA*)d)->key << " - " << ((AAA*)d)->mas << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    clock_t start, end;
    double searching_time;
    AAA a1(1, (char*)"one"), a2(2, (char*)"two"), a3(4, (char*)"three"), a4(2, (char*)"fo");
    int siz = 10, choice, k = 1; // Исправлено: начальная нумерация элементов с 1

    for (;;) {
        cout << "Введите размер хеш-таблицы: ";
        string input;
        cin >> input;

        // Проверяем каждый символ в строке на предмет цифр
        bool allDigits = true;
        for (char c : input) {
            if (!isdigit(c)) {
                allDigits = false;
                break;
            }
        }

        // Если все символы - цифры, преобразуем строку в int и выходим из цикла
        if (allDigits) {
            siz = stoi(input);
            cout << "Размер хеш-таблицы: " << siz << endl;
            break;
        }
        else {
            cout << "Ошибка: введены недопустимые символы. Пожалуйста, введите число." << endl;
            cin.clear(); // Сбрасываем флаг ошибки ввода

            // Очищаем буфер ввода до символа новой строки
            while (cin.get() != '\n') {
                continue;
            }
        }
    }

    Object H = create(siz, key);

    for (;;) {
        cout << "1 - вывод хеш-таблицы" << endl;
        cout << "2 - добавление элемента" << endl;
        cout << "3 - удаление элемента" << endl;
        cout << "4 - поиск элемента" << endl;
        cout << "0 - выход" << endl;

        cout << "Сделайте выбор: ";
        cin >> choice;

        // Проверка на ввод символа
        if (cin.fail()) {
            cout << "Ошибка: введен недопустимый символ. Пожалуйста, введите число." << endl;
            cin.clear(); // Сбрасываем флаг ошибки ввода

            // Очищаем буфер ввода до символа новой строки
            while (cin.get() != '\n') {
                continue;
            }
            continue; // Переходим к следующей итерации цикла
        }

        switch (choice) {
        case 0:  exit(0);
        case 1:
            cout << "Хеш-таблица:" << endl;
            H.scan(AAA_print);
            break;
        case 2:
        {
            AAA* a = new AAA;
            string keyInput; // Используем строку для ввода ключа
            char* str = new char[100]; // Увеличиваем размер буфера для строки

            cout << "Введите ключ: ";
            cin >> keyInput;

            try {
                a->key = stoi(keyInput); // Преобразуем строку введенного ключа в int
            }
            catch (const invalid_argument& e) {
                cout << "Ошибка: введен недопустимый ключ. Пожалуйста, введите число." << endl;
                break; // Выходим из блока case 2
            }

            cout << "Введите строку: ";
            cin.ignore(); // Очищаем буфер ввода перед использованием getline
            cin.getline(str, 100); // Считываем строку с пробелами
            a->mas = str;

            if (H.N == H.size) {
                cout << "Ошибка: таблица заполнена. Невозможно добавить новый элемент." << endl;
                break; // Выходим из блока case 2
            }
            else {
                H.insert(a);
                cout << "Элемент успешно добавлен" << endl;
            }
        }
        break;
        case 3:
        {
            cout << "Введите ключ для удаления: ";
            cin >> k; // Исправлено: ввод ключа для удаления
            H.deleteByKey(k);
        }
        break;
        case 4:
        {
            cout << "Введите ключ для поиска: ";
            cin >> k; // Исправлено: ввод ключа для поиска
            start = clock();
            if (H.search(k) == NULL)
                cout << "Элемент не найден" << endl;
            else
                AAA_print(H.search(k));

            end = clock();
            searching_time = (double)(end - start) / CLOCKS_PER_SEC;
            cout << "Время поиска: " << searching_time << endl;
        }
        break;
        default:
            cout << "Ошибка: неверный выбор. Пожалуйста, выберите действие из списка." << endl;
        }
    }

    return 0;
}
