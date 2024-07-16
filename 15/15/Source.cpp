#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // ��� ����������
#include <chrono>    // ��� ��������� �������

using namespace std;
using namespace std::chrono;

// ������� ��� ��������� ���������� ������� ��������� �������
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // ���������� ��������� ����� �� 0 �� 999
    }
    return arr;
}

// ������� ��� ����������� ��������� �� A � C
void moveElements(const vector<int>& A, const vector<int>& B, vector<int>& C) {
    int maxElementB = *max_element(B.begin(), B.end());
    for (int elem : A) {
        if (elem < maxElementB) {
            C.push_back(elem);
        }
    }
}

// ����������� ����������
void bubbleSort(vector<int>& arr) {
    bool swapped;
    for (int i = 0; i < arr.size() - 1; ++i) {
        swapped = false;
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] < arr[j + 1]) { // ���������� �� ��������
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// ���������� ����� (������� ����������)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] >= pivot) { // ���������� �� ��������
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ������� ��� �������� ����� ������� �������
int getValidInput() {
    int size;
    char input[100]; // ����� ��� �����

    while (true) {
        cin.getline(input, 100); // ��������� ������ �� �����
        bool validInput = true;
        // ��������� ������ ������ � ������
        for (int i = 0; input[i] != '\0'; ++i) {
            if (!isdigit(input[i])) { // ���� ������ �� �������� ������
                validInput = false; // ���� ��������
                break;
            }
        }
        if (validInput) { // ���� ���� ������, ����������� ������ � �����
            size = atoi(input);
            break;
        }
        else {
            cout << "������: ������� �����." << endl;
            cout << "������� ������ �������: ";
        }
    }

    return size;
}

int main() {
    setlocale(0, "");
    srand(time(nullptr));

    int sizeA, sizeB;
    cout << "������� ������ ������� A: ";
    sizeA = getValidInput();
    vector<int> A = generateRandomArray(sizeA); // ���������� ������ A

    cout << "������� ������ ������� B: ";
    sizeB = getValidInput();
    vector<int> B = generateRandomArray(sizeB); // ���������� ������ B

    // ������� ������� A � B
    cout << "������ A: ";
    for (int num : A) {
        cout << num << " ";
    }
    cout << endl;

    cout << "������ B: ";
    for (int num : B) {
        cout << num << " ";
    }
    cout << endl;

    // ������� ������ C � ��������� �������� �� A
    vector<int> C;
    moveElements(A, B, C);

    // ������� ������ C �� ����������
    cout << "������ C �� ����������: ";
    for (int num : C) {
        cout << num << " ";
    }
    cout << endl;

    // ������� ����� ������� C ��� ����������
    vector<int> C_bubble = C;
    vector<int> C_quick = C;

    auto startBubbleSort = high_resolution_clock::now(); // �������� ����� ������ ����������� ����������
    bubbleSort(C_bubble); // ����������� ����������
    auto stopBubbleSort = high_resolution_clock::now(); // �������� ����� ���������� ����������� ����������

    auto startQuickSort = high_resolution_clock::now(); // �������� ����� ������ ������� ����������
    quickSort(C_quick, 0, C_quick.size() - 1); // ������� ���������� (�����)
    auto stopQuickSort = high_resolution_clock::now(); // �������� ����� ���������� ������� ����������

    // ������� ������ C, ��������������� ����������� �����������
    cout << "��������������� ������ C (����������� ����������): ";
    for (int num : C_bubble) {
        cout << num << " ";
    }
    cout << endl;

    // ������� ������ C, ��������������� ������� �����������
    cout << "��������������� ������ C (���������� �����): ";
    for (int num : C_quick) {
        cout << num << " ";
    }
    cout << endl;

    auto durationBubbleSort = duration_cast<milliseconds>(stopBubbleSort - startBubbleSort); // ��������� ����� ���������� ����������� ����������
    auto durationQuickSort = duration_cast<milliseconds>(stopQuickSort - startQuickSort); // ��������� ����� ���������� ������� ����������

    cout << "����� ���������� ����������� ���������� ��� ������� �������� " << C.size() << ": " << durationBubbleSort.count() << " �����������." << endl;
    cout << "����� ���������� ������� ���������� ��� ������� �������� " << C.size() << ": " << durationQuickSort.count() << " �����������." << endl;

    return 0;
}
