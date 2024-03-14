#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

int main() {
    std::ofstream file("counter.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }

    int counter = 0;

    // while (true) {
        file << "Counter: " << counter++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

    file.close();
}
