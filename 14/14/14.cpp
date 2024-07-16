#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // ��� ������� ������������
#include <ctime>   // ��� ��������� ���������� ����� seed
#include <sstream> // ��� �������������� ������ � �����

using namespace std;

class HashTable {
public:
    struct Node {
        string email;
        string surname;
        int year;

        Node(const string& e, const string& s, int y) : email(e), surname(s), year(y) {}
    };

private:
    size_t m_length;
    vector<vector<Node*>> m_data;

    // ���-������� ��� ����� (���� ��������)
    int hash(int key) {
        return key % m_length;
    }

public:
    HashTable(size_t length) : m_length(length) {
        m_data.resize(length);
    }

    // ���������� ��������
    void add(const string& email, const string& surname, int year) {
        int hash_val = hash(year); // �������� ��� ��������
        m_data[hash_val].push_back(new Node(email, surname, year));
    }

    // �������� �������� �� ���� ��������
    void remove(int year) {
        int hash_val = hash(year);
        vector<Node*>& bucket = m_data[hash_val];
        for (size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i]->year == year) {
                delete bucket[i];
                bucket.erase(bucket.begin() + i);
                return;
            }
        }
        cout << "������� �� ������." << endl;
    }

    // ����� �������� �� ���� ��������
    Node* search(int year) {
        int hash_val = hash(year);
        vector<Node*>& bucket = m_data[hash_val];
        for (Node* node : bucket) {
            if (node->year == year) {
                return node;
            }
        }
        return nullptr;
    }

    // ����� �������
    void print() {
        for (size_t i = 0; i < m_length; ++i) {
            cout << "Bucket " << i << ": ";
            for (Node* node : m_data[i]) {
                cout << "(" << node->email << ", " << node->surname << ", " << node->year << ") ";
            }
            cout << endl;
        }
    }
};
// ������� ��� �������� ������������ ����� ����
int getValidYearInput() {
    string inputStr;
    int input;
    while (true) {
        getline(cin, inputStr); // ��������� ���� � ������
        stringstream ss(inputStr);
        if (ss >> input && ss.eof()) { // �������� ������������� ������ � ����� � ���������, ��� ����� ����������
            if (input >= 1000 && input <= 2024) { // ���������, ��� ��� ������� �� ������� ����
                break;
            }
            else {
                cout << "������: ��� ������ �������� �� ������� ���� ������ 2024." << endl;
            }
        }
        cout << "" << endl;
    }
    return input;
}

// ������� ��� �������� ������������ ����� �����
int getValidInput() {
    string inputStr;
    int input;
    while (true) {
        getline(cin, inputStr); // ��������� ���� � ������
        stringstream ss(inputStr);
        if (ss >> input && ss.eof()) { // �������� ������������� ������ � ����� � ���������, ��� ����� ����������
            break;
        }
        cout << "������: ������� �����." << endl;
    }
    return input;
}

// ������� ��� ��������, ��� ������ ������� �� ������ ����� ��� ��������, �� ����� ��������� �����

bool isValidSurname(const string& str) {
    if (str.empty()) {
        return false; // ���� ������ ������, ���������� false
    }

    bool hasSpace = false;
    for (char c : str) {
        if (isspace(c)) {
            hasSpace = true; // ���� ���� ���� ������ �������� ��������, ������������� ����
        }
        if (c == '-') {
            continue; // ���� ������ - �����, ��������� � ���������� �������
        }
        if (!isalpha(c)) {
            return false; // ���� ������ �� �������� ������ ��� �������, ���������� false
        }
    }
    return !hasSpace; // ���������� true, ���� � ������ ��� ��������
}



int main() {
    setlocale(0, "");
    srand(time(nullptr)); // ������������� seed ��� ��������� ��������� �����

    size_t table_size;
    cout << "������� ������ ���-�������: ";
    table_size = getValidInput(); // ���������� ������� ��� �������� �����

    HashTable table(table_size);

    int choice;
    while (true) {
        cout << "\n�������� ��������:\n";
        cout << "1. �������� �������\n";
        cout << "2. ������� �������\n";
        cout << "3. ����� �������\n";
        cout << "4. ������� �������\n";
        cout << "5. �����\n";
        cout << "�����: ";
        choice = getValidInput(); // ���������� ������� ��� �������� �����

        switch (choice) {
            // ��������� ����� ���� �������� ����������

        case 1: {
            string email, surname;
            cout << "������� �����: ";
            getline(cin, email); // ��������� ������ ������
            do {
                cout << "������� ������� ��������: ";
                getline(cin, surname); // ��������� ������ �������
                if (!isValidSurname(surname)) {
                    cout << "������: ������� ������ �������� �� ������ ����� ��� ��������, �� ����� ��������� �����. ����������, ������� �� ��� ���." << endl;
                }
            } while (!isValidSurname(surname)); // ��������� ����, ���� ������� �� ������������� �����������
            int year;
            cout << "������� ��� ��������: ";
            year = getValidYearInput(); // ���������� ������� ��� �������� ����� ����
            table.add(email, surname, year);
            break;
        }

        case 2: {
            cout << "������� ��� �������� �������� ��� ��������: ";
            int year = getValidYearInput(); // ���������� ������� ��� �������� ����� ����
            table.remove(year);
            break;
        }
        case 3: {
            cout << "������� ��� �������� �������� ��� ������: ";
            int year = getValidYearInput(); // ���������� ������� ��� �������� ����� ����
            HashTable::Node* result = table.search(year);
            if (result) {
                cout << "������: " << result->surname << ", " << result->email << ", " << result->year << endl;
            }
            else {
                cout << "������� �� ������." << endl;
            }
            break;
        }

        case 4:
            cout << "���-�������:" << endl;
            table.print();
            break;
        case 5:
            return 0;
        default:
            cout << "�������� �����. ���������� �����." << endl;
            break;
        }
    }

    return 0;
}
