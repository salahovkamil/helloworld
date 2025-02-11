#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

// 1. Структуры
struct Spell {
    string name;
    int damage;
};

// 2. Интерфейс стратегии
class AttackStrategy {
public:
    virtual void attack() = 0; // Чисто виртуальная функция
};

// 3. Конкретные стратегии
class MageAttackStrategy : public AttackStrategy {
public:
    void attack() override {
        cout << "Маг атакует заклинанием!" << endl;
    }
};

class MonsterAttackStrategy : public AttackStrategy {
public:
    void attack() override {
        cout << "Монстр нападает в ближнем бою!" << endl;
    }
};

// 4. Базовый класс персонажа
class Character {
protected:
    string name;
    int health;
    unique_ptr<AttackStrategy> attackStrategy;

public:
    Character(const string &name, int health, unique_ptr<AttackStrategy> strategy)
        : name(name), health(health), attackStrategy(move(strategy)) {}

    virtual void attack() {
        attackStrategy->attack();
    }

    int getHealth() const {
        return health;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    string getName() const {
        return name;
    }
};

// 5. Класс для создания персонажей
class CharacterFactory {
public:
    static unique_ptr<Character> createMage(const string &name) {
        return make_unique<Character>(name, 100, make_unique<MageAttackStrategy>());
    }

    static unique_ptr<Character> createMonster(const string &name) {
        return make_unique<Character>(name, 150, make_unique<MonsterAttackStrategy>());
    }
};

// 6. Шаблонный класс для списка персонажей
template <typename T>
class CharacterList {
private:
    vector<unique_ptr<T>> characters;

public:
    void addCharacter(unique_ptr<T> character) {
        characters.push_back(move(character));
    }

    T* getCharacter(int index) const {
        if (index < 0 || index >= characters.size()) {
            throw out_of_range("Индекс вне диапазона");
        }
        return characters[index].get();
    }

    size_t size() const {
        return characters.size();
    }

    void clear() {
        characters.clear();
    }
};

// 7. Класс для проведения битвы
class Battle {
public:
    void fight(Character* char1, Character* char2) {
        while (char1->getHealth() > 0 && char2->getHealth() > 0) {
            char1->attack();
            char2->takeDamage(10); // Предположим фиксированный урон
            if (char2->getHealth() <= 0) break;

            char2->attack();
            char1->takeDamage(10);
        }

        if (char1->getHealth() > 0) {
            cout << char1->getName() << " выиграл!" << endl;
        } else {
            cout << char2->getName() << " выиграл!" << endl;
        }
    }
};

// 8. Считывание из файла
CharacterList<Character> loadCharactersFromFile(const string &filename) {
    CharacterList<Character> characters;
    ifstream file(filename);
    
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        string type;
        ss >> name >> type;

        if (type == "Mage") {
            characters.addCharacter(CharacterFactory::createMage(name));
        } else if (type == "Monster") {
            characters.addCharacter(CharacterFactory::createMonster(name));
        }
    }

    return characters;
}

// 9. Функция для обработки ошибок
void handleError(const runtime_error &e) {
    cerr << "Ошибка: " << e.what() << endl;
}

int main() {
    try {
        CharacterList<Character> characters = loadCharactersFromFile("characters.txt");
        
        if (characters.size() < 2) {
            throw runtime_error("Недостаточно персонажей для битвы.");
        }

        Battle battle;
        battle.fight(characters.getCharacter(0), characters.getCharacter(1));
    } catch (const runtime_error &e) {
        handleError(e);
    }

    return 0;
}
