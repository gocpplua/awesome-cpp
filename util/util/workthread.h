#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
using namespace std;

namespace util {
	class WorkThread {
	public:
		WorkThread():stoped_(true),delay_ms_(100) {

		}
		WorkThread(int delay_ms) :stoped_(true), delay_ms_(delay_ms) {

		}
		~WorkThread() {
			if (!stoped_.load())
			{
				stop();
				if (t_.joinable())
				{
					t_.join();
				}
			}
		}

		void start() {
			if (!stoped_.load())
			{
				return;
			}
			stoped_.store(false);
			t_ = std::thread([this] {
				std::unique_lock<std::mutex> lock(mutex_cv_); // 这里使用unique_lock更加符合语义。 因为wait_for会释放，然后再获取mutex
				while (!cv_.wait_for(lock, std::chrono::milliseconds(delay_ms_), [this] { return stoped_.load(); }))
				{
					// stoped_ = false 的适合才会被阻塞，当超时/被通知的时候会返回stoped_
					// 当线程正在执行中stoped_为false, 超时后返回false，此时为了让while继续，我们需要使用!cv.wait_for(XX), 执行完work又进行wait_for
					// 当我们调用stop(),此时stoped_为true，当超时/被通知的时候，返回true，然后while终止
					work();
				}
				});
		}

		void stop() {
			stoped_.store(true);
			std::lock_guard<std::mutex> lock(mutex_cv_);
			cv_.notify_all();
		}

		virtual void work() = 0;

		void set_delay_ms(int delay_ms) {
			std::lock_guard<std::mutex> lock(mutex_cv_);
			delay_ms_ = delay_ms;
		}
	private:
		std::thread t_;
		std::atomic_bool stoped_;
		std::mutex mutex_cv_;
		std::condition_variable cv_;
		int delay_ms_;
	};
}
