#include <iostream>
#include <vector>
#include <list>
#include <utility>

using namespace std;

class HashTable {
private:
    vector<list<pair<int, string>>> table;
    int size;

    int hash(int key) {
        return key % size;
    }

public:
    HashTable(int s) : size(s) {
        table.resize(size);
    }

    void insert(int key, const string& value) {
        int hashIndex = hash(key);
        table[hashIndex].emplace_back(key, value);
    }

    string search(int key) {
        int hashIndex = hash(key);
        for (auto& pair : table[hashIndex]) {
            if (pair.first == key) {
                return pair.second; // Element found
            }
        }
        return "Not Found"; // Element not found
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            for (auto& pair : table[i]) {
                cout << "{" << pair.first << ": " << pair.second << "} ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht(10);

    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(12, "Charlie"); // Collision with key 2
    ht.insert(3, "David");

    ht.display();

    cout << "Searching for key 2: " << ht.search(2) << endl;
    cout << "Searching for key 5: " << ht.search(5) << endl; // Not found

    return 0;
}
