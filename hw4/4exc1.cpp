#include <iostream>
#include <vector>
#include <stdexcept>

struct Vector {
    std::vector<double> elements;

    // Конструктор для создания n-мерного вектора
    Vector(std::initializer_list<double> vals) : elements(vals) {}

    // Функция умножения вектора на число
    Vector operator*(double scalar) const {
        Vector result(*this); // Копируем текущий вектор
        for (auto& elem : result.elements) {
            elem *= scalar; // Умножаем каждый элемент на число
        }
        return result;
    }

    // Функция сложения векторов
    Vector operator+(const Vector& other) const {
        if (elements.size() != other.elements.size()) {
            throw std::invalid_argument("Vectors must be of the same dimension");
        }
        Vector result(*this); // Копируем текущий вектор
        for (size_t i = 0; i < result.elements.size(); ++i) {
            result.elements[i] += other.elements[i]; // Сложение каждого элемента
        }
        return result;
    }

    // Функция скалярного произведения векторов
    double dot(const Vector& other) const {
        if (elements.size() != other.elements.size()) {
            throw std::invalid_argument("Vectors must be of the same dimension");
        }
        double result = 0;
        for (size_t i = 0; i < elements.size(); ++i) {
            result += elements[i] * other.elements[i]; // Скалярное произведение
        }
        return result;
    }
};

int main() {
    Vector v1 = {1.0, 2.0, 3.0};
    Vector v2 = {4.0, 5.0, 6.0};

    Vector v3 = v1 * 2.0; // Умножение на число
    Vector v4 = v1 + v2;  // Сложение векторов
    double dotProduct = v1.dot(v2); // Скалярное произведение

    // Вывод результатов
    std::cout << "[v1 v2] = ";
    for (double elem : v3.elements) std::cout << elem << ' ';
    std::cout << std::endl;

    std::cout << "v1 + v2 = ";
    for (double elem : v4.elements) std::cout << elem << ' ';
    std::cout << std::endl;

    std::cout << "(v1, v2 )= " << dotProduct << std::endl;

    return 0;
}
