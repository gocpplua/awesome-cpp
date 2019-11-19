#include "pch.h"
#include <iostream>
#include<thread>
#include<future>
#include<utility>
int func(int x)
{
    std::cout << "2222 " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "3333 " << std::endl;
    return x + 2;
}

int mainPromise()
{
    std::packaged_task<int(int)> task(func);
    std::future<int> fut = task.get_future();

    std::thread(std::move(task), 2).detach();
    std::cout << "11111 " << std::endl;
    int value = fut.get(); //这里会等待线程结束在往下执行
    std::cout << "the result is " << value << std::endl;

    std::vector<std::shared_future<int>> v;
    auto f = std::async(std::launch::async,
        [](int a, int b) { return a + b; }, 2, 3);
    v.push_back(std::move(f));
    std::cout << "the shared_future result is " << v[0].get() << std::endl;

    return 0;
}