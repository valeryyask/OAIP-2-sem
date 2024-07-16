#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Для функций рандомизации
#include <ctime>   // Для генерации случайного числа seed
#include <sstream> // Для преобразования строки в число

using namespace std;

class HashTable {
public:
    struct Node {
        string email;
        string surname;
        int year;

        Node(const string& e, const string& s, int y) : email(e), surname(s), year(y) {}
    };

private:
    size_t m_length;
    vector<vector<Node*>> m_data;

    // Хеш-функция для ключа (года создания)
    int hash(int key) {
        return key % m_length;
    }

public:
    HashTable(size_t length) : m_length(length) {
        m_data.resize(length);
    }

    // Добавление элемента
    void add(const string& email, const string& surname, int year) {
        int hash_val = hash(year); // Хешируем год создания
        m_data[hash_val].push_back(new Node(email, surname, year));
    }

    // Удаление элемента по году создания
    void remove(int year) {
        int hash_val = hash(year);
        vector<Node*>& bucket = m_data[hash_val];
        for (size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i]->year == year) {
                delete bucket[i];
                bucket.erase(bucket.begin() + i);
                return;
            }
        }
        cout << "Элемент не найден." << endl;
    }

    // Поиск элемента по году создания
    Node* search(int year) {
        int hash_val = hash(year);
        vector<Node*>& bucket = m_data[hash_val];
        for (Node* node : bucket) {
            if (node->year == year) {
                return node;
            }
        }
        return nullptr;
    }

    // Вывод таблицы
    void print() {
        for (size_t i = 0; i < m_length; ++i) {
            cout << "Bucket " << i << ": ";
            for (Node* node : m_data[i]) {
                cout << "(" << node->email << ", " << node->surname << ", " << node->year << ") ";
            }
            cout << endl;
        }
    }
};
// Функция для проверки корректности ввода года
int getValidYearInput() {
    string inputStr;
    int input;
    while (true) {
        getline(cin, inputStr); // Считываем ввод в строку
        stringstream ss(inputStr);
        if (ss >> input && ss.eof()) { // Пытаемся преобразовать строку в число и проверяем, что поток закончился
            if (input >= 1000 && input <= 2024) { // Проверяем, что год состоит из четырех цифр
                break;
            }
            else {
                cout << "Ошибка: год должен состоять из четырех цифр меньше 2024." << endl;
            }
        }
        cout << "" << endl;
    }
    return input;
}

// Функция для проверки корректности ввода числа
int getValidInput() {
    string inputStr;
    int input;
    while (true) {
        getline(cin, inputStr); // Считываем ввод в строку
        stringstream ss(inputStr);
        if (ss >> input && ss.eof()) { // Пытаемся преобразовать строку в число и проверяем, что поток закончился
            break;
        }
        cout << "Ошибка: введите число." << endl;
    }
    return input;
}

// Функция для проверки, что строка состоит из одного слова без пробелов, но может содержать дефис

bool isValidSurname(const string& str) {
    if (str.empty()) {
        return false; // Если строка пустая, возвращаем false
    }

    bool hasSpace = false;
    for (char c : str) {
        if (isspace(c)) {
            hasSpace = true; // Если хоть один символ является пробелом, устанавливаем флаг
        }
        if (c == '-') {
            continue; // Если символ - дефис, переходим к следующему символу
        }
        if (!isalpha(c)) {
            return false; // Если символ не является буквой или дефисом, возвращаем false
        }
    }
    return !hasSpace; // Возвращаем true, если в строке нет пробелов
}



int main() {
    setlocale(0, "");
    srand(time(nullptr)); // Устанавливаем seed для генерации случайных чисел

    size_t table_size;
    cout << "Введите размер хеш-таблицы: ";
    table_size = getValidInput(); // Используем функцию для проверки ввода

    HashTable table(table_size);

    int choice;
    while (true) {
        cout << "\nВыберите действие:\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Найти элемент\n";
        cout << "4. Вывести таблицу\n";
        cout << "5. Выйти\n";
        cout << "Выбор: ";
        choice = getValidInput(); // Используем функцию для проверки ввода

        switch (choice) {
            // Остальная часть кода остается неизменной

        case 1: {
            string email, surname;
            cout << "Введите адрес: ";
            getline(cin, email); // Считываем строку адреса
            do {
                cout << "Введите фамилию абонента: ";
                getline(cin, surname); // Считываем строку фамилии
                if (!isValidSurname(surname)) {
                    cout << "Ошибка: фамилия должна состоять из одного слова без пробелов, но может содержать дефис. Пожалуйста, введите ее еще раз." << endl;
                }
            } while (!isValidSurname(surname)); // Повторяем ввод, пока фамилия не удовлетворяет требованиям
            int year;
            cout << "Введите год создания: ";
            year = getValidYearInput(); // Используем функцию для проверки ввода года
            table.add(email, surname, year);
            break;
        }

        case 2: {
            cout << "Введите год создания элемента для удаления: ";
            int year = getValidYearInput(); // Используем функцию для проверки ввода года
            table.remove(year);
            break;
        }
        case 3: {
            cout << "Введите год создания элемента для поиска: ";
            int year = getValidYearInput(); // Используем функцию для проверки ввода года
            HashTable::Node* result = table.search(year);
            if (result) {
                cout << "Найден: " << result->surname << ", " << result->email << ", " << result->year << endl;
            }
            else {
                cout << "Элемент не найден." << endl;
            }
            break;
        }

        case 4:
            cout << "Хеш-таблица:" << endl;
            table.print();
            break;
        case 5:
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    }

    return 0;
}
