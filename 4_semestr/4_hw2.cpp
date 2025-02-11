#include <iostream>
#include <vector>
#include <algorithm>

void SeparateAndSort(const std::vector<int>& input, std::vector<int>& positives, std::vector<int>& negatives) {
    for (int number : input) {
        if (number > 0) {
            positives.push_back(number);
        } else if (number < 0) {
            negatives.push_back(number);
        }
    }

    // Сортировка по возрастанию
    std::sort(positives.begin(), positives.end());
    std::sort(negatives.begin(), negatives.end());
}

int main() {
    std::vector<int> input = {3, -1, 2, -5, 0, 4, -2};
    std::vector<int> positives;
    std::vector<int> negatives;

    SeparateAndSort(input, positives, negatives);

    std::cout << "Положительные элементы:";
    for (int num : positives) {
        std::cout << " " << num;
    }
    std::cout << '\n';

    std::cout << "Отрицательные элементы:";
    for (int num : negatives) {
        std::cout << " " << num;
    }
    std::cout << '\n';

    return 0;
}
