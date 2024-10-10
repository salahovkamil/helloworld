#include <iostream>
#include <cstdlib> // для std::rand и std::srand
#include <ctime>   // для std::time

// Определите макрос для динамического или статического массива
#define DYNAMIC_MEMORY  // Убедитесь, что этот макрос закомментирован для статического массива
#define SIZE 10        // Размер массива

void fillAndPrintArray(int *arr, int size) {
    // Заполнение массива случайными значениями и вывод на экран
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 100; // Заполнение случайными числами от 0 до 99
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Инициализация генератора случайных чисел

#ifdef DYNAMIC_MEMORY
    // Создание динамического массива
    int* dynamicArray = new int[SIZE];
    fillAndPrintArray(dynamicArray, SIZE);
    delete[] dynamicArray; // Не забываем освободить выделенную память
#else
    // Создание статического массива
    int staticArray[SIZE];
    fillAndPrintArray(staticArray, SIZE);
#endif

    return 0;
}