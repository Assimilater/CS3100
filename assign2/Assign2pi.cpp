#include "Assign2pi.hpp"

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
