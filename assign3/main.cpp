#include "exec.hpp"

int main() {
    std::string command;
    std::vector<std::string> history{};
    std::chrono::microseconds exectime(0);
    do {
        std::cout << "[cmd]: ";
        std::getline(std::cin, command);
    } while (exec(command, history, exectime));

    return 0;
}
