#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SynchronizedPriorityQueue {
private:
    std::priority_queue<T> queue;
    std::condition_variable get;
    std::mutex mutex;

public:
    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex);
        get.wait(lock, [&] { return queue.size() > 0; });

        T val = queue.top();
        queue.pop();
        return val;
    }
    void enqueue(T value) {
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(value);
        get.notify_one();
    }
    std::size_t size() {
        return queue.size();
    }
};
