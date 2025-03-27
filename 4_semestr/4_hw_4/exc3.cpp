#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void hybridQuickSort(vector<int>& arr, int low, int high) {
    if (high - low < 10) {
        insertionSort(arr, low, high);
    } else {
        if (low < high) {
            int pi = partition(arr, low, high);
            hybridQuickSort(arr, low, pi - 1);
            hybridQuickSort(arr, pi + 1, high);
        }
    }
}

void measureTime(void (*sortFunc)(vector<int>&, int, int), vector<int> arr, const string& label) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
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

        // Стандартная быстрая сортировка
        arrCopy = arr; // Копируем массив
        measureTime(quickSort, arrCopy, "Standard Quick Sort");
        
        // Гибридная быстрая сортировка
        arrCopy = arr; // Копируем массив
        measureTime(hybridQuickSort, arrCopy, "Hybrid Quick Sort");
        
        cout << endl;
    }
    
    return 0;
}
