#include <iostream>
#include <string>

using namespace std;


struct Author {
    string firstName;  
    string lastName;   
};

struct Book {
    string title;          
    Author author;        
    int year;             
    int pageCount;        
    Book() : title("Неизвестно"), year(0), pageCount(0) {
        author.firstName = "Неизвестно";
        author.lastName = "Неизвестно";
    }

    void displayBook() {
        cout << "Название книги: " << title << endl;
        cout << "Автор: " << author.firstName << " " << author.lastName << endl;
        cout << "Год издания: " << year << endl;
        cout << "Количество страниц: " << pageCount << endl;
    }
};

// Функция для создания экземпляра книги на основе пользовательского ввода
Book createBook() {
    Book newBook;
    
    cout << "Введите название книги: ";
    getline(cin, newBook.title);
    
    cout << "Введите имя автора: ";
    getline(cin, newBook.author.firstName);
    
    cout << "Введите фамилию автора: ";
    getline(cin, newBook.author.lastName);
    
    cout << "Введите год издания: ";
    cin >> newBook.year;
    
    cout << "Введите количество страниц: ";
    cin >> newBook.pageCount;
    cin.ignore();  // Для очистки буфера ввода после cin

    return newBook;
}

int main() {
    const int bookCount = 3;  // Количество книг в библиотеке
    Book library[bookCount];   // Массив книг

    // Инициализация книг
    for (int i = 0; i < bookCount; ++i) {
        char choice;
        cout << "Хотите ввести данные для книги " << (i + 1) << "? (y/n): ";
        cin >> choice;
        cin.ignore();  // Очистка буфера ввода

        if (choice == 'y' || choice == 'Y') {
            library[i] = createBook();  // Создание книги с пользовательским вводом
        } else {
            library[i] = Book();  // Инициализация значениями по умолчанию
        }
    }

    // Вывод информации о книгах
    cout << "\nИнформация о книгах в библиотеке:\n";
    for (int i = 0; i < bookCount; ++i) {
        cout << "\nКнига " << (i + 1) << ":" << endl;
        library[i].displayBook();
    }

    return 0;
}
