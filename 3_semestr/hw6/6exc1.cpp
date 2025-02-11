#include <iostream>
#include <string>

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

    void displayInfo() {
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

    void displayInfo() {
        std::cout << "Собака:" << std::endl;
        std::cout << "Имя: " << name << ", Порода: " << breed << ", Возраст: " << age << " лет" << std::endl;
    }
};

int main() {
    Cat cat("Сиамская", "Мурка", 6);
    Dog dog("Лабрадор", "Бобик", 5);

    cat.displayInfo();
    cat.makeSound();

    dog.displayInfo();
    dog.makeSound();

    return 0;
}
