#include "pcthread.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>

//---------------------------------------------------------------------------------+
// void synchedOutput                                                              |
// Output a string in a thread-safe manner                                         |
//---------------------------------------------------------------------------------+
void synchedOutput(std::mutex& mutex, std::string message) {
    // static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << message << std::endl;
}

//---------------------------------------------------------------------------------+
// int Random::next                                                                |
// Generate a random number (thread-safe) between 1-100 using the class's dist     |
//---------------------------------------------------------------------------------+
int Random::next() {
    std::unique_lock<std::mutex> lock(mutex);
    int num = dist(gen);

    if (num > 100) { return 100; }
    if (num < 1) { return 1; }
    return num;
}

//---------------------------------------------------------------------------------+
// void producer                                                                   |
// This thread adds randomly generated numbers to thread-safe priority queue       |
//---------------------------------------------------------------------------------+
void producer(int t_id, Random& gen, std::mutex& mutex, SynchronizedPriorityQueue<int>& queue) {
    // Give this thread its own stringstream and random number generator
    //std::stringstream out;
    //std::default_random_engine gen((unsigned int)time(0));
    //std::normal_distribution<double> dist(50, 10);

    while (true) {
        int num = gen.next();
        //int num = dist(gen);
        //if (num > 100) { num = 100; }
        //if (num < 1) { num =  1; }

        //out.clear();
        //out << "Producer Thread " << t_id << " submits " << num;
        //synchedOutput(mutex, out.str());
        {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Producer Thread " << t_id << " submits " << num << std::endl;
        }

        queue.enqueue(num);
        sleep(1);
    }
}

//---------------------------------------------------------------------------------+
// void consumer                                                                   |
// This thread periodically prints items off the thread-safe priority queue        |
//---------------------------------------------------------------------------------+
void consumer(int t_id, std::mutex& mutex, SynchronizedPriorityQueue<int>& queue) {
    // Give this thread its own stringstream
    //std::stringstream out;

    while (true) {
        int num = queue.dequeue();

        //out.clear();
        //out << "Consumer Thread " << t_id << " reports " << num;
        //synchedOutput(mutex, out.str());
        {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Consumer Thread " << t_id << " reports " << num << std::endl << std::endl;
        }

        sleep(3);
    }
}
