#include "Assign2Fib.hpp"

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
