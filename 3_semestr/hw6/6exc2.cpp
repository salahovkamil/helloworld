#include <iostream>
#include <string>
#include <vector>

struct FullName {
    std::string firstName;
    std::string lastName;
    std::string patronymic;

    void display() const {
        std::cout << lastName << " " << firstName << " " << patronymic;
    }
};

class Animal {
public:
    virtual void makeSound() = 0; // Чистая виртуальная функция
    virtual ~Animal() {}
};

class Cat : public Animal {
private:
    std::string breed;
    std::string name;
    int age;

public:
    Cat(std::string br, std::string nm, int ag) : breed(br), name(nm), age(ag) {}

    void makeSound() override {
        std::cout << "Мяу!" << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "Кот:" << std::endl;
        std::cout << "Имя: " << name << ", Порода: " << breed << ", Возраст: " << age << " лет" << std::endl;
    }
};

class Dog : public Animal {
private:
    std::string breed;
    std::string name;
    int age;

public:
    Dog(std::string br, std::string nm, int ag) : breed(br), name(nm), age(ag) {}

    void makeSound() override {
        std::cout << "Гав!" << std::endl;
    }

    void displayInfo() const {
        std::cout << "Собака:" << std::endl;
        std::cout << "Имя: " << name << ", Порода: " << breed << ", Возраст: " << age << " лет" << std::endl;
    }
};

class Owner {
private:
    FullName fullName;
    int age;
    std::vector<Animal*> pets;

public:
    Owner(FullName fn, int ag) : fullName(fn), age(ag) {}

    void addPet(Animal* pet) {
        pets.push_back(pet);
    }

    void displayInfo() const {
        std::cout << "Хозяин:" << std::endl;
        std::cout << "ФИО: ";
        fullName.display();
        std::cout << ", Возраст: " << age << " лет" << std::endl;

        std::cout << "Питомцы:" << std::endl;
        for (const auto& pet : pets) {
            pet->makeSound(); // Выводит звук питомца
        }
    }

    ~Owner() {
        for (auto& pet : pets) {
            delete pet; // Освобождение памяти
        }
    }
};

int main() {
    FullName ownerName = {"Иван", "Иванов", "Иванович"};
    Owner owner(ownerName, 30);

    // Добавляем питомцев
    owner.addPet(new Cat("Сиамская", "Мурка", 6));
    owner.addPet(new Dog("Лабрадор", "Бобик", 5));

    // Выводим информацию о хозяине и питомцах
    owner.displayInfo();

    return 0;
}
