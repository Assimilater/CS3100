#include "Assign2e.hpp"

double e(int n) {
    double sum = 1;
    for (int i = n - 1; i > 0; --i) {
        sum = 1 + sum / i;
    }
    return sum;
}
