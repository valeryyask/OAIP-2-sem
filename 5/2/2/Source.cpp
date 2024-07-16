#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// ������������ ��� ��������������
enum Specialties {
    INFORMATICS,
    ELECTRICAL_ENGINEERING,
    MECHANICS,
    CHEMISTRY,
    CONSTRUCTION
};

// ��������� ��� �������� ���������� � ����
struct University {
    string name;
    string address;
    union {
        unsigned int competitionScores[5]; // ������ ��� ������ �� ������� �� ������ �������������
        struct {
            unsigned int informatics;
            unsigned int electricalEngineering;
            unsigned int mechanics;
            unsigned int chemistry;
            unsigned int construction;
        } competitionScoresIndividual;
    };
    float tuitionFee; // ������ ������ ��� ���������� ��������
};

const int MAX_UNIVERSITIES = 100;
int numUniversities = 0;
University universities[MAX_UNIVERSITIES];

// ������� ��� ������ ������ � ����
void writeDataToFile() {
    ofstream file("universities.txt");
    if (file.is_open()) {
        file << numUniversities << endl;
        for (int i = 0; i < numUniversities; ++i) {
            file << universities[i].name << endl;
            file << universities[i].address << endl;
            for (int j = 0; j < 5; ++j) {
                file << universities[i].competitionScores[j] << " ";
            }
            file << endl;
            file << universities[i].tuitionFee << endl;
        }
        file.close();
    }
    else {
        cout << "������ �������� ����� ��� ������ ������!" << endl;
    }
}

// ������� ��� ������ ������ �� �����
void readDataFromFile() {
    ifstream file("universities.txt");
    if (file.is_open()) {
        file >> numUniversities;
        file.ignore(); // ���������� ������ ����� ������ ����� ������ ����� �����
        for (int i = 0; i < numUniversities; ++i) {
            getline(file, universities[i].name);
            getline(file, universities[i].address);
            for (int j = 0; j < 5; ++j) {
                file >> universities[i].competitionScores[j];
            }
            file >> universities[i].tuitionFee;
            file.ignore(); // ���������� ������ ����� ������ ����� ������ ������ ��������
        }
        file.close();
    }
    else {
        cout << "������ �������� ����� ��� ������ ������!" << endl;
    }
}

// ������� ��� �������� �������� ����
bool isValidUniversityName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false; // �������� �������� ������������ �������
        }
    }
    return true;
}

// ������� ��� �������� ���������� ��������������
bool isValidSpecialtiesCount(int count) {
    return count >= 0 && count <= 5; // ���������� �������������� �� ��������� 5 � �� �������������
}

// ������� ��� �������� ������ �� �������
bool isValidCompetitionScore(int score) {
    return score >= 0 && score <= 400; // ����� �� ��������� 400 � �� �������������
}

// ������� ��� ���������� ����
void addUniversity() {
    if (numUniversities < MAX_UNIVERSITIES) {
        University u;

        cout << "������� �������� ����: ";
        getline(cin, u.name);
        if (!isValidUniversityName(u.name)) {
            cout << "�������� ���� �������� ������������ �������!" << endl;
            return;
        }

        cout << "������� ����� ����: ";
        getline(cin, u.address);

        // ���� ������ �� ������� �� ������ �������������
        cout << "������� ����� �� ������� �� ��������������:" << endl;
        for (int i = 0; i < 5; ++i) {
            int score;
            cout << "������� ����� �� ������� �� ������������� " << i + 1 << ": ";
            cin >> score;
            if (!isValidCompetitionScore(score)) {
                cout << "������������ �����!" << endl;
                return;
            }
            u.competitionScores[i] = score; // ��������� �����
        }

        cout << "������� ������ ������ ��� ���������� ��������: ";
        cin >> u.tuitionFee;

        universities[numUniversities++] = u;

        writeDataToFile(); // ���������� ������ � ����
    }
    else {
        cout << "���������� ������������ ���������� �����!" << endl;
    }
}

// ������� ��� ������ ���������� � ����
void displayUniversity(const University& u) {
    cout << "��������: " << u.name << endl;
    cout << "�����: " << u.address << endl;
    cout << "����� �� ������� �� ��������������:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "������������� " << i + 1 << ": " << u.competitionScores[i] << endl;
    }
    cout << "������ ������ ��� ���������� ��������: " << u.tuitionFee << endl;
}

// ������� ��� ������ ������ �����
void displayUniversities() {
    for (int i = 0; i < numUniversities; ++i) {
        cout << "��� " << i + 1 << ":" << endl;
        displayUniversity(universities[i]);
    }
}

// ������� ��� �������� ����
void deleteUniversity() {
    cout << "������� �������� ���� ��� ��������: ";
    string name;
    getline(cin, name);
    for (int i = 0; i < numUniversities; ++i) {
        if (universities[i].name == name) {
            for (int j = i; j < numUniversities - 1; ++j) {
                universities[j] = universities[j + 1];
            }
            --numUniversities;
            cout << "��� ������� ������!" << endl;
            writeDataToFile(); // ����� �������� ���������� ��������� � ����
            return;
        }
    }
    cout << "��� �� ������!" << endl;
}

// ������� ��� ������ ���� � ����������� ���������
void searchUniversityByMinimumCompetition() {
    int specialty;
    cout << "������� ����� ������������� ��� ������ ���� � ����������� ���������: ";
    cin >> specialty;

    int minCompetition = 401; // ������������� ��������� ���� ������������� ����� (400)
    University* minCompetitionUniversity = nullptr;

    for (int i = 0; i < numUniversities; ++i) {
        if (universities[i].competitionScores[specialty - 1] < minCompetition) {
            minCompetition = universities[i].competitionScores[specialty - 1];
            minCompetitionUniversity = &universities[i];
        }
    }

    if (minCompetitionUniversity != nullptr) {
        cout << "��� � ����������� ��������� �� ������������� " << specialty << ":" << endl;
        displayUniversity(*minCompetitionUniversity);
    }
    else {
        cout << "���� �� �������!" << endl;
    }
}

// ������� ��� ������ ����
void displayMenu() {
    cout << "����:" << endl;
    cout << "1. �������� ���" << endl;
    cout << "2. ������� ������ �����" << endl;
    cout << "3. ������� ���" << endl;
    cout << "4. ����� ��� � ����������� ���������" << endl;
    cout << "5. ��������� ������ �� �����" << endl;
    cout << "6. �����" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int choice;
    do {
        displayMenu();
        cout << "������� ��� �����: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addUniversity();
            break;
        case 2:
            displayUniversities();
            break;
        case 3:
            deleteUniversity();
            break;
        case 4:
            searchUniversityByMinimumCompetition();
            break;
        case 5:
            readDataFromFile(); // ������ ������ �� �����
            cout << "������ ������� ��������� �� �����." << endl;
            break;
        case 6:
            cout << "�� ��������!" << endl;
            break;
        default:
            cout << "������������ �����! ���������� ��� ���." << endl;
            break;
        }

    } while (choice != 6);

    return 0;
}