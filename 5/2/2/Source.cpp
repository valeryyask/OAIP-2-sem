#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// Перечисления для специальностей
enum Specialties {
    INFORMATICS,
    ELECTRICAL_ENGINEERING,
    MECHANICS,
    CHEMISTRY,
    CONSTRUCTION
};

// Структура для хранения информации о вузе
struct University {
    string name;
    string address;
    union {
        unsigned int competitionScores[5]; // Массив для баллов за конкурс по каждой специальности
        struct {
            unsigned int informatics;
            unsigned int electricalEngineering;
            unsigned int mechanics;
            unsigned int chemistry;
            unsigned int construction;
        } competitionScoresIndividual;
    };
    float tuitionFee; // Размер оплаты при договорном обучении
};

const int MAX_UNIVERSITIES = 100;
int numUniversities = 0;
University universities[MAX_UNIVERSITIES];

// Функция для записи данных в файл
void writeDataToFile() {
    ofstream file("universities.txt");
    if (file.is_open()) {
        file << numUniversities << endl;
        for (int i = 0; i < numUniversities; ++i) {
            file << universities[i].name << endl;
            file << universities[i].address << endl;
            for (int j = 0; j < 5; ++j) {
                file << universities[i].competitionScores[j] << " ";
            }
            file << endl;
            file << universities[i].tuitionFee << endl;
        }
        file.close();
    }
    else {
        cout << "Ошибка открытия файла для записи данных!" << endl;
    }
}

// Функция для чтения данных из файла
void readDataFromFile() {
    ifstream file("universities.txt");
    if (file.is_open()) {
        file >> numUniversities;
        file.ignore(); // Пропускаем символ новой строки после чтения числа вузов
        for (int i = 0; i < numUniversities; ++i) {
            getline(file, universities[i].name);
            getline(file, universities[i].address);
            for (int j = 0; j < 5; ++j) {
                file >> universities[i].competitionScores[j];
            }
            file >> universities[i].tuitionFee;
            file.ignore(); // Пропускаем символ новой строки после чтения оплаты обучения
        }
        file.close();
    }
    else {
        cout << "Ошибка открытия файла для чтения данных!" << endl;
    }
}

// Функция для проверки названия вуза
bool isValidUniversityName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false; // Название содержит недопустимые символы
        }
    }
    return true;
}

// Функция для проверки количества специальностей
bool isValidSpecialtiesCount(int count) {
    return count >= 0 && count <= 5; // Количество специальностей не превышает 5 и не отрицательное
}

// Функция для проверки баллов за конкурс
bool isValidCompetitionScore(int score) {
    return score >= 0 && score <= 400; // Баллы не превышают 400 и не отрицательные
}

// Функция для добавления вуза
void addUniversity() {
    if (numUniversities < MAX_UNIVERSITIES) {
        University u;

        cout << "Введите название вуза: ";
        getline(cin, u.name);
        if (!isValidUniversityName(u.name)) {
            cout << "Название вуза содержит недопустимые символы!" << endl;
            return;
        }

        cout << "Введите адрес вуза: ";
        getline(cin, u.address);

        // Ввод баллов за конкурс по каждой специальности
        cout << "Введите баллы за конкурс по специальностям:" << endl;
        for (int i = 0; i < 5; ++i) {
            int score;
            cout << "Введите баллы за конкурс по специальности " << i + 1 << ": ";
            cin >> score;
            if (!isValidCompetitionScore(score)) {
                cout << "Некорректные баллы!" << endl;
                return;
            }
            u.competitionScores[i] = score; // Сохраняем баллы
        }

        cout << "Введите размер оплаты при договорном обучении: ";
        cin >> u.tuitionFee;

        universities[numUniversities++] = u;

        writeDataToFile(); // Записываем данные в файл
    }
    else {
        cout << "Достигнуто максимальное количество вузов!" << endl;
    }
}

// Функция для вывода информации о вузе
void displayUniversity(const University& u) {
    cout << "Название: " << u.name << endl;
    cout << "Адрес: " << u.address << endl;
    cout << "Баллы за конкурс по специальностям:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "Специальность " << i + 1 << ": " << u.competitionScores[i] << endl;
    }
    cout << "Размер оплаты при договорном обучении: " << u.tuitionFee << endl;
}

// Функция для вывода списка вузов
void displayUniversities() {
    for (int i = 0; i < numUniversities; ++i) {
        cout << "Вуз " << i + 1 << ":" << endl;
        displayUniversity(universities[i]);
    }
}

// Функция для удаления вуза
void deleteUniversity() {
    cout << "Введите название вуза для удаления: ";
    string name;
    getline(cin, name);
    for (int i = 0; i < numUniversities; ++i) {
        if (universities[i].name == name) {
            for (int j = i; j < numUniversities - 1; ++j) {
                universities[j] = universities[j + 1];
            }
            --numUniversities;
            cout << "Вуз успешно удален!" << endl;
            writeDataToFile(); // После удаления записываем изменения в файл
            return;
        }
    }
    cout << "Вуз не найден!" << endl;
}

// Функция для поиска вуза с минимальным конкурсом
void searchUniversityByMinimumCompetition() {
    int specialty;
    cout << "Введите номер специальности для поиска вуза с минимальным конкурсом: ";
    cin >> specialty;

    int minCompetition = 401; // Инициализация значением выше максимального балла (400)
    University* minCompetitionUniversity = nullptr;

    for (int i = 0; i < numUniversities; ++i) {
        if (universities[i].competitionScores[specialty - 1] < minCompetition) {
            minCompetition = universities[i].competitionScores[specialty - 1];
            minCompetitionUniversity = &universities[i];
        }
    }

    if (minCompetitionUniversity != nullptr) {
        cout << "Вуз с минимальным конкурсом по специальности " << specialty << ":" << endl;
        displayUniversity(*minCompetitionUniversity);
    }
    else {
        cout << "Вузы не найдены!" << endl;
    }
}

// Функция для вывода меню
void displayMenu() {
    cout << "Меню:" << endl;
    cout << "1. Добавить вуз" << endl;
    cout << "2. Вывести список вузов" << endl;
    cout << "3. Удалить вуз" << endl;
    cout << "4. Найти вуз с минимальным конкурсом" << endl;
    cout << "5. Прочитать данные из файла" << endl;
    cout << "6. Выход" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int choice;
    do {
        displayMenu();
        cout << "Введите ваш выбор: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addUniversity();
            break;
        case 2:
            displayUniversities();
            break;
        case 3:
            deleteUniversity();
            break;
        case 4:
            searchUniversityByMinimumCompetition();
            break;
        case 5:
            readDataFromFile(); // Чтение данных из файла
            cout << "Данные успешно загружены из файла." << endl;
            break;
        case 6:
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Некорректный выбор! Попробуйте еще раз." << endl;
            break;
        }

    } while (choice != 6);

    return 0;
}