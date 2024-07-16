#include <iostream>
#include <windows.h>
#include <regex>
#define MAX_SIZE_ARRAY 30

using namespace std;

int iterInputData = 0;
enum LisOfSpecialties {
    Unkown = 0, Accountant, Cook, Designer, Doctor, Economist, Engineer, Florist, Jeweler, Journalist, Teacher, Max
};

struct AbiturientHandbook {
    int numberSpecialties;
    string nameUniversity;
    string adress;
    string payment;
    LisOfSpecialties listSpecialist;
    unsigned contestScoreBit : 9;
};

AbiturientHandbook human[MAX_SIZE_ARRAY];

void InputData(AbiturientHandbook human[]) {
    string buffContestYearBit;
    for (iterInputData; iterInputData < MAX_SIZE_ARRAY; iterInputData++) {
        do {
            cout << "�������� �������������: Accountant, Cook, Designer, Doctor, Economist, Engineer, Florist, Jeweler, Journalist, Teacher\n";
            cin >> human[iterInputData].numberSpecialties;
            if (human[iterInputData].numberSpecialties < 1 || human[iterInputData].numberSpecialties > 10) {
                cout << "������: ����� ������������� ������ ���� �� 1 �� 10.\n";
            }
        } while (human[iterInputData].numberSpecialties < 1 || human[iterInputData].numberSpecialties > 10);

        cout << "������� �������� ����: ";
        cin >> human[iterInputData].nameUniversity;
        while (!regex_match(human[iterInputData].nameUniversity, regex("^[A-Za-z]+$"))) {
            cout << "�������� ������. ����������, ������� ������ �����: ";
            cin >> human[iterInputData].nameUniversity;
        }

        cout << "������� ����� ����: ";
        cin.ignore();
        getline(cin, human[iterInputData].adress);
        while (!regex_match(human[iterInputData].adress, regex("^[A-Za-z0-9,\\s]+$"))) {
            cout << "�������� ������. ����������, ������� ����� � �����, ����������� ������� ��� ��������: ";
            getline(cin, human[iterInputData].adress);
        }

        cout << "������� ��������� ������ �� �������� (������� �����): ";
        cin >> human[iterInputData].payment;
        while (!regex_match(human[iterInputData].payment, regex("^[0-9]+$"))) {
            cout << "�������� ������. ����������, ������� ������ �����: ";
            cin >> human[iterInputData].payment;
        }

        bool error;
        do {
            cout << "������� ������� �������� ���� (�� 0 �� 400): ";
            cin >> buffContestYearBit;
            error = false;
            for (int i = 0; i < buffContestYearBit.length(); i++) {
                if (buffContestYearBit[i] < '0' || buffContestYearBit[i] > '9') {
                    error = true;
                }
            }
            if (!error && (stoi(buffContestYearBit) < 0 || stoi(buffContestYearBit) > 400)) {
                error = true;
            }
        } while (error);

        human[iterInputData].contestScoreBit = stol(buffContestYearBit);

        cout << "���������� ����?: ��(1), ���(����� ������)\n";
        int outInputData;
        cin >> outInputData;
        if (outInputData != 1)
            break;
    }
    cout << "���������� ���������!\n\n";
}

void PrintData(AbiturientHandbook human[]) {
    for (int i = 0; i < iterInputData + 1; i++) {
        cout << "\n\t\t�������� " << i + 1 << "\n\n";
        cout << "�������������: " << human[i].numberSpecialties << '\n';
        cout << "�������� ������������: " << human[i].nameUniversity << '\n';
        cout << "����� ������������: " << human[i].adress << '\n';
        cout << "��������� ������: " << human[i].payment << '\n';
        cout << "������� �������� ����: " << human[i].contestScoreBit << "\n\n";
    }
}

void Delete(AbiturientHandbook human[]) {
    cout << "��������, ����� �������� ����� �������: \n\n";
    PrintData(human);
    int deleteFromBook;
    cin >> deleteFromBook;
    if (deleteFromBook > iterInputData)
        return;
    for (int del = deleteFromBook - 1; del < iterInputData; del++)
        human[del] = human[del + 1];
    iterInputData--;
    cout << "\n\n\t\t������� ������!\n\n";
}

void Find(AbiturientHandbook human[]) {
    cout << "\n\n������� ������� �����: ";
    unsigned searchScore;
    cin >> searchScore;
    bool flag = false;
    for (int j = 0; j < iterInputData; j++) {
        if (searchScore >= human[j].contestScoreBit) {
            cout << "������� ������: \n";
            cout << "\n\t\t�������� " << j + 1 << "\n\n";
            cout << "�������������: " << human[j].numberSpecialties << '\n';
            cout << "�������� ������������: " << human[j].nameUniversity << '\n';
            cout << "����� ������������: " << human[j].adress << '\n';
            cout << "��������� ������: " << human[j].payment << '\n';
            cout << "������� �������� ����: " << human[j].contestScoreBit << "\n\n";
            flag = true;
        }
    }
    if (!flag)
        cout << "������� �� �������!\n\n";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;
    do {
        cout << "�������� ��������:\n1 - ���� � ����������\n2 - ����� �� �����\n3 - ��������\n4 - ����� ���������\n5 - �����\n";
        cin >> choice;
        switch (choice) {
        case 1: {
            InputData(human);
            break;
        }
        case 2: {
            PrintData(human);
            break;
        }
        case 3: {
            Delete(human);
            break;
        }
        case 4: {
            Find(human);
            break;
        }
        case 5: {
            exit(0);
        }
        default:
            cout << "��������� ��������� ������!\n\n";
            break;
        }
    } while (choice != 5);

    return 0;
}