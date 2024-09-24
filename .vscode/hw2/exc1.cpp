#include <iostream>

bool isPrime(int num) {
    if (num <= 1) return false; // 0 и 1 не являются простыми
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false; // Найден делитель
    }
    return true; // Число простое
}

int maxDivisor(int num) {
    for (int i = num / 2; i > 1; --i) {
        if (num % i == 0) return i; // Найден максимальный делитель
    }
    return 1; // Если не найден делитель, возвращаем 1
}

int main() {
    int number;
    std::cout << "Введите целое число: ";
    std::cin >> number;

    if (isPrime(number)) {
        std::cout << number << " - простое число." << std::endl;
    } else {
        int divisor = maxDivisor(number);
        std::cout << number << " - не является простым числом." << std::endl;
        std::cout << "Максимальный делитель: " << divisor << std::endl;
    }

    return 0;
}
