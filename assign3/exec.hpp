#pragma once

#include <iostream>
#include <chrono>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#include "split.hpp"

bool exec(std::string &command, std::vector<std::string> &history, std::chrono::microseconds &exectime);
