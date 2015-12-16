#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <dlfcn.h>

enum Trig {
    SIN = 0,
    COS = 1,
    TAN = 2
};

double evaluateTrig(double(*trig)(double)) {
    double i = 0, sum = 0, tempi, tempsum;
    do {
        tempi = (int)i;
        /*
        switch (tempi) {
            case 0: case 90: case 180:
                std::cout << i << "  " << trig(i) << std::endl;
                break;
        }
        //*/

        tempsum = trig(i);
        if ((tempsum <= 1 && tempsum >= -1) || (tempi < 88 || (tempi > 92 && tempi < 268) || tempi > 272)) {
            sum += tempsum;
        }
        i += 0.1;
    } while (i < 360);

    //std::cout << std::endl << std::endl;
    return sum;
}

void evaluateFile(void* handle, double* table) {
    if (!handle) {
        std::cout << "Couldn't open the shared library, error: " << dlerror() << std::endl;
        exit(1);
    }

    void(*init)() = (void(*)())dlsym(handle, "init");
    double(*mySin)(double) = (double(*)(double))dlsym(handle, "mySin");
    double(*myCos)(double) = (double(*)(double))dlsym(handle, "myCos");
    double(*myTan)(double) = (double(*)(double))dlsym(handle, "myTan");
    if (dlerror() != NULL) {
        std::cout << "Missing required methods, error: " << dlerror() << std::endl;
        exit(1);
    }

    // Evaluate each method in the file
    init();
    table[Trig::SIN] = evaluateTrig(mySin);
    table[Trig::COS] = evaluateTrig(myCos);
    table[Trig::TAN] = evaluateTrig(myTan);

    dlclose(handle);
}

int main() {
    double stdfnc[3], lookup[3];
    evaluateFile(dlopen("./trig-std.so", RTLD_LAZY), stdfnc);
    evaluateFile(dlopen("./trig-lookup.so", RTLD_LAZY), lookup);

    // Print out the table
    std::cout << std::setprecision(10) << std::left
        << std::setw(10) << " "
        << std::setw(20) << "trig-lookup.so"
        << std::setw(20) << "trig-std.so"
        << std::setw(20) << "difference"
        << std::endl

        << std::setw(65) << std::setfill('-') << "-"
        << std::endl << std::setfill(' ')

        << std::setw(10) << "sin"
        << std::setw(20) << lookup[Trig::SIN]
        << std::setw(20) << stdfnc[Trig::SIN]
        << std::setw(20) << lookup[Trig::SIN] - stdfnc[Trig::SIN]
        << std::endl

        << std::setw(10) << "cos"
        << std::setw(20) << lookup[Trig::COS]
        << std::setw(20) << stdfnc[Trig::COS]
        << std::setw(20) << lookup[Trig::COS] - stdfnc[Trig::COS]
        << std::endl

        << std::setw(10) << "tan"
        << std::setw(20) << lookup[Trig::TAN]
        << std::setw(20) << stdfnc[Trig::TAN]
        << std::setw(20) << lookup[Trig::TAN] - stdfnc[Trig::TAN]
        << std::endl;

    return 0;
}
