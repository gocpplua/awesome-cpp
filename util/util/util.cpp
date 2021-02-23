// util.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <atomic>
#include "workthread.h"
#include "msgbus.h"
#include "beta/threadpool.h"
//#define WORK_THREAD

#ifdef WORK_THREAD
class MyThread : public util::WorkThread {
    virtual void work() {
        std::cout << "MyThread" << std::endl;
    }
};


int main()
{
    MyThread myThread;
    myThread.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Hello World!\n";
}
#endif

std::atomic_int ato_count = 0;
void fun() {
    std::cout << ato_count++ << endl;
}

int main() {
    icharle::ThreadPool pool(3);
    char c = 'a';
    do 
    {
        c = getchar();
        pool.addTask(fun);
    } while (c != 'q');
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
