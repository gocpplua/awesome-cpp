// threadpoolmain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"threadpool.hpp"

int main()
{
    ThreadPool pool;
    std::thread thd1(
        [&pool]() {
        for (size_t i = 0; i < 10; i++)
        {
            auto thdId = std::this_thread::get_id();
            pool.AddTask([thdId] {
                std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
                std::cout << "同步线程1的线程ID:" << thdId << std::endl;
            });
        }
    }
    );

    std::thread thd2(
        [&pool]() {
        for (size_t i = 0; i < 10; i++)
        {
            auto thdId = std::this_thread::get_id();
            pool.AddTask([thdId] {
                std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
                std::cout << "同步线程2的线程ID:" << thdId << std::endl;
            });
        }
    }
    );

    std::this_thread::sleep_for(std::chrono::seconds(2));
    getchar();
    pool.Stop();
    thd1.join();
    thd2.join();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
