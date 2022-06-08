#pragma once

#include <future>
#include <thread>
#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>


class ThreadPool
{
	std::vector <std::thread> threads;
	std::queue <std::function <void()>> pool_queue;
	std::atomic <bool> state;
	std::condition_variable condition;
	std::mutex locker;

public:
	explicit ThreadPool(size_t);
	~ThreadPool();

	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
		std::unique_lock <std::mutex> lock(locker);
        using packaged = std::packaged_task<decltype(func(args...))()>;
		auto task_ptr = std::make_shared<packaged>(packaged(move(std::bind(func, args...))));
		auto task = [task_ptr](){ (*task_ptr)(); };
		pool_queue.emplace(task);
		lock.unlock();
		condition.notify_one();
		return task_ptr->get_future();
	}
};