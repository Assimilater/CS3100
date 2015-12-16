#include "pQueue.hpp"
#include "pcthread.hpp"
#include <iostream>
#include <string> // for integer parsing of argv
#include <chrono> // for starting each producer 200 ms apart
#include <random> // for shared random number generation
#include <thread>
#include <vector>

bool tryParseArg(char**, int, int&);

int main(int argc, char** argv) {
    // Validate input
    int p_size, c_size;
    if (argc != 3) {
        std::cout << "Invalid parameters" << std::endl;
        return 0;
    }
    if (!tryParseArg(argv, 1, p_size)) {
        std::cout << "Unable to parse producers \"" << argv[1] << "\" as an int" << std::endl;
        return 0;
    }
    if (!tryParseArg(argv, 2, c_size)) {
        std::cout << "Unable to parse consumers \"" << argv[2] << "\" as an int" << std::endl;
        return 0;
    }

    // Initialize the threads
    std::mutex mutex; // for synchronized output
    std::vector<std::thread> consumers(c_size);
    std::vector<std::thread> producers(p_size);
    SynchronizedPriorityQueue<int> queue;
    Random gen;

    for (int i = 0; i < c_size; ++i) {
        consumers[i] = std::thread(consumer, i + 1, std::ref(mutex), std::ref(queue));
    }
    for (int i = 0; i < p_size; ++i) {
        producers[i] = std::thread(producer, i + 1, std::ref(gen), std::ref(mutex), std::ref(queue));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Join the threads
    for (int i = 0; i < p_size; ++i) {
        producers[i].join();
    }
    for (int i = 0; i < c_size; ++i) {
        consumers[i].join();
    }

    return 0;
}

//---------------------------------------------------------------------------------+
// bool tryParseArg                                                                |
// Attempt to parse int (n) from the given argument                                |
// On sucesses, assign out the parsed value and return true                        |
//---------------------------------------------------------------------------------+
bool tryParseArg(char** argv, int i, int& out) {
    try {
        out = std::stoi(std::string(argv[i]));
        return true;
    } catch (...) {
        return false;
    }
}
