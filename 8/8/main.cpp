#include <iostream>
#include <locale>
#include "queue.h"

void menu() {
    std::cout << "Меню:\n";
    std::cout << "1 - Ввод очереди (максимальный размер, ввод элементов очереди)\n";
    std::cout << "2 - Вывод очереди после удаления двух элементов очереди\n";
    std::cout << "3 - Удаление элемента\n";
    std::cout << "4 - Очистка очереди\n";
    std::cout << "5 - Вывод первого элемента очереди\n";
    std::cout << "6 - Добавление элемента и вывод обновленной очереди\n";
    std::cout << "7 - Вывод очереди без удаления элементов\n";
    std::cout << "8 - Выход из программы\n";
    std::cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Queue queue;
    bool initialized = false;
    char etalon;

    while (true) {
        menu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int capacity;
            std::cout << "Введите максимальный размер очереди: ";
            std::cin >> capacity;

            initQueue(queue, capacity);
            initialized = true;

            std::cout << "Введите эталонный символ: ";
            std::cin >> etalon;
            queue.etalon = etalon;

            std::cin.ignore();
            std::cout << "Введите символы для добавления в очередь (для завершения ввода введите 0): ";
            char input;
            while (true) {
                std::cin >> input;
                if (input == '0') {
                    break;
                }
                enqueue(queue, input);
            }
            break;
        }
        case 2: {
            if (!initialized) {
                std::cerr << "Очередь не инициализирована." << std::endl;
                break;
            }
            if (!queue.hasEtalon) {
                std::cerr << "Очередь не содержит эталонный элемент." << std::endl;
                break;
            }
            dequeue(queue);
            dequeue(queue);
            std::cout << "Размер очереди после удаления двух элементов: " << getSize(queue) << std::endl;
            printQueue(queue);
            break;
        }
        case 3: {
            if (!initialized) {
                std::cerr << "Очередь не инициализирована." << std::endl;
                break;
            }
            char removedElement = dequeue(queue);
            if (removedElement != '\0') {
                std::cout << "Удаленный элемент: " << removedElement << std::endl;
            }
            break;
        }
        case 4: {
            if (!initialized) {
                std::cerr << "Очередь не инициализирована." << std::endl;
                break;
            }
            clearQueue(queue);
            std::cout << "Очередь очищена." << std::endl;
            break;
        }
        case 5: {
            if (!initialized) {
                std::cerr << "Очередь не инициализирована." << std::endl;
                break;
            }
            if (isEmpty(queue)) {
                std::cerr << "Очередь пуста." << std::endl;
            }
            else {
                std::cout << "Первый элемент очереди: " << queue.items[queue.front] << std::endl;
            }
            break;
        }
        case 6: {
            if (!initialized) {
                std::cerr << "Очередь не инициализирована." << std::endl;
                break;
            }
            char item;
            std::cout << "Введите элемент для добавления: ";
            std::cin >> item;
            enqueueAndPrint(queue, item);
            break;
        }
        case 7: {
            if (!initialized) {
                std::cerr << "Очередь не инициализирована." << std::endl;
                break;
            }
            displayQueue(queue);
            break;
        }
        case 8: {
            if (initialized) {
                destroyQueue(queue);
            }
            std::cout << "Выход из программы." << std::endl;
            return 0;
        }
        default: {
            std::cerr << "Неверный выбор. Пожалуйста, выберите снова." << std::endl;
            break;
        }
        }
    }
    return 0;
}
