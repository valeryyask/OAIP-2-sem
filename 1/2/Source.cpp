#include <iostream>
#include <bitset>

// ������� ��� �������� ����� �� ���������� ������� ��������� � ��������
template<typename... Args>
void decimalToBinary(Args... args) {
    setlocale(LC_ALL, "Russian");
    int values[] = { args... };
    for (int value : values) {
        std::bitset<32> binary(value);
        std::cout << "���������� ����� " << value << " � �������� �������: " << binary << std::endl;
    }
}

int main() {
    // ����� ������� � ������ ����������� ����������
    decimalToBinary(9);
    decimalToBinary(245, 2300);
    decimalToBinary(15, 87, 123);

    return 0;
}
