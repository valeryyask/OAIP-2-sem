#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Структура, представляющая преподавателя
struct Teacher {
    string surname;   // Фамилия преподавателя
    string examName;  // Название экзамена
    string examDate;  // Дата экзамена
};

// Функция для ввода информации о преподавателе с клавиатуры
void inputTeacherInfo(Teacher& teacher) {
    cout << "Введите фамилию преподавателя: ";
    cin >> teacher.surname;
    cout << "Введите название экзамена: ";
    cin >> teacher.examName;
    cout << "Введите дату экзамена: ";
    cin >> teacher.examDate;
}

// Функция для вывода информации о преподавателе
void printTeacherInfo(const Teacher& teacher) {
    cout << "Фамилия преподавателя: " << teacher.surname << endl;
    cout << "Название экзамена: " << teacher.examName << endl;
    cout << "Дата экзамена: " << teacher.examDate << endl;
}

// Функция для удаления заданного преподавателя из массива
void deleteTeacher(Teacher teachers[], int& numTeachers, const string& surname) {
    for (int i = 0; i < numTeachers; ++i) {
        if (teachers[i].surname == surname) {
            for (int j = i; j < numTeachers - 1; ++j) {
                teachers[j] = teachers[j + 1];
            }
            numTeachers--;
            cout << "Преподаватель " << surname << " удален." << endl;
            return;
        }
    }
    cout << "Преподаватель с фамилией " << surname << " не найден." << endl;
}

// Функция для поиска преподавателя по фамилии
void findTeacher(const Teacher teachers[], int numTeachers, const string& surname) {
    for (int i = 0; i < numTeachers; ++i) {
        if (teachers[i].surname == surname) {
            cout << "Информация о преподавателе:" << endl;
            printTeacherInfo(teachers[i]);
            return;
        }
    }
    cout << "Преподаватель с фамилией " << surname << " не найден." << endl;
}

// Функция для записи информации о преподавателях в файл
void writeToFile(const Teacher teachers[], int numTeachers, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < numTeachers; ++i) {
            file << teachers[i].surname << " "
                << teachers[i].examName << " "
                << teachers[i].examDate << endl;
        }
        cout << "Данные записаны в файл." << endl;
        file.close();
    }
    else {
        cout << "Ошибка открытия файла для записи." << endl;
    }
}

// Функция для чтения информации о преподавателях из файла
void readFromFile(Teacher teachers[], int& numTeachers, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        numTeachers = 0;
        while (!file.eof()) {
            file >> teachers[numTeachers].surname
                >> teachers[numTeachers].examName
                >> teachers[numTeachers].examDate;
            numTeachers++;
        }
        numTeachers--;  // Исправление лишнего увеличения numTeachers на 1
        cout << "Данные прочитаны из файла." << endl;
        file.close();
    }
    else {
        cout << "Ошибка открытия файла для чтения." << endl;
    }
}

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");
    string surnameToFind;
    string surnameToDelete;
    const int MAX_TEACHERS = 100;
    Teacher teachers[MAX_TEACHERS];
    int numTeachers = 0;

    int choice;
    string filename;

    do {
        cout << "\nМеню:" << endl;
        cout << "1. Ввод информации о преподавателе с клавиатуры" << endl;
        cout << "2. Вывод информации о преподавателях" << endl;
        cout << "3. Удаление преподавателя по фамилии" << endl;
        cout << "4. Поиск информации о преподавателе" << endl;
        cout << "5. Запись информации о преподавателях в файл" << endl;
        cout << "6. Чтение информации о преподавателях из файла" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (numTeachers < MAX_TEACHERS) {
                inputTeacherInfo(teachers[numTeachers]);
                numTeachers++;
            }
            else {
                cout << "Достигнуто максимальное количество преподавателей." << endl;
            }
            break;
        case 2:
            cout << "Информация о преподавателях:" << endl;
            for (int i = 0; i < numTeachers; ++i) {
                cout << "Преподаватель " << i + 1 << ":" << endl;
                printTeacherInfo(teachers[i]);
            }
            break;
        case 3:
            cout << "Введите фамилию преподавателя для удаления: ";
            cin >> surnameToDelete;
            deleteTeacher(teachers, numTeachers, surnameToDelete);
            break;
        case 4:
            cout << "Введите фамилию преподавателя для поиска: ";
            cin >> surnameToFind;
            findTeacher(teachers, numTeachers, surnameToFind);
            break;
        case 5:
            cout << "Введите имя файла для записи: ";
            cin >> filename;
            writeToFile(teachers, numTeachers, filename);
            break;
        case 6:
            cout << "Введите имя файла для чтения: ";
            cin >> filename;
            readFromFile(teachers, numTeachers, filename);
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
