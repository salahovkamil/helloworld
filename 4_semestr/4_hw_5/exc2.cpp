#include <iostream>
#include <vector>
#include <thread>
#include <random>

const int ARRAY_SIZE = 10000;
const int NUM_THREADS = 4;

void fillArraySegment(std::vector<int>& arr, int start, int end) {
    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100); // Генерация случайных чисел от 1 до 100

    for (int i = start; i < end; ++i) {
        arr[i] = dis(gen);
    }
}

int main() {
    std::vector<int> arr(ARRAY_SIZE);
    std::vector<std::thread> threads;

    int segment_size = ARRAY_SIZE / NUM_THREADS;

    // Запуск потоков для заполнения массива
    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * segment_size;
        int end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : start + segment_size;
        threads.push_back(std::thread(fillArraySegment, std::ref(arr), start, end));
    }

    // Ожидание завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    // Вывод первых 20 элементов для проверки
    for (int i = 0; i < 20; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
