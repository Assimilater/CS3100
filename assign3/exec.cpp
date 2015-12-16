#include "exec.hpp"

//---------------------------------------------------------------------------------+
// bool exec                                                                       |
// Parse the line typed by the user and execute the command                        |
// If the command is exit, return false to close the program                       |
// Update the history and clocked wait time for child processes as necessary       |
//---------------------------------------------------------------------------------+
bool exec(std::string &command, std::vector<std::string> &history, std::chrono::microseconds &exectime) {
    using namespace std;
    vector<string> argv = Split(command, ' ');

    // Early exit cases
    int argc = argv.size();
    if (argc == 0) { return true; }
    if (argv[0] == "exit") { return false; }

    // Predefined commands
    if (argv[0] == "^") {
        if (argc > 1) {
            try {
                int histID = stoi(argv[1]);
                if (history.size() >= histID && histID > 0) {
                    return exec(history[histID - 1], history, exectime);
                } else {
                    cout << "ID " << histID << " not found in command history" << endl;
                }
            } catch (...) {
                cout << "Unable to parse ID from: \"" << argv[1] << "\"" << endl;
            }
        } else {
            cout << "Missing history ID argument" << endl;
        }
        return true;
    }

    if (argv[0] == "history") {
        // Insert history into the history immediately because otherwise
        // it might be confusing for the user in combination with "^"
        history.insert(history.begin(), command);

        // Print the history
        cout << "--- History ---" << endl;
        for (int i = history.size(); i > 0; --i) {
            cout << i << ": " << history[i - 1] << endl;
        }
        return true;
    }

    if (argv[0] == "ptime") {
        auto sec = chrono::duration_cast<chrono::seconds>(exectime);
        auto milli = chrono::duration_cast<chrono::milliseconds>(exectime - sec);
        auto micro = chrono::duration_cast<chrono::microseconds>(exectime - sec - milli);

        history.insert(history.begin(), command);
        cout << "Time executing child processes: " << endl
            << sec.count() << " seconds" << endl
            << milli.count() << " milliseconds" << endl
            << micro.count() << " microseconds" << endl;

        return true;
    }

    // Direct commands
    history.insert(history.begin(), command);
    if (fork()) {
        auto start = std::chrono::system_clock::now();
        wait(NULL);

        // Stop the clock and add it to the total
        auto stop = std::chrono::system_clock::now();
        exectime += chrono::duration_cast<chrono::microseconds>(stop - start);

        return true;
    } else {
        int vpargc = (int)argv.size();

        // Memory deallocation will occur when the process terminates (shortly)
        char** vpargs = new char*[vpargc + 1];

        // Copy the strings into char* format
        for (int i = 0; i < vpargc; ++i) {
            int len = argv[i].length() + 1;

            vpargs[i] = new char[len];
            strncpy(vpargs[i], argv[i].c_str(), len);
        }

        // Set the last element to NULL to satisfy execvp requirements
        vpargs[vpargc] = NULL;

        // Execute the requested command with the appropriate arguments
        execvp(vpargs[0], vpargs);

        // If execution continues to this point, execvp failed
        cout << "Command not found: " << vpargs[0] << endl;

        // Return false to exit the child process
        return false;
    }
}
