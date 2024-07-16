#include <iostream>
#include <windows.h>
#include <regex>
#define MAX_SIZE_ARRAY 30

using namespace std;

int iterInputData = 0;
enum LisOfSpecialties {
    Unkown = 0, Accountant, Cook, Designer, Doctor, Economist, Engineer, Florist, Jeweler, Journalist, Teacher, Max
};

struct AbiturientHandbook {
    int numberSpecialties;
    string nameUniversity;
    string adress;
    string payment;
    LisOfSpecialties listSpecialist;
    unsigned contestScoreBit : 9;
};

AbiturientHandbook human[MAX_SIZE_ARRAY];

void InputData(AbiturientHandbook human[]) {
    string buffContestYearBit;
    for (iterInputData; iterInputData < MAX_SIZE_ARRAY; iterInputData++) {
        do {
            cout << "Выберите специальность: Accountant, Cook, Designer, Doctor, Economist, Engineer, Florist, Jeweler, Journalist, Teacher\n";
            cin >> human[iterInputData].numberSpecialties;
            if (human[iterInputData].numberSpecialties < 1 || human[iterInputData].numberSpecialties > 10) {
                cout << "Ошибка: Номер специальности должен быть от 1 до 10.\n";
            }
        } while (human[iterInputData].numberSpecialties < 1 || human[iterInputData].numberSpecialties > 10);

        cout << "Введите название вуза: ";
        cin >> human[iterInputData].nameUniversity;
        while (!regex_match(human[iterInputData].nameUniversity, regex("^[A-Za-z]+$"))) {
            cout << "Неверный формат. Пожалуйста, введите только буквы: ";
            cin >> human[iterInputData].nameUniversity;
        }

        cout << "Введите адрес вуза: ";
        cin.ignore();
        getline(cin, human[iterInputData].adress);
        while (!regex_match(human[iterInputData].adress, regex("^[A-Za-z0-9,\\s]+$"))) {
            cout << "Неверный формат. Пожалуйста, введите буквы и цифры, разделенные запятой или пробелом: ";
            getline(cin, human[iterInputData].adress);
        }

        cout << "Введите стоимость оплаты за обучение (платная форма): ";
        cin >> human[iterInputData].payment;
        while (!regex_match(human[iterInputData].payment, regex("^[0-9]+$"))) {
            cout << "Неверный формат. Пожалуйста, введите только цифры: ";
            cin >> human[iterInputData].payment;
        }

        bool error;
        do {
            cout << "Введите конкурс прошлого года (от 0 до 400): ";
            cin >> buffContestYearBit;
            error = false;
            for (int i = 0; i < buffContestYearBit.length(); i++) {
                if (buffContestYearBit[i] < '0' || buffContestYearBit[i] > '9') {
                    error = true;
                }
            }
            if (!error && (stoi(buffContestYearBit) < 0 || stoi(buffContestYearBit) > 400)) {
                error = true;
            }
        } while (error);

        human[iterInputData].contestScoreBit = stol(buffContestYearBit);

        cout << "Продолжаем ввод?: да(1), нет(любая кнопка)\n";
        int outInputData;
        cin >> outInputData;
        if (outInputData != 1)
            break;
    }
    cout << "Информация добавлена!\n\n";
}

void PrintData(AbiturientHandbook human[]) {
    for (int i = 0; i < iterInputData + 1; i++) {
        cout << "\n\t\tСтраница " << i + 1 << "\n\n";
        cout << "Специальность: " << human[i].numberSpecialties << '\n';
        cout << "Название университета: " << human[i].nameUniversity << '\n';
        cout << "Адрес университета: " << human[i].adress << '\n';
        cout << "Стоимость оплаты: " << human[i].payment << '\n';
        cout << "Конкурс прошлого года: " << human[i].contestScoreBit << "\n\n";
    }
}

void Delete(AbiturientHandbook human[]) {
    cout << "Выберите, какую страницу нужно удалить: \n\n";
    PrintData(human);
    int deleteFromBook;
    cin >> deleteFromBook;
    if (deleteFromBook > iterInputData)
        return;
    for (int del = deleteFromBook - 1; del < iterInputData; del++)
        human[del] = human[del + 1];
    iterInputData--;
    cout << "\n\n\t\tЭлемент удален!\n\n";
}

void Find(AbiturientHandbook human[]) {
    cout << "\n\nВведите конкурс балла: ";
    unsigned searchScore;
    cin >> searchScore;
    bool flag = false;
    for (int j = 0; j < iterInputData; j++) {
        if (searchScore >= human[j].contestScoreBit) {
            cout << "Найдена запись: \n";
            cout << "\n\t\tСтраница " << j + 1 << "\n\n";
            cout << "Специальность: " << human[j].numberSpecialties << '\n';
            cout << "Название университета: " << human[j].nameUniversity << '\n';
            cout << "Адрес университета: " << human[j].adress << '\n';
            cout << "Стоимость оплаты: " << human[j].payment << '\n';
            cout << "Конкурс прошлого года: " << human[j].contestScoreBit << "\n\n";
            flag = true;
        }
    }
    if (!flag)
        cout << "Записей не найдено!\n\n";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;
    do {
        cout << "Выберите действие:\n1 - ввод с клавиатуры\n2 - вывод на экран\n3 - удаление\n4 - поиск элементов\n5 - выход\n";
        cin >> choice;
        switch (choice) {
        case 1: {
            InputData(human);
            break;
        }
        case 2: {
            PrintData(human);
            break;
        }
        case 3: {
            Delete(human);
            break;
        }
        case 4: {
            Find(human);
            break;
        }
        case 5: {
            exit(0);
        }
        default:
            cout << "Проверьте введенные данные!\n\n";
            break;
        }
    } while (choice != 5);

    return 0;
}