#include <iostream>

int main() {
    int sum = 0;
    while (true) {
        int n;
        std::cin >> n;
        if (n == 0) {
            break;
        }
        if (n > 0) {
            sum += n;
            std::cout << sum << std::endl;
            int* array = new int[n];
            delete[] array;
        }  
    }
    return 0;
}
