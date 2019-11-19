// thread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<thread>
class X
{
public:
    void do_lengthy_work(int num = -1) { std::cout << "param:" << num << std::endl; }
};

void func()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "start " << __FUNCTION__ << ":thread id = " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "end " << __FUNCTION__ << ":thread id = " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void funcArgs(int a)
{
	std::cout << "start " << __FUNCTION__ << ":thread id = " << std::this_thread::get_id() << ", a = " << a << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "end " << __FUNCTION__ << ":thread id = " << std::this_thread::get_id() << ", a = " << a << std::endl;

}
int main()
{
	std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;
	std::thread t1(func);
	std::thread t2(funcArgs, 1);
	//t1.detach();//加上这句代码后，就不能在使用t1.join

	//xx.join 表示一定要等到这个线程结束了，才会执行到下一个代码行
	std::cout << "t1.join" << std::endl;
	t1.join(); //去掉这句代码会导致崩溃，可以尝试定位下这个崩溃
	std::cout << "t2.join" << std::endl;
	t2.join();

    X my_x;
    std::thread t3(&X::do_lengthy_work, &my_x, 100); // 1
    std::cout << "t3.join" << std::endl;
    t3.join();

	std::cout << "Hello World!\n";
	return 0;
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
