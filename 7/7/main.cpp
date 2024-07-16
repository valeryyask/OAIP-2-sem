#include "stack.h"

int main() {
    Stack stack;

    int choice;
    int data;

    setlocale(LC_ALL, "Russian");

    while (true) {
        std::cout << "\n1. �������� ������� � ����\n"
            "2. ������� ������� �� �����\n"
            "3. ����������� ������� ������� �����\n"
            "4. ������� ������ ������������� ������� �����\n"
            "5. ��������� ���� � ����\n"
            "6. ������� ���� �� �����\n"
            "7. �������� ����\n"
            "8. �����\n"
            "9. ������� ���� �� �����\n";


        std::cout << "�������� ��������: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cerr << "������: ������������ ����. ������� ����� �� 1 �� 8." << std::endl;
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue; 
        }

        switch (choice) {
        case 1:
            std::cout << "������� �������� ��� ����������: ";
            std::cin >> data;
            stack.push(data);
            break;
        case 2:
            std::cout << "��������� �������: " << stack.pop() << std::endl;
            break;
        case 3:
            std::cout << "������� ������� �����: " << stack.peek() << std::endl;
            break;
        case 4:
            stack.removeFirstDuplicate();
            std::cout << "������ ������������� ������� ������ (���� ������).\n";
            break;
        case 5:
            stack.saveToFile("stack.txt");
            std::cout << "���� �������� � ����� 'stack.txt'.\n";
            break;
        case 6:
            stack.clear();
            stack.readFromFile("stack.txt");
            std::cout << "���� �������� �� ����� 'stack.txt'.\n";
            break;
        case 7:
            stack.clear();
            std::cout << "���� ������.\n";
            break;
        case 8:
            std::cout << "��������� ���������.\n";
            return 0;
        case 9:
            stack.printStack();
            break;
        default:
            std::cout << "�������� �����. ���������� ��� ���.\n";
        }
    }

    return 0;
}
