#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ���������, �������������� �������������
struct Teacher {
    string surname;   // ������� �������������
    string examName;  // �������� ��������
    string examDate;  // ���� ��������
};

// ������� ��� ����� ���������� � ������������� � ����������
void inputTeacherInfo(Teacher& teacher) {
    cout << "������� ������� �������������: ";
    cin >> teacher.surname;
    cout << "������� �������� ��������: ";
    cin >> teacher.examName;
    cout << "������� ���� ��������: ";
    cin >> teacher.examDate;
}

// ������� ��� ������ ���������� � �������������
void printTeacherInfo(const Teacher& teacher) {
    cout << "������� �������������: " << teacher.surname << endl;
    cout << "�������� ��������: " << teacher.examName << endl;
    cout << "���� ��������: " << teacher.examDate << endl;
}

// ������� ��� �������� ��������� ������������� �� �������
void deleteTeacher(Teacher teachers[], int& numTeachers, const string& surname) {
    for (int i = 0; i < numTeachers; ++i) {
        if (teachers[i].surname == surname) {
            for (int j = i; j < numTeachers - 1; ++j) {
                teachers[j] = teachers[j + 1];
            }
            numTeachers--;
            cout << "������������� " << surname << " ������." << endl;
            return;
        }
    }
    cout << "������������� � �������� " << surname << " �� ������." << endl;
}

// ������� ��� ������ ������������� �� �������
void findTeacher(const Teacher teachers[], int numTeachers, const string& surname) {
    for (int i = 0; i < numTeachers; ++i) {
        if (teachers[i].surname == surname) {
            cout << "���������� � �������������:" << endl;
            printTeacherInfo(teachers[i]);
            return;
        }
    }
    cout << "������������� � �������� " << surname << " �� ������." << endl;
}

// ������� ��� ������ ���������� � �������������� � ����
void writeToFile(const Teacher teachers[], int numTeachers, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < numTeachers; ++i) {
            file << teachers[i].surname << " "
                << teachers[i].examName << " "
                << teachers[i].examDate << endl;
        }
        cout << "������ �������� � ����." << endl;
        file.close();
    }
    else {
        cout << "������ �������� ����� ��� ������." << endl;
    }
}

// ������� ��� ������ ���������� � �������������� �� �����
void readFromFile(Teacher teachers[], int& numTeachers, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        numTeachers = 0;
        while (!file.eof()) {
            file >> teachers[numTeachers].surname
                >> teachers[numTeachers].examName
                >> teachers[numTeachers].examDate;
            numTeachers++;
        }
        numTeachers--;  // ����������� ������� ���������� numTeachers �� 1
        cout << "������ ��������� �� �����." << endl;
        file.close();
    }
    else {
        cout << "������ �������� ����� ��� ������." << endl;
    }
}

// ������� �������
int main() {
    setlocale(LC_ALL, "Russian");
    string surnameToFind;
    string surnameToDelete;
    const int MAX_TEACHERS = 100;
    Teacher teachers[MAX_TEACHERS];
    int numTeachers = 0;

    int choice;
    string filename;

    do {
        cout << "\n����:" << endl;
        cout << "1. ���� ���������� � ������������� � ����������" << endl;
        cout << "2. ����� ���������� � ��������������" << endl;
        cout << "3. �������� ������������� �� �������" << endl;
        cout << "4. ����� ���������� � �������������" << endl;
        cout << "5. ������ ���������� � �������������� � ����" << endl;
        cout << "6. ������ ���������� � �������������� �� �����" << endl;
        cout << "0. �����" << endl;
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (numTeachers < MAX_TEACHERS) {
                inputTeacherInfo(teachers[numTeachers]);
                numTeachers++;
            }
            else {
                cout << "���������� ������������ ���������� ��������������." << endl;
            }
            break;
        case 2:
            cout << "���������� � ��������������:" << endl;
            for (int i = 0; i < numTeachers; ++i) {
                cout << "������������� " << i + 1 << ":" << endl;
                printTeacherInfo(teachers[i]);
            }
            break;
        case 3:
            cout << "������� ������� ������������� ��� ��������: ";
            cin >> surnameToDelete;
            deleteTeacher(teachers, numTeachers, surnameToDelete);
            break;
        case 4:
            cout << "������� ������� ������������� ��� ������: ";
            cin >> surnameToFind;
            findTeacher(teachers, numTeachers, surnameToFind);
            break;
        case 5:
            cout << "������� ��� ����� ��� ������: ";
            cin >> filename;
            writeToFile(teachers, numTeachers, filename);
            break;
        case 6:
            cout << "������� ��� ����� ��� ������: ";
            cin >> filename;
            readFromFile(teachers, numTeachers, filename);
            break;
        case 0:
            cout << "����� �� ���������." << endl;
            break;
        default:
            cout << "������������ �����. ���������� �����." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
