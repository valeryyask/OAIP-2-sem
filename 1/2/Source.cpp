#include <iostream>
#include <bitset>

// Функция для перевода чисел из десятичной системы счисления в двоичную
template<typename... Args>
void decimalToBinary(Args... args) {
    setlocale(LC_ALL, "Russian");
    int values[] = { args... };
    for (int value : values) {
        std::bitset<32> binary(value);
        std::cout << "Десятичное число " << value << " в двоичной системе: " << binary << std::endl;
    }
}

int main() {
    // Вызов функции с разным количеством параметров
    decimalToBinary(9);
    decimalToBinary(245, 2300);
    decimalToBinary(15, 87, 123);

    return 0;
}
