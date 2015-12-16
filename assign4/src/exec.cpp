#include "exec.hpp"

//---------------------------------------------------------------------------------+
// bool pcommand                                                                   |
// Parse and execute the given command                                             |
// If custom command, fork and track execution time (to be reported by ptime)      |
// return true if shell execution is to continue                                   |
//---------------------------------------------------------------------------------+
bool pcommand(std::string &command, std::vector<std::string> &history, std::chrono::microseconds &exectime) {
    std::vector<std::string> argv = Split(command, ' ');
    int argc = argv.size();

    if (argc == 0) {
        return true;
    } else if (argv[0] == "exit") {
        return false;
    } else if (argv[0] == "ptime") {
        ptime(exectime);
    } else if (argv[0] == "history") {
        phistory(history);
    } else {
        if (fork()) {
            // Start the clock and wait for the child process to terminate
            auto start = std::chrono::system_clock::now();
            wait(NULL);

            // Stop the clock and add it to the total
            auto stop = std::chrono::system_clock::now();
            exectime += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        } else {
            exec(argv, argc);
        }
    }

    return true;
}

//---------------------------------------------------------------------------------+
// void phistory                                                                   |
// Predefined command, prints the shell history                                    |
//---------------------------------------------------------------------------------+
void phistory(std::vector<std::string> &history) {
    std::cout << "--- History ---" << std::endl;
    for (int i = history.size(); i > 0; --i) {
        std::cout << i << ": " << history[i - 1] << std::endl;
    }
}

//---------------------------------------------------------------------------------+
// void phistory                                                                   |
// Predefined command, prints the time spent executing child processes             |
//---------------------------------------------------------------------------------+
void ptime(std::chrono::microseconds &exectime) {
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(exectime);
    auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(exectime - sec);
    auto micro = std::chrono::duration_cast<std::chrono::microseconds>(exectime - sec - milli);

    std::cout << "Time executing child processes: " << std::endl
        << sec.count() << " seconds" << std::endl
        << milli.count() << " milliseconds" << std::endl
        << micro.count() << " microseconds" << std::endl;
}

//---------------------------------------------------------------------------------+
// void exec                                                                       |
// Handles all commands not predefined by means of execvp (fork expected)          |
//---------------------------------------------------------------------------------+
void exec(const std::vector<std::string> &argv, const int &argc) {
    char** vpargs = new char*[argc + 1]; // Deallocated on termination (shortly)
    for (int i = 0; i < argc; ++i) { vpargs[i] = const_cast<char *>(argv[i].c_str()); }
    vpargs[argc] = NULL; // Set NULL sentinel for execvp
    execvp(vpargs[0], vpargs);

    // If execution continues to this point, execvp failed
    std::cout << "Command not found: " << vpargs[0] << std::endl;
    exit(EXIT_SUCCESS); // exit the child process
}
