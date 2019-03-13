// threadmessage.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//c++控制台（非窗口，非MFC框架）里线程如何通过自定义消息通信
// 参考:https://blog.csdn.net/fuck487/article/details/44244765

#include "pch.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <windows.h>
#define WM_MYMSG	WM_USER+100
struct A
{
    int a;
    int b;
};
void func1()
{
    while (true)
    {
        MSG msg;
        GetMessage(&msg, NULL, 0, 0);
        if (msg.message == WM_MYMSG)
        {
            A *st = (A*)msg.wParam;
            std::cout << std::this_thread::get_id() << ":" << "func1 recv WM_MYMSG(" << st->a << " " << st->b << ")"<< std::endl;
        }

    }
}

void func2(unsigned long long tID, unsigned long long tMainID)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    static int paramA = 1;
    static int paramB = 1;
    while (true)
    {
        A st;
        st.a = paramA;
        st.b = paramB;
        paramA++;
        paramB++;
        PostThreadMessage(tID, WM_MYMSG, (WPARAM)&st, 0);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        PostThreadMessage(tMainID, WM_MYMSG, (WPARAM)&st, 0);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// c++ 11 std::thread 线程 获取线程ID的整数值
unsigned long long getThreadIdOfString(const std::thread::id & id)
{
    std::ostringstream oss;
    oss << id;
    std::string stid = oss.str();
    unsigned long long tid = std::stoull(stid);
    return tid;
}

int main()
{
    std::thread t1(func1);
    std::thread::id tID1 =  t1.get_id();
    std::thread t2(func2, getThreadIdOfString(tID1), getThreadIdOfString(std::this_thread::get_id()));
    std::thread::id tID2 = t2.get_id();
    std::cout << "tID1:" << tID1 << " tID2:" << tID2 << std::endl;
    while (true)
    {
        MSG msg;
        GetMessage(&msg, NULL, 0, 0);
        if (msg.message == WM_MYMSG)
        {
            A *st = (A*)msg.wParam;
            std::cout << std::this_thread::get_id() << ":" << "main recv WM_MYMSG(" << st->a << " " << st->b << ")" << std::endl;
        }

    }

    t1.join();
    t2.join();
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
