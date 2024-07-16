#include <iostream>
#include <fstream>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");
    std::ofstream fileF1("F1.txt"); // ������� ���� F1 ��� ������

    if (!fileF1) {
        std::cerr << "�� ������� ������� ���� F1." << std::endl;
        return 1;
    }

    // ���������� ���������� � ���� F1
    fileF1 << "������ 1" << std::endl;
    fileF1 << "������ 2" << std::endl;
    fileF1 << "������ 3" << std::endl;
    fileF1 << "������ 4" << std::endl;
    fileF1 << "������ 5" << std::endl;
    fileF1 << "������ 6" << std::endl;
    fileF1 << "������ 7 ����� ������� ����" << std::endl;
    fileF1 << "������ 8 ���� ������ ����" << std::endl;
    fileF1 << "������ 8 ������ �� ��� " << std::endl;
    fileF1 << "������ 8 ����� �����" << std::endl;
    fileF1 << "������ 8 ������ � �" << std::endl;
    fileF1 << "������ 8 ���� ���� �����" << std::endl;
    fileF1 << "������ 8 ���8��� ��" << std::endl;


    fileF1.close();

    int k;
    std::cout << "������� �������� k: ";
    std::cin >> k;

    std::ifstream fileF1Read("F1.txt"); // ��������� ���� F1 ��� ������
    std::ofstream fileF2("F2.txt"); // ������� ���� F2 ��� ������

    if (!fileF1Read) {
        std::cerr << "�� ������� ������� ���� F1 ��� ������." << std::endl;
        return 1;
    }

    if (!fileF2) {
        std::cerr << "�� ������� ������� ���� F2." << std::endl;
        return 1;
    }

    std::string line;
    int lineCount = 0;

    // �������� ������ �� F1 � F2, ������� � ������ k �� k + 3
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

    std::cout << "����������� ����� ���������." << std::endl;

    return 0;
}