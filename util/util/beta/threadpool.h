#pragma once

#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
// https://icharle.com/c11threadpool.html

namespace icharle {
	class ThreadPool {
	public:
		using Task = std::function<void()>;

		ThreadPool(int threadNum);

		bool addTask(const Task&);

		~ThreadPool();

	private:
		void Run();

	private:
		bool _stop;
		std::vector<std::thread*> _threads;
		std::mutex _mutex;
		std::condition_variable _cond;
		std::queue<Task> _tasks;
	};
}
