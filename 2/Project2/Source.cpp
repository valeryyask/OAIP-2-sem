#include <iostream>
#include <fstream>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");
    std::ofstream fileF1("F1.txt"); // Создаем файл F1 для записи

    if (!fileF1) {
        std::cerr << "Не удалось создать файл F1." << std::endl;
        return 1;
    }

    // Записываем информацию в файл F1
    fileF1 << "Строка 1" << std::endl;
    fileF1 << "Строка 2" << std::endl;
    fileF1 << "Строка 3" << std::endl;
    fileF1 << "Строка 4" << std::endl;
    fileF1 << "Строка 5" << std::endl;
    fileF1 << "Строка 6" << std::endl;
    fileF1 << "Строка 7 пуаои мтвпгит свпр" << std::endl;
    fileF1 << "Строка 8 впст сврыпо вспр" << std::endl;
    fileF1 << "Строка 8 рвпоми вп ови " << std::endl;
    fileF1 << "Строка 8 рвпои втсьт" << std::endl;
    fileF1 << "Строка 8 рывпои в и" << std::endl;
    fileF1 << "Строка 8 рвыь втмп лроьт" << std::endl;
    fileF1 << "Строка 8 рвш8нрт вс" << std::endl;


    fileF1.close();

    int k;
    std::cout << "Введите значение k: ";
    std::cin >> k;

    std::ifstream fileF1Read("F1.txt"); // Открываем файл F1 для чтения
    std::ofstream fileF2("F2.txt"); // Создаем файл F2 для записи

    if (!fileF1Read) {
        std::cerr << "Не удалось открыть файл F1 для чтения." << std::endl;
        return 1;
    }

    if (!fileF2) {
        std::cerr << "Не удалось создать файл F2." << std::endl;
        return 1;
    }

    std::string line;
    int lineCount = 0;

    // Копируем строки из F1 в F2, начиная с номера k до k + 3
    while (std::getline(fileF1Read, line)) {
        lineCount++;

        if (lineCount >= k && lineCount <= k + 3) {
            fileF2 << line << std::endl;
        }

        if (lineCount > k + 3) {
            break;
        }
    }

    fileF1Read.close();
    fileF2.close();

    std::cout << "Копирование строк завершено." << std::endl;

    return 0;
}