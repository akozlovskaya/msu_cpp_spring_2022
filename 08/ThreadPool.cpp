#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t poolSize)
{
    for (size_t i = 0; i < poolSize; ++i) {
        auto new_thread = [this]()  {
            while (true) {
                std::unique_lock <std::mutex> lock(locker);
                auto predicate = [this] {
                    return !(state && pool_queue.empty());
                };
                condition.wait(lock, predicate);
                if (!state && pool_queue.empty()) return;
                auto task = move(pool_queue.front());
                pool_queue.pop();
                lock.unlock();
                task();
           }
        };
        threads.emplace_back(new_thread);
    }
}

ThreadPool::~ThreadPool()
{
    state = false;
    condition.notify_all();
    for (auto it = threads.begin(); it != threads.end(); ++it)
        it->join();
}