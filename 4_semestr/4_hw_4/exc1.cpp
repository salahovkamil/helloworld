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

void quickSort(vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

void merge(vector<int>& arr, int left, int middle, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + middle + 1);
    vector<int> rightArr(arr.begin() + middle + 1, arr.begin() + right + 1);
    
    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

void measureTime(void (*sortFunc)(vector<int>&), vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    cout << "Time taken: " << elapsed.count() << " ms" << endl;
}

int main() {
    vector<int> sizes = {1000, 5000, 10000};
    
    for (int size : sizes) {
        cout << "Sorting array of size " << size << endl;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 10000);
        
        vector<int> arr(size);
        generate(arr.begin(), arr.end(), [&]() { return dis(gen); });
        
        cout << "Bubble Sort: ";
        measureTime(bubbleSort, arr);
        
        cout << "Quick Sort: ";
        measureTime([](vector<int>& a) { quickSort(a, 0, a.size() - 1); }, arr);
        
        cout << "Merge Sort: ";
        measureTime([](vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, arr);
        
        cout << "Selection Sort: ";
        measureTime(selectionSort, arr);
        
        cout << endl;
    }
    
    return 0;
}
