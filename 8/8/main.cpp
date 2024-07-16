#include <iostream>
#include <locale>
#include "queue.h"

void menu() {
    std::cout << "����:\n";
    std::cout << "1 - ���� ������� (������������ ������, ���� ��������� �������)\n";
    std::cout << "2 - ����� ������� ����� �������� ���� ��������� �������\n";
    std::cout << "3 - �������� ��������\n";
    std::cout << "4 - ������� �������\n";
    std::cout << "5 - ����� ������� �������� �������\n";
    std::cout << "6 - ���������� �������� � ����� ����������� �������\n";
    std::cout << "7 - ����� ������� ��� �������� ���������\n";
    std::cout << "8 - ����� �� ���������\n";
    std::cout << "�������� �����: ";
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
            std::cout << "������� ������������ ������ �������: ";
            std::cin >> capacity;

            initQueue(queue, capacity);
            initialized = true;

            std::cout << "������� ��������� ������: ";
            std::cin >> etalon;
            queue.etalon = etalon;

            std::cin.ignore();
            std::cout << "������� ������� ��� ���������� � ������� (��� ���������� ����� ������� 0): ";
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
                std::cerr << "������� �� ����������������." << std::endl;
                break;
            }
            if (!queue.hasEtalon) {
                std::cerr << "������� �� �������� ��������� �������." << std::endl;
                break;
            }
            dequeue(queue);
            dequeue(queue);
            std::cout << "������ ������� ����� �������� ���� ���������: " << getSize(queue) << std::endl;
            printQueue(queue);
            break;
        }
        case 3: {
            if (!initialized) {
                std::cerr << "������� �� ����������������." << std::endl;
                break;
            }
            char removedElement = dequeue(queue);
            if (removedElement != '\0') {
                std::cout << "��������� �������: " << removedElement << std::endl;
            }
            break;
        }
        case 4: {
            if (!initialized) {
                std::cerr << "������� �� ����������������." << std::endl;
                break;
            }
            clearQueue(queue);
            std::cout << "������� �������." << std::endl;
            break;
        }
        case 5: {
            if (!initialized) {
                std::cerr << "������� �� ����������������." << std::endl;
                break;
            }
            if (isEmpty(queue)) {
                std::cerr << "������� �����." << std::endl;
            }
            else {
                std::cout << "������ ������� �������: " << queue.items[queue.front] << std::endl;
            }
            break;
        }
        case 6: {
            if (!initialized) {
                std::cerr << "������� �� ����������������." << std::endl;
                break;
            }
            char item;
            std::cout << "������� ������� ��� ����������: ";
            std::cin >> item;
            enqueueAndPrint(queue, item);
            break;
        }
        case 7: {
            if (!initialized) {
                std::cerr << "������� �� ����������������." << std::endl;
                break;
            }
            displayQueue(queue);
            break;
        }
        case 8: {
            if (initialized) {
                destroyQueue(queue);
            }
            std::cout << "����� �� ���������." << std::endl;
            return 0;
        }
        default: {
            std::cerr << "�������� �����. ����������, �������� �����." << std::endl;
            break;
        }
        }
    }
    return 0;
}
