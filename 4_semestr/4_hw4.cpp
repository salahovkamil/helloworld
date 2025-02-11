#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

bool isValid(const std::string& s) {
    std::stack<char> st;
    std::unordered_map<char, char> brackets = {{')', '('}, {']', '['}, {'}', '{'}};

    for (char ch : s) {
        // Если открывающая скобка, добавляем её в стек
        if (brackets.count(ch) == 0) {
            st.push(ch);
        } 
        // Если закрывающая скобка, проверяем стек
        else {
            if (st.empty() || st.top() != brackets[ch]) {
                return false; // Неправильная последовательность
            }
            st.pop(); // Убираем соответствующую открывающую скобку
        }
    }
    return st.empty(); // Если стек пуст, последовательность правильная
}

int main() {
    std::string input;
    std::cout << "Введите скобочную последовательность: ";
    std::getline(std::cin, input);
    
    if (isValid(input)) {
        std::cout << "Скобочная последовательность правильная." << std::endl;
    } else {
        std::cout << "Скобочная последовательность неправильная." << std::endl;
    }

    return 0;
}
