#include "ThreadPool.h"
using namespace std;
namespace icharle {
	ThreadPool::ThreadPool(int threadNum) :
		_stop(false),
		_threads(threadNum) {
		for (int i = 0; i < threadNum; ++i) {
			
			thread* temp = new thread(bind(&ThreadPool::Run, this));
			_threads[i] = temp;
		}
	}


	void ThreadPool::Run() {
		while (true) {
			std::unique_lock<std::mutex> lock(_mutex);
			while (!_stop && _tasks.empty()) {
				_cond.wait(lock);
			}
			if (_stop && _tasks.empty()) {
				return;
			}
			Task nextTask = _tasks.front();
			_tasks.pop();
			lock.unlock();
			nextTask();
		}
	}

	bool ThreadPool::addTask(const Task& task) {
		std::unique_lock<std::mutex> lock(_mutex);
		if (!_stop) {
			_tasks.emplace(task);
			lock.unlock();
			_cond.notify_one();
			return true;
		}
		return false;
	}

	ThreadPool::~ThreadPool() {
		std::unique_lock<std::mutex> lock(_mutex);
		_stop = true;
		lock.unlock();
		_cond.notify_all();
		for (size_t i = 0; i < _threads.size(); ++i) {
			_threads[i]->join();
		}
	}
}