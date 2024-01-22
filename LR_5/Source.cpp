#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable readCV, writeCV;

bool canRead = true;

void reader(const std::string& fileName) {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        readCV.wait(lock, [] { return canRead; });

        std::ifstream file(fileName);
        std::string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                std::cout << "Reader: " << line << std::endl;
            }
            file.close();
        }

        canRead = false;
        writeCV.notify_one();

        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void writer(const std::string& fileName) {
    int counter = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        writeCV.wait(lock, [] { return !canRead; });

        std::ofstream file(fileName, std::ofstream::trunc);
        if (file.is_open()) {
            file << "Data " << counter++ << std::endl;
            file.close();
        }

        canRead = true;
        readCV.notify_one();

        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(0));
    }
}

int main() {
    std::string fileName = "example.txt";

    std::thread readerThread(reader, fileName);
    std::thread writerThread(writer, fileName);

    readerThread.join();
    writerThread.join();

    return 0;
}
