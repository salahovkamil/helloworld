#include <iostream>
#include <map>
#include <string>

class PhoneBook {
private:
    std::map<std::string, std::string> contacts; // Имя контакта как ключ, номер телефона как значение

public:
    void addContact(const std::string& name, const std::string& phone) {
        contacts[name] = phone; // Добавить или обновить контакт
        std::cout << "Контакт добавлен: " << name << " - " << phone << std::endl;
    }

    void removeContact(const std::string& name) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            contacts.erase(it);
            std::cout << "Контакт удален: " << name << std::endl;
        } else {
            std::cout << "Контакт не найден: " << name << std::endl;
        }
    }

    void searchContact(const std::string& name) const {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            std::cout << "Найден контакт: " << it->first << " - " << it->second << std::endl;
        } else {
            std::cout << "Контакт не найден: " << name << std::endl;
        }
    }

    void displayContacts() const {
        if (contacts.empty()) {
            std::cout << "Телефонная книга пуста." << std::endl;
            return;
        }
        std::cout << "Список контактов:" << std::endl;
        for (const auto& contact : contacts) {
            std::cout << contact.first << " - " << contact.second << std::endl;
        }
    }
};

int main() {
    PhoneBook phoneBook;
    
    phoneBook.addContact("Алексей", "123-456-789");
    phoneBook.addContact("Мария", "987-654-321");
    
    phoneBook.displayContacts();

    phoneBook.searchContact("Алексей");
    
    phoneBook.removeContact("Мария");
    phoneBook.displayContacts();
    
    phoneBook.removeContact("Ольга"); // Попытка удалить несуществующий контакт

    return 0;
}
