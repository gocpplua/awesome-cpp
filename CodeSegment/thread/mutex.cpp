#include "pch.h"
#include <iostream>
#include<thread>
#include <mutex>
#include <vector>

std::mutex g_lock;

void mutexfunc1()
{
    g_lock.lock();
    std::cout << __FUNCTION__ << " " << __LINE__ << " " << "thread id:" << std::this_thread::get_id() << std::endl;
    g_lock.unlock();
}

void mutexfunc2()
{
    std::lock_guard<std::mutex> locker(g_lock);
    std::cout << __FUNCTION__ << " " << __LINE__ << " " << "thread id:" << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::vector<std::thread> g_list;
    std::thread t1(mutexfunc1); g_list.push_back(std::move(t1));
    std::thread t2(mutexfunc1); g_list.push_back(std::move(t2));
    std::thread t3(mutexfunc1); g_list.push_back(std::move(t3));
    std::thread t4(mutexfunc2); g_list.push_back(std::move(t4));
    std::thread t5(mutexfunc2); g_list.push_back(std::move(t5));
    std::thread t6(mutexfunc2); g_list.push_back(std::move(t6));
    //std::thread t7(mutexfunc2); g_list.push_back(t7);// 因为 thread& operator=(const thread&) = delete;， so 这种用法错误
    for (auto &thread : g_list)
    {
        thread.join();
    }
    return 0;
}