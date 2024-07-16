#include "stack.h"

int main() {
    Stack stack;

    int choice;
    int data;

    setlocale(LC_ALL, "Russian");

    while (true) {
        std::cout << "\n1. Добавить элемент в стек\n"
            "2. Удалить элемент из стека\n"
            "3. Просмотреть верхний элемент стека\n"
            "4. Удалить первый повторяющийся элемент стека\n"
            "5. Сохранить стек в файл\n"
            "6. Считать стек из файла\n"
            "7. Очистить стек\n"
            "8. Выйти\n"
            "9. Вывести стек на экран\n";


        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cerr << "Ошибка: Некорректный ввод. Введите число от 1 до 8." << std::endl;
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue; 
        }

        switch (choice) {
        case 1:
            std::cout << "Введите значение для добавления: ";
            std::cin >> data;
            stack.push(data);
            break;
        case 2:
            std::cout << "Удаленный элемент: " << stack.pop() << std::endl;
            break;
        case 3:
            std::cout << "Верхний элемент стека: " << stack.peek() << std::endl;
            break;
        case 4:
            stack.removeFirstDuplicate();
            std::cout << "Первый повторяющийся элемент удален (если найден).\n";
            break;
        case 5:
            stack.saveToFile("stack.txt");
            std::cout << "Стек сохранен в файле 'stack.txt'.\n";
            break;
        case 6:
            stack.clear();
            stack.readFromFile("stack.txt");
            std::cout << "Стек загружен из файла 'stack.txt'.\n";
            break;
        case 7:
            stack.clear();
            std::cout << "Стек очищен.\n";
            break;
        case 8:
            std::cout << "Программа завершена.\n";
            return 0;
        case 9:
            stack.printStack();
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    }

    return 0;
}
