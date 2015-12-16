#include <iostream>
#include <limits>
#include <string>
#include "Assign2e.hpp"
#include "Assign2pi.hpp"
#include "Assign2Fib.hpp"

bool tryParseArg(int argc, char** argv, int i, int& out);

int main(int argc, char** argv) {
    using namespace std;

    bool help = true;
    for (int i = 1; i < argc; ++i) {
        int temp;
        string arg = argv[i];

        if (arg == "-e") {
            if (tryParseArg(argc, argv, i + 1, temp)) {
                if (temp < 1 || temp > 30) {
                    cout << "Only values 1-30 may be used for calculating e" << endl;
                } else {
                    cout.precision(numeric_limits<double>::digits10 + 2);
                    cout << "e(" << temp << ") = " << e(temp) << endl;
                    help = false;
                }
            }
        } else if (arg == "-pi") {
            if (tryParseArg(argc, argv, i + 1, temp)) {
                if (temp < 1 || temp > 10) {
                    cout << "Only values 1-10 may be used for calculating pi" << endl;
                } else {
                    cout.precision(temp + 1);
                    cout << "pi(" << temp << ") = " << pi(temp) << endl;
                    help = false;
                }
            }
        } else if (arg == "-fib") {
            if (tryParseArg(argc, argv, i + 1, temp)) {
                if (temp < 0 || temp > 14) {
                    cout << "Only values 0-14 may be used for calculating fib" << endl;
                } else {
                    cout.precision(1);
                    cout << "fib(" << temp << ") = " << fib(temp) << endl;
                    help = false;
                }
            }
        }
    }

    if (help) {
        cout << "--- Assign 1 Help---" << endl
            << " -fib [n] Compute the fibonacci of [n]" << endl
            << " -e   [n] Compute 'e' using [n] iterations" << endl
            << " -pi  [n] Compute Pi accurate to [n] digits" << endl;
    }

    return 0;
}

//---------------------------------------------------------------------------------+
// bool tryParseArg                                                                |
// Attempt to parse int (n) from the given argument                                |
// On failures, print error messages and return false                              |
// On sucesses, assign out the parsed value and return true                        |
//---------------------------------------------------------------------------------+
bool tryParseArg(int argc, char** argv, int i, int& out) {
    using namespace std;
    if (i < argc) {
        try {
            out = stoi(string(argv[i]));
            return true;
        } catch (...) {}
        cout << "Unable to parse \"" << argv[i] << "\" as an int" << endl;
        return false;
    } else {
        cout << "Missing argument n after \"" << argv[i - 1] << "\"" << endl;
        return false;
    }
}
