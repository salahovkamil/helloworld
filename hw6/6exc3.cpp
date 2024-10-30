#include <iostream>
#include <vector>
#include <string>

class FullName {
public:
    std::string firstName;
    std::string lastName;

    FullName(std::string first, std::string last) : firstName(first), lastName(last) {}
};

class Animal {
private:
    int health; // Показатель здоровья

public:
    Animal(int health) : health(health) {}

    // Метод для получения текущего здоровья
    int getHealth() const {
        return health;
    }

    // Метод для лечения и улучшения здоровья
    void heal(int amount) {
        health += amount;
        std::cout << "Питомец вылечен на " << amount << ". Текущий уровень здоровья: " << health << std::endl;
    }
};

class Owner {
private:
    FullName fullName;
    int age;
    std::vector<Animal*> pets;

public:
    Owner(FullName name, int age) : fullName(name), age(age) {}

    void addPet(Animal* pet) {
        pets.push_back(pet);
    }

    // Получение количества питомцев
    std::vector<Animal*>& getPets() {
        return pets;
    }

    // Доступ к имени владельца
    std::string getName() const {
        return fullName.firstName + " " + fullName.lastName;
    }

    friend class Veterinarian; // Дружественный класс
};

class Veterinarian {
public:
    void medicalExamination(Owner& owner) {
        std::cout << "Медицинский осмотр питомцев владельца: " << owner.getName() << std::endl;
        for (Animal* pet : owner.getPets()) {
            std::cout << "Питомец с уровнем здоровья: " << pet->getHealth() << std::endl;
        }
    }

    void healPet(Animal& pet, int amount) {
        pet.heal(amount);
    }

    void talkToOwner(Owner& owner) {
        std::cout << "Здравствуйте, " << owner.getName() << "! Как ваши питомцы?" << std::endl;
    }
};

// Пример использования
int main() {
    Owner owner(FullName("Иван", "Иванов"), 30);
    Animal pet1(50);
    Animal pet2(70);

    owner.addPet(&pet1);
    owner.addPet(&pet2);

    Veterinarian vet;
    vet.talkToOwner(owner);
    vet.medicalExamination(owner);
    vet.healPet(pet1, 20);
    
    return 0;
}