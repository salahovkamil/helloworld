#include <iostream>

int main() {
    int n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;


    int* arr = new int[n];

    for (int i = 0; i < n; ++i) {
        arr[i] = i * i; 
    }


    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }

    std::cout << "Сумма элементов массива: " << sum << std::endl;

    delete[] arr;

    return 0;
}
