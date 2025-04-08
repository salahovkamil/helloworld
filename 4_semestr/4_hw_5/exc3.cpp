#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>
#include <mutex>

const int ARRAY_SIZE = 10000;
const int NUM_THREADS = 4;

std::mutex mtx; // Мьютекс для синхронизации

// Функция для сортировки сегмента массива
void sortArraySegment(std::vector<int>& arr, int start, int end) {
    std::sort(arr.begin() + start, arr.begin() + end);
}

// Функция для поиска значения в массиве
bool searchValue(const std::vector<int>& arr, int value) {
    return std::find(arr.begin(), arr.end(), value) != arr.end();
}

int main() {
    std::vector<int> arr(ARRAY_SIZE);
    std::vector<std::thread> threads;

    // Заполнение массива случайными числами
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = dis(gen);
    }

    // Сортировка массива с использованием потоков
    int segment_size = ARRAY_SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * segment_size;
        int end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : start + segment_size;
        threads.push_back(std::thread(sortArraySegment, std::ref(arr), start, end));
    }

    // Ожидание завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    // Объединение отсортированных сегментов
    std::vector<int> sorted(arr);
    std::sort(sorted.begin(), sorted.end());

    // Поиск значения
    int valueToFind = 50; // пример значения для поиска
    bool found = searchValue(sorted, valueToFind);

    if (found) {
        std::cout << "Значение " << valueToFind << " найдено в массиве." << std::endl;
    } else {
        std::cout << "Значение " << valueToFind << " не найдено в массиве." << std::endl;
    }

    return 0;
}
