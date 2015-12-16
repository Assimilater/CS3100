#pragma once

#include <chrono>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "split.hpp"
#include "exec.hpp"

class PipeData {
public:
    std::vector<Command> pipelines;
    int pipec;

    PipeData() {}
    PipeData(std::string command) {
        std::vector<std::string> commands = Split(command, " | ");
        pipec = commands.size();
        pipelines.resize(pipec);
        for (int i = 0; i < pipec; ++i) {
            pipelines[i] = Command(commands[i]);
        }
    }
};

std::string prepare(std::string &command, std::vector<std::string> &history);
bool pexec(std::string &command, std::vector<std::string> &history, std::chrono::microseconds &exectime);
