#include <iostream>
#include <thread>
#include <vector>

void printHelloWorld(int thread_id, int total_threads) {
    std::cout << "Thread ID: " << thread_id 
              << ", Total Threads: " << total_threads 
              << ", Message: HelloWorld" << std::endl;
}

int main() {
    const int num_threads = 8;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(printHelloWorld, i, num_threads));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
//Вывод программы не всегда будет идентичен. Это связано с тем, что потоки выполняются асинхронно, 
//и их порядок выполнения может варьироваться при каждом запуске программы. 
//В зависимости от планировщика операционной системы и внутренней реализации потоков порядок, 
//в котором потоки начинают и заканчивают выполнение, может меняться. 
//Из-за этого порядок вывода может отличаться в разных запусках программы.