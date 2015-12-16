#include <iostream>
#include <limits>
#include <vector>
#include <string>

int fib(int n);
double e(int n);
double pi(int n);
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

//---------------------------------------------------------------------------------+
// double e                                                                        |
// Uses taylor expansion e^x = 1 + x/1! + x^2/2! + x^3/3! + ...                    |
// Re-written as e^x = 1 + (x/1)(1 + (x/2)(1 + (x/3)(...)))                        |
// I don't understand this math reduction, but it appears to work for x = 1:       |
// http://www.geeksforgeeks.org/program-to-efficiently-calculate-ex/               |
//---------------------------------------------------------------------------------+
double e(int n) {
    double sum = 1;
    for (int i = n - 1; i > 0; --i) {
        sum = 1 + sum / i;
    }
    return sum;
}

//---------------------------------------------------------------------------------+
// double pi                                                                       |
// Uses the second algorithm: http://en.wikipedia.org/wiki/Pi#Rate_of_convergence  |
// Stop case for iterating is when the difference after n + 1 digits == 0          |
// This is only actually truly accurate up to 7 digits, then it diverges from pi   |
// I avoid infinite loops with to_string instead of more accurate comparisons      |
//---------------------------------------------------------------------------------+
double pi(int n) {
    double sum = 3, prev;
    int i = 1, i2 = 2;

    do {
        prev = sum;
        sum += (i % 2 == 0 ? -4 : 4)
            / (double)(i2 * (i2 + 1) * (i2 + 2));

        i2 = 2 * ++i;
    } while (std::to_string(prev) != std::to_string(sum));

    return sum;
}

//---------------------------------------------------------------------------------+
// int fib                                                                         |
// Uses a dynamic programming method and a static vector for reuse effeciency      |
// Thankfully this algorithm is simple and familiar enough google was not required |
//---------------------------------------------------------------------------------+
int fib(int n) {
    static std::vector<int> fibs{0, 1};
    int last = fibs.size();
    if (n >= last) {
        fibs.resize(n + 1);
        for (int i = last; i <= n; ++i) {
            fibs[i] = fibs[i - 2] + fibs[i - 1];
        }
    }
    return fibs[n];
}
