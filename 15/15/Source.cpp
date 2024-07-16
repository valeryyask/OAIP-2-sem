#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Для сортировки
#include <chrono>    // Для измерения времени

using namespace std;
using namespace std::chrono;

// Функция для генерации случайного массива заданного размера
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // Генерируем случайное число от 0 до 999
    }
    return arr;
}

// Функция для перемещения элементов из A в C
void moveElements(const vector<int>& A, const vector<int>& B, vector<int>& C) {
    int maxElementB = *max_element(B.begin(), B.end());
    for (int elem : A) {
        if (elem < maxElementB) {
            C.push_back(elem);
        }
    }
}

// Пузырьковая сортировка
void bubbleSort(vector<int>& arr) {
    bool swapped;
    for (int i = 0; i < arr.size() - 1; ++i) {
        swapped = false;
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] < arr[j + 1]) { // Сортировка по убыванию
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Сортировка Хоара (быстрая сортировка)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] >= pivot) { // Сортировка по убыванию
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

// Функция для проверки ввода размера массива
int getValidInput() {
    int size;
    char input[100]; // Буфер для ввода

    while (true) {
        cin.getline(input, 100); // Считываем строку из ввода
        bool validInput = true;
        // Проверяем каждый символ в строке
        for (int i = 0; input[i] != '\0'; ++i) {
            if (!isdigit(input[i])) { // Если символ не является цифрой
                validInput = false; // Ввод неверный
                break;
            }
        }
        if (validInput) { // Если ввод верный, преобразуем строку в число
            size = atoi(input);
            break;
        }
        else {
            cout << "Ошибка: введите число." << endl;
            cout << "Введите размер массива: ";
        }
    }

    return size;
}

int main() {
    setlocale(0, "");
    srand(time(nullptr));

    int sizeA, sizeB;
    cout << "Введите размер массива A: ";
    sizeA = getValidInput();
    vector<int> A = generateRandomArray(sizeA); // Генерируем массив A

    cout << "Введите размер массива B: ";
    sizeB = getValidInput();
    vector<int> B = generateRandomArray(sizeB); // Генерируем массив B

    // Выводим массивы A и B
    cout << "Массив A: ";
    for (int num : A) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Массив B: ";
    for (int num : B) {
        cout << num << " ";
    }
    cout << endl;

    // Создаем массив C и переносим элементы из A
    vector<int> C;
    moveElements(A, B, C);

    // Выводим массив C до сортировки
    cout << "Массив C до сортировки: ";
    for (int num : C) {
        cout << num << " ";
    }
    cout << endl;

    // Создаем копии массива C для сортировок
    vector<int> C_bubble = C;
    vector<int> C_quick = C;

    auto startBubbleSort = high_resolution_clock::now(); // Замеряем время начала пузырьковой сортировки
    bubbleSort(C_bubble); // Пузырьковая сортировка
    auto stopBubbleSort = high_resolution_clock::now(); // Замеряем время завершения пузырьковой сортировки

    auto startQuickSort = high_resolution_clock::now(); // Замеряем время начала быстрой сортировки
    quickSort(C_quick, 0, C_quick.size() - 1); // Быстрая сортировка (Хоара)
    auto stopQuickSort = high_resolution_clock::now(); // Замеряем время завершения быстрой сортировки

    // Выводим массив C, отсортированный пузырьковой сортировкой
    cout << "Отсортированный массив C (пузырьковая сортировка): ";
    for (int num : C_bubble) {
        cout << num << " ";
    }
    cout << endl;

    // Выводим массив C, отсортированный быстрой сортировкой
    cout << "Отсортированный массив C (сортировка Хоара): ";
    for (int num : C_quick) {
        cout << num << " ";
    }
    cout << endl;

    auto durationBubbleSort = duration_cast<milliseconds>(stopBubbleSort - startBubbleSort); // Вычисляем время выполнения пузырьковой сортировки
    auto durationQuickSort = duration_cast<milliseconds>(stopQuickSort - startQuickSort); // Вычисляем время выполнения быстрой сортировки

    cout << "Время выполнения пузырьковой сортировки для массива размером " << C.size() << ": " << durationBubbleSort.count() << " миллисекунд." << endl;
    cout << "Время выполнения быстрой сортировки для массива размером " << C.size() << ": " << durationQuickSort.count() << " миллисекунд." << endl;

    return 0;
}
