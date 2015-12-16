#pragma once
#include "pQueue.hpp"
#include <random>

class Random {
private:
    std::mutex mutex;
    std::default_random_engine gen;
    std::normal_distribution<double> dist;
public:
    Random() : dist(50, 10), gen((unsigned int)time(0)) {}
    int next();
};

void producer(int, Random&, std::mutex&, SynchronizedPriorityQueue<int>&);
void consumer(int, std::mutex&, SynchronizedPriorityQueue<int>&);
