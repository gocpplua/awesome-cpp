#include "pch.h"
#include <iostream>
#include<thread>
#include <mutex>
#include <vector>

std::once_flag onceFlag;

void onceFlagFunc()
{
    std::call_once(onceFlag, []() {std::cout << "onceFlagFunc" << std::endl; });
}

int main()
{
    std::thread t1(onceFlagFunc);
    std::thread t2(onceFlagFunc);
    std::thread t3(onceFlagFunc);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}

