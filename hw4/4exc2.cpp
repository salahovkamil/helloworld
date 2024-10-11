#include <iostream>
#include <string>

using namespace std;

// Структура для автора книги
struct Author {
    string firstName;
    string lastName;
};

// Структура для книги
struct Book {
    string title;
    Author author;
    int year;
    int pages;

    // Конструктор по умолчанию
    Book() {
        title = "Неизвестно";
        author.firstName = "Неизвестно";
        author.lastName = "Неизвестно";
        year = 0;
        pages = 0;
    }

    // Функция-член для отображения информации о книге
    void displayBook() {
        cout << "Название книги: " << title << endl;
        cout << "Автор: " << author.firstName << " " << author.lastName << endl;
        cout << "Год издания: " << year << endl;
        cout << "Количество страниц: " << pages << endl;
        cout << "------------------------------" << endl;
    }
};

// Функция для создания книги
Book createBook() {
    Book book;
    cout << "Введите название книги: ";
    getline(cin, book.title);
    cout << "Введите имя автора: ";
    getline(cin, book.author.firstName);
    cout << "Введите фамилию автора: ";
    getline(cin, book.author.lastName);
    cout << "Введите год издания: ";
    cin >> book.year;
    cout << "Введите количество страниц: ";
    cin >> book.pages;
    cin.ignore(); // Очищаем буфер ввода
    return book;
}

int main() {
    const int bookCount = 3;
    Book books[bookCount];

    // Инициализация книг
    for (int i = 0; i < bookCount; i++) {
        cout << "Книга " << (i + 1) << ":" << endl;
        cout << "Хотите ввести данные о книге? (да/нет): ";
        string choice;
        getline(cin, choice);

        if (choice == "да") {
            books[i] = createBook();
        } else {
            books[i] = Book(); // Используем значения по умолчанию
        }
    }

    // Вывод информации о каждой книге
    cout << "\nИнформация о книгах:\n";
    for (int i = 0; i < bookCount; i++) {
        books[i].displayBook();
    }

    return 0;
}
