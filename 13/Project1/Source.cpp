#include "Header.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <cctype> // ��� ������������� ������� isdigit
using namespace std;

struct AAA {
    int key;
    char* mas;
    AAA(int k, char* z) {
        key = k;  mas = z;
    }
    AAA() {}
};

int key(void* d) {
    AAA* f = (AAA*)d;
    return f->key;
}

void AAA_print(void* d) {
    cout << " ���� " << ((AAA*)d)->key << " - " << ((AAA*)d)->mas << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    clock_t start, end;
    double searching_time;
    AAA a1(1, (char*)"one"), a2(2, (char*)"two"), a3(4, (char*)"three"), a4(2, (char*)"fo");
    int siz = 10, choice, k = 1; // ����������: ��������� ��������� ��������� � 1

    for (;;) {
        cout << "������� ������ ���-�������: ";
        string input;
        cin >> input;

        // ��������� ������ ������ � ������ �� ������� ����
        bool allDigits = true;
        for (char c : input) {
            if (!isdigit(c)) {
                allDigits = false;
                break;
            }
        }

        // ���� ��� ������� - �����, ����������� ������ � int � ������� �� �����
        if (allDigits) {
            siz = stoi(input);
            cout << "������ ���-�������: " << siz << endl;
            break;
        }
        else {
            cout << "������: ������� ������������ �������. ����������, ������� �����." << endl;
            cin.clear(); // ���������� ���� ������ �����

            // ������� ����� ����� �� ������� ����� ������
            while (cin.get() != '\n') {
                continue;
            }
        }
    }

    Object H = create(siz, key);

    for (;;) {
        cout << "1 - ����� ���-�������" << endl;
        cout << "2 - ���������� ��������" << endl;
        cout << "3 - �������� ��������" << endl;
        cout << "4 - ����� ��������" << endl;
        cout << "0 - �����" << endl;

        cout << "�������� �����: ";
        cin >> choice;

        // �������� �� ���� �������
        if (cin.fail()) {
            cout << "������: ������ ������������ ������. ����������, ������� �����." << endl;
            cin.clear(); // ���������� ���� ������ �����

            // ������� ����� ����� �� ������� ����� ������
            while (cin.get() != '\n') {
                continue;
            }
            continue; // ��������� � ��������� �������� �����
        }

        switch (choice) {
        case 0:  exit(0);
        case 1:
            cout << "���-�������:" << endl;
            H.scan(AAA_print);
            break;
        case 2:
        {
            AAA* a = new AAA;
            string keyInput; // ���������� ������ ��� ����� �����
            char* str = new char[100]; // ����������� ������ ������ ��� ������

            cout << "������� ����: ";
            cin >> keyInput;

            try {
                a->key = stoi(keyInput); // ����������� ������ ���������� ����� � int
            }
            catch (const invalid_argument& e) {
                cout << "������: ������ ������������ ����. ����������, ������� �����." << endl;
                break; // ������� �� ����� case 2
            }

            cout << "������� ������: ";
            cin.ignore(); // ������� ����� ����� ����� �������������� getline
            cin.getline(str, 100); // ��������� ������ � ���������
            a->mas = str;

            if (H.N == H.size) {
                cout << "������: ������� ���������. ���������� �������� ����� �������." << endl;
                break; // ������� �� ����� case 2
            }
            else {
                H.insert(a);
                cout << "������� ������� ��������" << endl;
            }
        }
        break;
        case 3:
        {
            cout << "������� ���� ��� ��������: ";
            cin >> k; // ����������: ���� ����� ��� ��������
            H.deleteByKey(k);
        }
        break;
        case 4:
        {
            cout << "������� ���� ��� ������: ";
            cin >> k; // ����������: ���� ����� ��� ������
            start = clock();
            if (H.search(k) == NULL)
                cout << "������� �� ������" << endl;
            else
                AAA_print(H.search(k));

            end = clock();
            searching_time = (double)(end - start) / CLOCKS_PER_SEC;
            cout << "����� ������: " << searching_time << endl;
        }
        break;
        default:
            cout << "������: �������� �����. ����������, �������� �������� �� ������." << endl;
        }
    }

    return 0;
}
