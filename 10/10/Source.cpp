#include <iostream>

int S(int x) {
    if (x > 100) {
        return x + 10;
    }
    else {
        return S(S(x + 4));
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    int x;
    std::cout << "������� ����� ��������������� �������� x: ";
    std::cin >> x;

    if (x < 0) {
        std::cerr << "������: �������� ������ ���� ���������������." << std::endl;
        return 1;
    }

    int result = S(x);
    std::cout << "S(" << x << ") = " << result << std::endl;

    return 0;
}
