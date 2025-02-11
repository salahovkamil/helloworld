#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    const string firstName;     // Имя студента
    const string lastName;      // Фамилия студента
    string group;               // Номер группы
    int age;                    // Возраст студента
    int XP;                     // Опыт студента
    int money;                  // Количество денег
    int studentTime;            // Время студента (в часах)
    int life;                   // Показатель жизни

public:
    int grade;
    Student(string fName, string lName, string gr, int initialGrade, int initialMoney)
        : firstName(fName), lastName(lName), group(gr), age(19), XP(0), money(initialMoney), studentTime(0), life(100), grade(initialGrade) {
    }

    // Конструктор по умолчанию с автоматической оценкой 10
    Student(string fName, string lName, string gr, int initialMoney)
        : firstName(fName), lastName(lName), group(gr), age(19), XP(0), money(initialMoney), studentTime(0), life(100), grade(10) {}

    void eat(int cost) {
        if (money >= cost) {
            money -= cost;
            XP += 5; // добавляем XP за еду
        } else {
            cout << "Ошибка: недостаточно денег для еды!" << endl;
        }
    }

    // Метод: Учёба
    void study(int hours) {
        if (studentTime >= 24) {
            XP -= hours * 3; // урон увеличивается
        } else {
            XP -= hours;
        }
        studentTime += hours;
    }

    // Метод: Сон
    void sleep(int hours) {
        XP += hours * 2; // восстанавливаем XP
        if (hours > 6) {
            studentTime = 0; // сбрасываем счетчик времени
        }
    }

    // Метод: Работа
    void work(int hours) {
        if (hours >= 24) {
            XP -= hours * 3; // урон увеличивается
        } else {
            XP -= hours;
        }
        money += hours * 10; // заработок за часы работы
    }

    // Метод: Развлечения
    void entertainment(int hours, int cost) {
        if (money >= cost) {
            money -= cost;
            if (studentTime >= 24) {
                XP += hours / 3; // делим XP на 3
            } else {
                XP += hours;
            }
        } else {
            cout << "Ошибка: недостаточно денег для развлечений!" << endl;
        }
    }

    // Метод: Получение значения жизни
    int getLife() const {
        return life;
    }

    // Метод: Получение информации о деньгах
    int getMoney() const {
        return money;
    }

    // Метод: Получение оставшегося времени в сутках
    int getRemainingTime() const {
        return 24 - studentTime; // оставшееся время
    }

    // Метод: Получение всей информации о студенте
    void getStudentInfo() const {
        cout << "Имя: " << firstName << endl;
        cout << "Фамилия: " << lastName << endl;
        cout << "Группа: " << group << endl;
        cout << "Возраст: " << age << endl;
        cout << "XP: " << XP << endl;
        cout << "Деньги: " << money << endl;
        cout << "Время студента: " << studentTime << " часов" << endl;
        cout << "Оценка: " << grade << endl;
        cout << "Жизнь: " << life << endl;

        if (life <= 0) {
            cout << "Ошибка: Ушёл в академ!" << endl;
        }
    }
};

int main() {
    // Пример создания студента
    Student student1("Иван", "Иванов", "101", 100); // Оценка по умолчанию 10 и 100 денег
    Student student2("Петр", "Петров", "102", 5);   // Пользователь вводит оценку

    student1.getStudentInfo();
    student2.getStudentInfo();

    // Пример использования методов
    student1.eat(10);
    student1.study(2);
    student1.sleep(8);
    student1.work(5);
    
    student1.entertainment(3, 10);

    student1.getStudentInfo();

    return 0;
}
