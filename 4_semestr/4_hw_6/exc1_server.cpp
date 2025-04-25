#include <iostream>
#include <cstdlib>
#include <ctime>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace std;

const int PORT = 12345;

int main() {
    io_service io_service;
    ip::tcp::acceptor acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), PORT));

    srand(static_cast<unsigned int>(time(0)));
    int target_number = rand() % 100 + 1; // Загаданное число от 1 до 100

    cout << "Server: Загадано число от 1 до 100" << endl;

    while (true) {
        ip::tcp::socket socket(io_service);
        acceptor.accept(socket);
        
        cout << "Client connected" << endl;

        while (true) {
            int guess;
            boost::system::error_code error;

            boost::asio::read(socket, boost::asio::buffer(&guess, sizeof(guess)), error);
            if (error) break;

            cout << "Client guessed: " << guess << endl;

            if (guess < target_number) {
                const char* response = "Загаданное число больше!";
                boost::asio::write(socket, boost::asio::buffer(response, strlen(response)));
            } else if (guess > target_number) {
                const char* response = "Загаданное число меньше!";
                boost::asio::write(socket, boost::asio::buffer(response, strlen(response)));
            } else {
                const char* response = "Поздравляем! Вы угадали число!";
                boost::asio::write(socket, boost::asio::buffer(response, strlen(response)));
                break;
            }
        }
    }

    return 0;
}
