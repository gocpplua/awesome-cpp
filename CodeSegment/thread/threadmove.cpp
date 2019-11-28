#include "pch.h"
#include <iostream>
#include<thread>

void funcMove()
{
    std::cout << "func start" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "func end" << std::endl;
}

int mainMove()
{
    std::thread t1(funcMove);
    //t1.join();
    if (t1.joinable())
    {
        std::cout << __LINE__ <<"t1 is joinable" << std::endl;
    }
    else
    {
        std::cout << __LINE__ << "t1 is not joinable" << std::endl;
    }
    std::thread t2(std::move(t1));//此时t1 is not joinable，t2 is joinable
    if (t1.joinable())
    {
        std::cout << __LINE__ << "t1 is joinable" << std::endl;
    }
    else
    {
        std::cout << __LINE__ << "t1 is not joinable" << std::endl;
    }
    std::thread t3(std::move(t1)); //此时t3 is not joinable, 我们不能使用t3.join()
    t2.join();
    return 0;
}