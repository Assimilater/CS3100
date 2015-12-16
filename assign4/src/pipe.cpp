#include "pipe.hpp"

//---------------------------------------------------------------------------------+
// string prepare                                                                  |
// Return the resulting command after resolving "^ #" history portions             |
//---------------------------------------------------------------------------------+
std::string prepare(std::string &command, std::vector<std::string> &history) {
    std::vector<std::string> argv = Split(command, ' ');
    int argc = argv.size();
    std::string out = "";
    for (int i = 0; i < argc; ++i) {
        if (argv[i] == "^") {
            if (argc > i + 1) {
                try {
                    int histID = stoi(argv[i + 1]);
                    if (history.size() >= histID && histID > 0) {
                        if (out != "") { out += ' '; }
                        out += history[histID - 1];
                        ++i; // Skip over the next argument
                    } else {
                        std::cout << "ID " << histID << " not found in command history" << std::endl;
                        return "";
                    }
                } catch (...) {
                    std::cout << "Unable to parse history ID from: \"" << argv[i + 1] << "\"" << std::endl;
                    return "";
                }
            } else {
                std::cout << "Missing history ID argument" << std::endl;
                return "";
            }
        } else {
            if (out != "") { out += ' '; }
            out += argv[i];
        }
    }
    return out;
}

//---------------------------------------------------------------------------------+
// bool pexec                                                                      |
// Check for and setup pipes, then execute each command                            |
//---------------------------------------------------------------------------------+
bool pexec(std::string &command, std::vector<std::string> &history, std::chrono::microseconds &exectime) {
    ///*
    static const int PIPE_COUNT = 2;
    static const int PIPE_WRITE = 1;
    static const int PIPE_READ = 0;
    static const int STDOUT = 1;
    static const int STDIN = 0;

    PipeData pd(command);

    if (pd.pipec == 0) { return true; }
    if (pd.pipec == 1) { return pcommand(pd.pipelines[0].command, history, exectime); }
    if (pd.pipec == 2) {
        int savedStdOut = dup(STDOUT);
        int savedStdIn = dup(STDIN);
        int pids[PIPE_COUNT];
        pid_t fWrite, fRead;

        // Create a new pipe for the next command pair to interact with
        pipe(pids);

        if (fWrite = fork() == 0) {
            // Open the write end of the new pipe
            dup2(pids[PIPE_WRITE], STDOUT);

            // Execute the left hand command
            exec(pd.pipelines[0].argv, pd.pipelines[0].argc);
            return false;
        }

        else if (fRead = fork() == 0) {
            // Open the read end for the next command
            dup2(pids[PIPE_READ], STDIN);

            // Close off the write end of the new pipe
            close(pids[PIPE_WRITE]);

            // Execute the right hand command
            exec(pd.pipelines[1].argv, pd.pipelines[1].argc);
            return false;
        }

        else {
            // Start the clock and wait for the child process to terminate
            auto start = std::chrono::system_clock::now();

            // Wait for the first child to finish
            int status;
            waitpid(fWrite, &status, 0);

            // Fully close down all the pipes
            close(pids[PIPE_WRITE]);
            close(pids[PIPE_READ]);

            // Close the second end of the pipe
            waitpid(fRead, &status, 0);

            // Stop the clock and add it to the total
            auto stop = std::chrono::system_clock::now();
            exectime += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            // Restore standard out and in
            dup2(savedStdOut, STDOUT);
            dup2(savedStdIn, STDIN);

            return true;
        }
    }

    std::cout << "This shell is only designed to handle one pipe";
    return true;

    //*/
    /*

    static const int PIPE_COUNT = 2;
    static const int PIPE_WRITE = 1;
    static const int PIPE_READ = 0;
    static const int STDOUT = 1;
    static const int STDIN = 0;

    std::vector<std::string> pipelines = Split(command, " |");
    int pipec = pipelines.size();
    bool out = true;

    if (pipec == 0) { return out; }
    if (pipec == 1) { return pcommand(pipelines[0], history, exectime); }
    if (pipec == 2) {
        int savedStdOut = dup(STDOUT);
        int savedStdIn = dup(STDIN);
        int pids[PIPE_COUNT];

        // Create a new pipe for the next command pair to interact with
        pipe(pids);

        // Open the write end of the new pipe
        dup2(pids[PIPE_WRITE], STDOUT);

        // Execute the left hand command
        out = pcommand(pipelines[0], history, exectime);

        if (out) {
            // Open the read end for the next command
            dup2(pids[PIPE_READ], STDIN);

            // Close off the write end of the new pipe
            close(pids[PIPE_WRITE]);

            // Execute the right hand command
            out = pcommand(pipelines[1], history, exectime);
        }

        // Fully close down all the pipes
        close(pids[PIPE_WRITE]);
        close(pids[PIPE_READ]);

        // Restore standard out and in
        dup2(savedStdOut, STDOUT);
        dup2(savedStdIn, STDIN);

        return out;
    }
    std::cout << "This shell is only designed to handle one pipe";
    return true;

    //*/
    /*

    static const int PIPE_COUNT = 2;
    static const int PIPE_WRITE = 1;
    static const int PIPE_READ = 0;
    static const int STDOUT = 1;
    static const int STDIN = 0;
    bool activePipe = 0;

    int savedStdOut = dup(STDOUT);
    int savedStdIn = dup(STDIN);
    int pids[PIPE_COUNT][PIPE_COUNT];

    std::vector<std::string> pipelines = Split(command, " |");
    int pipec = pipelines.size();
    bool out = true;

    if (pipec == 0) { return out; }
    for (int i = 0; i < pipec - 1; ++i) {
        // Create a new pipe for the coming command pair to interact with
        pipe(pids[activePipe]);

        // Open the write end of the new pipe
        dup2(pids[activePipe][PIPE_WRITE], STDOUT);

        if (out = pcommand(pipelines[i], history, exectime)) {
            // Close off the write end of the new pipe
            close(pids[activePipe][PIPE_WRITE]);

            // Open the read end of the pipe for the next command
            dup2(pids[activePipe][PIPE_READ], STDIN);

            // Close off the currently used read end (if created before)
            if (i != 0) {
                close(pids[!activePipe][PIPE_READ]);
            }

            // Alternate which of the two stored pipes is used
            activePipe = !activePipe;
        } else {
            // This should only happen for failed execvp calls
            // to ensure forked child processes terminate
            // or if the command "exit" is issued
            break;
        }
    }

    if (out) {
        out = pcommand(pipelines[pipec - 1], history, exectime);
    }

    // Fully close down all the pipes
    close(pids[activePipe][PIPE_WRITE]);
    close(pids[activePipe][PIPE_READ]);
    close(pids[!activePipe][PIPE_WRITE]);
    close(pids[!activePipe][PIPE_READ]);

    // Restore standard out and in
    dup2(savedStdOut, STDOUT);
    dup2(savedStdIn, STDIN);

    return out;
    //*/
}
