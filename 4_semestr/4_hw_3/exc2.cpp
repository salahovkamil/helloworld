#include <iostream>
#include <vector>
#include <list>
#include <utility>

using namespace std;

class HashTable {
private:
    vector<list<pair<int, string>>> table; // Вектор списков для хранения пар (ключ, значение)
    int size; // Размер таблицы

    int hash(int key) {
        return key % size; // Хэш-функция
    }

public:
    HashTable(int s) : size(s) {
        table.resize(size); // Инициализация вектора списков
    }

    void insert(int key, const string& value) {
        int hashIndex = hash(key); // Вычисление индекса
        table[hashIndex].emplace_back(key, value); // Добавление пары (ключ, значение)
    }

    string search(int key) {
        int hashIndex = hash(key); // Вычисление индекса
        for (auto& pair : table[hashIndex]) { // Поиск в списке
            if (pair.first == key) {
                return pair.second; // Элемент найден
            }
        }
        return "Не найден"; // Элемент не найден
    }

    void display() {
        for (int i = 0; i < size; ++i) { // Отображение таблицы
            cout << i << ": ";
            for (auto& pair : table[i]) {
                cout << "{" << pair.first << ": " << pair.second << "} "; // Вывод пары
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht(10); // Создание хэш-таблицы размером 10

    ht.insert(1, "Алиса");
    ht.insert(2, "Боб");
    ht.insert(12, "Чарли"); // Коллизия с ключом 2
    ht.insert(3, "Дэвид");

    ht.display(); // Отображение содержимого хэш-таблицы

    cout << "Поиск ключа 2: " << ht.search(2) << endl; // Поиск ключа 2
    cout << "Поиск ключа 5: " << ht.search(5) << endl; // Не найден

    return 0;
}
