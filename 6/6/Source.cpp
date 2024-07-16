#include <iostream>
#include <fstream>
#include <stdexcept>
#include <regex>

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct LinkedList {
    Node* head;

    LinkedList() : head(nullptr) {}

    void addNode(int data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        cout << "Element added successfully!" << endl;
    }

    void deleteNode(int data) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Element deleted successfully!" << endl;
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data != data) {
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "Element not found!" << endl;
            return;
        }

        Node* temp = current->next;

        current->next = temp->next;
        delete temp;
        cout << "Element deleted successfully!" << endl;
    }

    void searchNode(int data) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr && current->data != data) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Element not found!" << endl;
        }
        else {
            cout << "Element found!" << endl;
        }
    }

    void displayList() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void saveToFile(string filename) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        try {
            ofstream file(filename);
            if (!file.is_open()) {
                throw runtime_error("Unable to open file!");
            }

            Node* current = head;
            while (current != nullptr) {
                file << current->data << " ";
                current = current->next;
            }
            file.close();
            cout << "List saved to file!" << endl;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    int getIntInput() {
        int input;
        string userInput;

        while (true) {
            cout << "Enter an integer: ";
            cin >> userInput;

            // Check each character in the string to see if it is a digit
            bool isDigit = true;
            for (char c : userInput) {
                if (!isdigit(c)) {
                    isDigit = false;
                    break;
                }
            }

            if (isDigit) {
                input = stoi(userInput);
                break;
            }
            else {
                cout << "Invalid input! Please enter an integer." << endl;
            }
        }

        return input;
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Unable to open file!" << endl;
            return;
        }

        int data;
        while (file >> data) {
            addNode(data);
        }
        file.close();
        cout << "List loaded from file!" << endl;
    }

    void sumOfElements() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        int sum = 0;
        Node* current = head;
        while (current != nullptr) {
            int lastDigit = abs(current->data) % 10;
            if (current->data > 0 && lastDigit == 7) {
                sum += current->data;
            }
            current = current->next;
        }

        if (sum == 0) {
            cout << "No positive elements found with last digit 7!" << endl;
        }
        else {
            cout << "Sum of positive elements with last digit 7: " << sum << endl;
        }
    }

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
};

int getIntInput() {
    int input;
    string userInput;

    while (true) {
        cout << "Enter an integer: ";
        cin >> userInput;

        bool isNegative = false;
        if (userInput.size() > 0 && userInput[0] == '-') {
            isNegative = true;
            userInput = userInput.substr(1);
        }

        bool isDigit = true;
        for (char c : userInput) {
            if (!isdigit(c)) {
                isDigit = false;
                break;
            }
        }

        if (isDigit) {
            input = stoi(userInput) * (isNegative ? -1 : 1);
            break;
        }
        else {
            cout << "Invalid input! Please enter an integer." << endl;
        }
    }

    return input;
}
int main() {
    LinkedList list;
    int choice, data;
    string filename;

    do {
        cout << endl;
        cout << "1. Add element (only int)" << endl;
        cout << "2. Delete element" << endl;
        cout << "3. Search element" << endl;
        cout << "4. Display list" << endl;
        cout << "5. Save list to file" << endl;
        cout << "6. Load list from file" << endl;
        cout << "7. Sum of + elements with last digit 7" << endl;
        cout << "8. Exit" << endl;

        // Получаем выбор пользователя, ограничивая его только цифрами от 1 до 8
        choice = getIntInput();
        if (choice < 1 || choice > 8) {
            cout << "Invalid choice! Please choose a number from 1 to 8." << endl;
            continue; // Пропускаем остаток цикла и переходим к следующей итерации
        }

        switch (choice) {
        case 1:
            data = getIntInput();
            list.addNode(data);
            break;
        case 2:
            data = getIntInput();
            list.deleteNode(data);
            break;
        case 3:
            data = getIntInput();
            list.searchNode(data);
            break;
        case 4:
            list.displayList();
            break;
        case 5:
            cout << "Enter file name: ";
            cin >> filename;
            list.saveToFile(filename);
            break;
        case 6:
            cout << "Enter file name: ";
            cin >> filename;
            list.loadFromFile(filename);
            break;
        case 7:
            list.sumOfElements();
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        }
    } while (choice != 8);

    return 0;
}

