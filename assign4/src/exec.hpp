#pragma once

#include <chrono>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#include "split.hpp"

class Command {
public:
    std::string command;
    std::vector<std::string> argv;
    int argc;

    Command() {}
    Command(std::string c) {
        command = c;
        argv = Split(command, ' ');
        argc = argv.size();
    }
};

bool pcommand(std::string &command, std::vector<std::string> &history, std::chrono::microseconds &exectime);
void phistory(std::vector<std::string> &history);
void ptime(std::chrono::microseconds &exectime);
void exec(const std::vector<std::string> &argv, const int &argc);
