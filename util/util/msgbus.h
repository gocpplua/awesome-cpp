#pragma once
#include<string>
#include <shared_mutex>
#include <map>
#include <any>
#include <iostream>
using namespace std;

namespace util {
/// 消息总线实现
/// 该总线会在publish时同线程同步调用所有注册函数
/// 若使用异步调用可使用buspool(一个带线程池的总线)
///
/// 

	namespace msgbus {
		class msgbus{ // 可以继承 private boost::noncopyable 实现禁止copy类
		public:
			template<typename F>
			void subscribe(string& topic, F&& f);

			template<typename F>
			void publish(const string& topic);

		private:
			std::shared_mutex mutex_;
			//std::multimap<string, std::any> msg_map_;
		};




		template<typename F>
		void msgbus::subscribe(std::string& topic, F&& f) {

		}
		
		template<typename F>
		void msgbus::publish(const string& topic)
		{

		}

	}
}