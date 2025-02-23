#include <iostream>
#include <deque>
#include <string>

class TaskManager {
private:
    std::deque<std::pair<std::string, bool>> tasks; // bool - true для высокого приоритета

public:
    void addTask(const std::string& task, bool highPriority) {
        if (highPriority) {
            tasks.push_front({task, highPriority}); // Добавить в начало для высокого приоритета
        } else {
            tasks.push_back({task, highPriority}); // Добавить в конец для низкого приоритета
        }
    }

    void executeTask() {
        if (tasks.empty()) {
            std::cout << "Нет задач в очереди" << std::endl;
            return;
        }

        auto task = tasks.front();
        std::cout << "Выполнение задачи: " << task.first << std::endl;
        tasks.pop_front(); // Удалить выполненную задачу
    }

    int getTaskCount() const {
        return tasks.size();
    }
};

int main() {
    TaskManager manager;
    manager.addTask("Задача 1", true);   // Высокий приоритет
    manager.addTask("Задача 2", false);  // Низкий приоритет
    manager.addTask("Задача 3", true);   // Высокий приоритет

    std::cout << "Количество задач в очереди: " << manager.getTaskCount() << std::endl;

    manager.executeTask(); // Выполнить первую высокоприоритетную задачу
    std::cout << "Количество задач в очереди: " << manager.getTaskCount() << std::endl;

    manager.executeTask(); // Выполнить задачу
    std::cout << "Количество задач в очереди: " << manager.getTaskCount() << std::endl;

    manager.executeTask(); // Выполнить задачу
    std::cout << "Количество задач в очереди: " << manager.getTaskCount() << std::endl;

    manager.executeTask(); // Показать сообщение, что задач больше нет

    return 0;
}
