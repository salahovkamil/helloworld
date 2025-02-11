#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <stdexcept>

// Абстрактный класс для заклинаний
class Spell {
public:
    virtual std::string getName() const = 0; // Чисто виртуальная функция для получения имени заклинания
    virtual ~Spell() = default;
};

// Различные классы заклинаний
class AttackSpell : public Spell {
public:
    std::string getName() const override {
        return "Attack Spell";
    }
};

class DefenseSpell : public Spell {
public:
    std::string getName() const override {
        return "Defense Spell";
    }
};

class UtilitySpell : public Spell {
public:
    std::string getName() const override {
        return "Utility Spell";
    }
};

// Шаблонный класс для хранения группы заклинаний
template<typename T>
class SpellGroup {
private:
    std::unordered_set<std::string> spellNames; // Для уникальности названий заклинаний
    std::vector<std::shared_ptr<T>> spells; // Вектор для хранения заклинаний

public:
    void addSpell(const std::shared_ptr<T>& spell) {
        std::string name = spell->getName();
        if (spellNames.find(name) != spellNames.end()) {
            throw std::runtime_error("Spell already exists: " + name);
        }
        spellNames.insert(name);
        spells.push_back(spell);
    }

    void showSpells() const {
        for (const auto& spell : spells) {
            std::cout << spell->getName() << std::endl;
        }
    }
};

// Фабрика для создания заклинаний
class SpellFactory {
public:
    virtual std::shared_ptr<Spell> createSpell() const = 0;
    virtual ~SpellFactory() = default;
};

// Конкретные фабрики для создания заклинаний
class AttackSpellFactory : public SpellFactory {
public:
    std::shared_ptr<Spell> createSpell() const override {
        return std::make_shared<AttackSpell>();
    }
};

class DefenseSpellFactory : public SpellFactory {
public:
    std::shared_ptr<Spell> createSpell() const override {
        return std::make_shared<DefenseSpell>();
    }
};

class UtilitySpellFactory : public SpellFactory {
public:
    std::shared_ptr<Spell> createSpell() const override {
        return std::make_shared<UtilitySpell>();
    }
};

int main() {
    try {
        // Создаем группы заклинаний с использованием шаблона
        SpellGroup<Spell> attackSpells;
        SpellGroup<Spell> defenseSpells;
        SpellGroup<Spell> utilitySpells;

        // Используем фабрики для создания заклинаний и добавляем их в соответствующие группы
        AttackSpellFactory attackFactory;
        DefenseSpellFactory defenseFactory;
        UtilitySpellFactory utilityFactory;

        // Добавление заклинаний в группы
        attackSpells.addSpell(attackFactory.createSpell());
        defenseSpells.addSpell(defenseFactory.createSpell());
        utilitySpells.addSpell(utilityFactory.createSpell());

        // Попробуем добавить дубликат заклинания
        attackSpells.addSpell(attackFactory.createSpell()); // Это вызовет исключение

        // Показать заклинания
        std::cout << "Attack Spells:" << std::endl;
        attackSpells.showSpells();
        
        std::cout << "Defense Spells:" << std::endl;
        defenseSpells.showSpells();
        
        std::cout << "Utility Spells:" << std::endl;
        utilitySpells.showSpells();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}




// Шаблон в C++ — это конструкция, которая позволяет создавать функции и классы, работающие с разными типами данных. 
// В нашем коде шаблон используется в классе SpellGroup
// Здесь SpellGroup — это шаблонный класс, который может принимать любой тип, производный от класса Spell. 
// Это позволяет ему хранить различные типы заклинаний (например, AttackSpell, DefenseSpell, UtilitySpell) в одной группе.

// Абстрактная фабрика — это паттерн проектирования, который позволяет создавать интерфейс для создания семейств взаимосвязанных объектов, 
// не специфицируя конкретные классы. 
// В нашем коде абстрактная фабрика представлена интерфейсом SpellFactory
// Каждая конкретная фабрика (AttackSpellFactory, DefenseSpellFactory, UtilitySpellFactory) реализует метод createSpell, 
// создавая и возвращая конкретный тип заклинания. 
// Это позволяет нам использовать один и тот же интерфейс для создания различных заклинаний, 
// что упрощает добавление новых типов заклинаний в будущем.

// Компоновщик — это паттерн проектирования, 
// который позволяет сгруппировать объекты в древовидные структуры для представления иерархий «часть-целое». 
// В нашем примере компоновщик можно увидеть в классе SpellGroup
// SpellGroup хранит коллекцию заклинаний и предоставляет методы для добавления и отображения заклинаний, 
// что позволяет манипулировать группой заклинаний как единым объектом. 
// Это делает SpellGroup компоновщиком, так как он объединяет несколько объектов (заклинания) в единое целое.