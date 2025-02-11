#include <iostream>
#include <vector>
#include <string>

template <typename Container>
void Print(const Container& container, const std::string& delimiter) {
    bool first = true;
    for (const auto& element : container) {
        if (!first) {
            std::cout << delimiter;
        }
        std::cout << element;
        first = false;
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> data = {1, 2, 3};
    Print(data, ", ");
    return 0;
}
