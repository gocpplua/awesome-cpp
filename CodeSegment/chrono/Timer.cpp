// C++ 工具库: 
// 1、计时器Timer
#include <iostream>
#include<chrono>
#include <thread>

namespace YQTools {
    class Timer {
    public:
        Timer():timebegin_(std::chrono::high_resolution_clock::now()){}
        void reset() {
            timebegin_ = std::chrono::high_resolution_clock::now();
        }

        template<typename Duration=std::chrono::milliseconds>
        // 默认是毫秒
        int64_t elapsed() const {
            return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - timebegin_).count();
        }

        // 微秒 符号μs（英语：microsecond ）
        int64_t elapsed_us() const {
            return elapsed<std::chrono::microseconds>();
        }

        // 豪秒 符号ms（英语：millisecond  ）
        int64_t elapsed_ms() const {
            return elapsed<std::chrono::milliseconds>();
        }

        int64_t elapsed_s() const {
            return elapsed<std::chrono::seconds>();
        }

        int64_t elapsed_minutes() const {
            return elapsed<std::chrono::minutes>();
        }

        int64_t elapsed_hours() const {
            return elapsed<std::chrono::hours>();
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> timebegin_;
    };
}

int main() {
    YQTools::Timer tm;
    std::this_thread::sleep_for(std::chrono::seconds(6));
    std::cout << tm.elapsed() << std::endl;
    std::cout << tm.elapsed_hours() << std::endl;
    std::cout << tm.elapsed_minutes() << std::endl;
    std::cout << tm.elapsed_s() << std::endl;
    std::cout << tm.elapsed_ms() << std::endl;

    tm.reset();
    std::cout << tm.elapsed_us() << std::endl;
    return 0;
}