#include <iostream>

int main() {
    int n;

    std::cout << "Введите число n: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cout << "привет мир" << std::endl;
    }

    return 0;
}