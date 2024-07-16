#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;
void countWords(string sentence);
void func();
int main() {
    ofstream clearfile("FILE2.txt", std::ios::out | std::ios::trunc);
    setlocale(LC_ALL, "Rus");
    ifstream file("FILE1.txt");
    string line;
    while (getline(file, line)) {
        countWords(line);
    }
    func();
    file.close();
    return 0;
}
void countWords(string sentence) {
    int wordCount = 0;
    bool inWord = false;
    for (char c : sentence) {
        if (c == ' ') {
            inWord = false;
        }
        else {
            if (!inWord) {
                inWord = true;
                ++wordCount;
            }
        }
    }

    string* lineWords = new string[wordCount];
    int currentIndex = 0;
    string currentWord;

    for (char c : sentence) {
        if (c == ' ') {
            if (!currentWord.empty()) {
                lineWords[currentIndex++] = currentWord;
                currentWord.clear();
            }
        }
        else {
            currentWord += c;
        }
    }
    if (!currentWord.empty()) {
        lineWords[currentIndex++] = currentWord;
    }

    for (int x = 0; x < wordCount; x++) {
        int counter = 0;
        for (int y = 0; y < wordCount; y++) {
            if (y == x) {
                continue;
            }
            else {
                if (lineWords[x] == lineWords[y]) {
                    counter++;
                }
            }
        }
        if (counter >= 1) {
            ofstream file2("FILE2.txt", ios::app);
            file2 << sentence << endl;

            file2.close();
            break;
        }
    }
    delete[] lineWords;
}

void func() {
    ifstream file2("FILE2.txt");
    string line;
    string word;

    int index = 0;
    int indexA = 0;
    int counterA = 0;
    string foundword;

    while (getline(file2, line)) {
        for (char x : line) {
            if (x == ' ') {
                if (!word.empty()) {
                    index++;
                    int counterBuffer = 0;
                    for (char y : word) {

                        counterBuffer++;

                    }
                    if (counterBuffer > counterA) {
                        foundword = word;
                        counterA = counterBuffer;
                        indexA = index;
                    }

                    word.clear();
                }
            }
            else {
                word += x;
            }
        }
        if (!word.empty()) {
            index++;
            int counterBuffer = 0;
            for (char y : word) {

                counterBuffer++;

            }
            if (counterBuffer > counterA) {
                foundword = word;
                counterA = counterBuffer;
                indexA = index;

            }

        }
        word.clear();
    }


    cout << "Index: " << indexA << endl;
    file2.close();
}