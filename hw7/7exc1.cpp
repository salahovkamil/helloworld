#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <stdexcept>

// Абстрактный класс Заклинание
class Spell {
public:
    virtual std::string getName() const = 0;
    virtual ~Spell() = default;
};

// Конкретные классы заклинаний
class AttackSpell : public Spell {
public:
    std::string getName() const override {
        return "Атакующее заклинание";
    }
};

class DefenseSpell : public Spell {
public:
    std::string getName() const override {
        return "Защитное заклинание";
    }
};

class UtilitySpell : public Spell {
public:
    std::string getName() const override {
        return "Бытовое заклинание";
    }
};

class UnforgivableSpell : public Spell {
public:
    std::string getName() const override {
        return "Непростительное заклинание";
    }
};

// Класс для книги заклинаний
class SpellBook {
private:
    std::unordered_set<std::string> spellNames;
    std::vector<std::unique_ptr<Spell>> spells;

public:
    void addSpell(std::unique_ptr<Spell> spell) {
        if (spellNames.find(spell->getName()) != spellNames.end()) {
            throw std::runtime_error("Заклинание уже существует в книге!");
        }
        spellNames.insert(spell->getName());
        spells.push_back(std::move(spell));
    }

    void showSpells() const {
        std::cout << "Заклинания в книге:\n";
        for (const auto& spell : spells) {
            std::cout << "- " << spell->getName() << "\n";
        }
    }
};

// Главная функция
int main() {
    SpellBook mySpellBook;
    
    try {
        mySpellBook.addSpell(std::make_unique<AttackSpell>());
        mySpellBook.addSpell(std::make_unique<DefenseSpell>());
        mySpellBook.addSpell(std::make_unique<UtilitySpell>());
        mySpellBook.addSpell(std::make_unique<UnforgivableSpell>());
        
        // Попытка добавить повторяющееся заклинание
        mySpellBook.addSpell(std::make_unique<AttackSpell>());
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    mySpellBook.showSpells();
    
    return 0;
}
