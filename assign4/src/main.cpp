#include "pipe.hpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <string>

int main() {
    std::string command;
    std::vector<std::string> history{};
    std::chrono::microseconds exectime(0);
    do {
        std::cout << "[cmd]: ";
        std::getline(std::cin, command);
        command = prepare(command, history);

        // Add non-empty commands to the history
        if (command != "") {
            history.insert(history.begin(), command);
        }
    } while (pexec(command, history, exectime));

    return 0;
}
