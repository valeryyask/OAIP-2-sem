#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ������� ��� ������ ������ � ����
void tofile(const string& fileName, const string& str) {
    ofstream fout(fileName);

    if (!fout) {
        cerr << "������ �������� �����." << endl;
        return;
    }

    fout << str;

    fout.close();
}

// ������� ��� ������ ����, ���������� ����� '�', �� �����
void letterX(const string& fileName) {
    ifstream fin(fileName);

    if (!fin) {
        cerr << "������ �������� �����." << endl;
        return;
    }

    string word;
    while (fin >> word) {
        if (word.find('x') != string::npos || word.find('X') != string::npos) {
            cout << word << endl;
        }
    }

    fin.close();
}

int main() {
    string inputFile = "input.txt";
    string inputString;

    cout << "Enter the string: ";
    getline(cin, inputString);

    // ���������� ������ � ����
    tofile(inputFile, inputString);
    cout << "The string is written to the file" << endl;

    // ��������� ����� � ������ "x" �� ����� � ������� ��
    cout << "Words with letter 'x' from file:" << endl;
    letterX(inputFile);

    return 0;
}
