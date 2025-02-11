#include <iostream>
#include <algorithm>

// Функция для поиска элемента в массиве типа int
bool findElement(int arr[], int size, int element) {
    return std::find(arr, arr + size, element) != arr + size;
}

// Функция для поиска элемента в массиве типа float
bool findElement(float arr[], int size, float element) {
    return std::find(arr, arr + size, element) != arr + size;
}

// Функция для поиска элемента в массиве типа char
bool findElement(char arr[], int size, char element) {
    return std::find(arr, arr + size, element) != arr + size;
}

int main() {
    // Пример использования для массива int
    int intArr[] = {1, 2, 3, 4, 5};
    int intElement = 3;
    std::cout << "Элемент " << intElement << (findElement(intArr, 5, intElement) ? " найден." : " не найден.") << std::endl;

    // Пример использования для массива float
    float floatArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float floatElement = 3.3f;
    std::cout << "Элемент " << floatElement << (findElement(floatArr, 5, floatElement) ? " найден." : " не найден.") << std::endl;

    // Пример использования для массива char
    char charArr[] = {'a', 'b', 'c', 'd', 'e'};
    char charElement = 'c';
    std::cout << "Элемент '" << charElement << "'" << (findElement(charArr, 5, charElement) ? " найден." : " не найден.") << std::endl;

    return 0;
}
