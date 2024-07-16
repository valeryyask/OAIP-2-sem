#include <iostream>
#include <cmath>

// ��������� 1: x^3 + x - 2
double equation1(double x) {
    return std::pow(x, 3) + x - 2;
}

// ��������� 2: sin(x) + 0.3
double equation2(double x) {
    return std::sin(x) + 0.3;
}

// ����� ���������
double bisectionMethod(double (*equation)(double), double a, double b, double epsilon) {
    double fa = equation(a);
    double fb = equation(b);

    if (fa * fb > 0) {
        std::cerr << "������: ��������� �������� �� ������������ ���������� ������ ���������." << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }

    while ((b - a) / 2 > epsilon) {
        double c = (a + b) / 2;
        double fc = equation(c);

        if (fc == 0.0) {
            return c;
        }
        else if (fa * fc < 0) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }
    }

    return (a + b) / 2;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double epsilon = 0.001;


    // ��������� 1: x^3 + x - 2
    double root1 = bisectionMethod(equation1, -2, 2, epsilon);

    // ��������� 2: sin(x) + 0.3
    double root2 = bisectionMethod(equation2, -2, 2, epsilon);

    // ����� �����������
    std::cout << "������ ��������� 1: " << root1 << std::endl;
    std::cout << "������ ��������� 2: " << root2 << std::endl;

    return 0;
}
