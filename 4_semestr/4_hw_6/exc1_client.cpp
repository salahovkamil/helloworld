#include <iostream>
#include <boost>
#include <chrono>
#include <thread>

using namespace boost::asio;
using namespace std;

const int PORT = 12345;

int main() {
    io_service io_service;
    ip::tcp::socket socket(io_service);
    socket.connect(ip::tcp::endpoint(address::from_string("127.0.0.1"), PORT));

    while (true) {
        int guess;
        cout << "Введите ваше число (от 1 до 100): ";
        cin >> guess;

        boost::asio::write(socket, boost::asio::buffer(&guess, sizeof(guess)));

        char response[256];
        size_t len = socket.read_some(boost::asio::buffer(response));
        response[len] = '\0'; // Завершаем строку

        cout << "Ответ от сервера: " << response << endl;

        std::this_thread::sleep_for(std::chrono::seconds(10)); // Ждем 10 секунд перед отправкой следующего числа
    }

    return 0;
}
