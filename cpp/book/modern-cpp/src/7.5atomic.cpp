// clang++ book/modern-cpp/src/7.5atomic.cpp -pthread -latomic
// 不适用 -latomic 编译出错:  undefined reference to `__atomic_is_lock_free'
#include <atomic>
#include <thread>
#include <iostream>

struct A {
    float x;
    int y;
    long long z;
};

std::atomic<int> count = {0};

int main() {
    std::thread t1([](){
        count.fetch_add(1);
    });
    std::thread t2([](){
        count++;        // 等价于 fetch_add
        count += 1;     // 等价于 fetch_add
    });
    t1.join();
    t2.join();
    std::cout << count << " " << count.is_lock_free() <<std::endl;

    std::atomic<A> a;
    std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    return 0;
}