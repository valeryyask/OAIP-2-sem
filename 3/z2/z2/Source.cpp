#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция для записи строки в файл
void tofile(const string& fileName, const string& str) {
    ofstream fout(fileName);

    if (!fout) {
        cerr << "Ошибка открытия файла." << endl;
        return;
    }

    fout << str;

    fout.close();
}

// Функция для чтения слов, содержащих букву 'х', из файла
void letterX(const string& fileName) {
    ifstream fin(fileName);

    if (!fin) {
        cerr << "Ошибка открытия файла." << endl;
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

    // Записываем строку в файл
    tofile(inputFile, inputString);
    cout << "The string is written to the file" << endl;

    // Считываем слова с буквой "x" из файла и выводим их
    cout << "Words with letter 'x' from file:" << endl;
    letterX(inputFile);

    return 0;
}
