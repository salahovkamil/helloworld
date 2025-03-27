#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void optimizedBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Если не было обменов, массив уже отсортирован
        if (!swapped) {
            break;
        }
    }
}

void measureTime(void (*sortFunc)(vector<int>&), vector<int> arr, const string& label) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    cout << label << " time taken: " << elapsed.count() << " ms" << endl;
}

int main() {
    vector<int> sizes = {1000, 5000, 10000};
    
    for (int size : sizes) {
        cout << "Sorting array of size " << size << endl;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 10000);
        
        // Генерация случайного массива
        vector<int> arr(size);
        generate(arr.begin(), arr.end(), [&]() { return dis(gen); });

        vector<int> arrCopy;

        // Оригинальная сортировка
        arrCopy = arr; // Копируем массив
        measureTime(bubbleSort, arrCopy, "Bubble Sort");
        
        // Оптимизированная сортировка
        arrCopy = arr; // Копируем массив
        measureTime(optimizedBubbleSort, arrCopy, "Optimized Bubble Sort");
        
        cout << endl;
    }
    
    return 0;
}
