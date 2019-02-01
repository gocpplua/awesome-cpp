#include "pch.h"
#include <iostream>
#include<thread>
#include<future>
#include<utility>
int func(int x)
{
    return x + 2;
}

int main()
{
    std::packaged_task<int(int)> task(func);
    std::future<int> fut = task.get_future();

    std::thread(task, 2).detach();

    int value = fut.get();
    std::cout << "the result is " << value << std::endl;

    std::vector<std::future<int>> v;
    auto f = std::async(std::launch::async,
        [](int a, int b) { return a + b; }, 2, 3);
    v.push_back(f);
    std::cout << "the shared_future result is " << value << std::endl;


    return 0;
}