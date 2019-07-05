// CodeSegment.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <random>
#include <array>
#include <time.h>
class A {
    virtual int test() { return 1; };
};
class B : public A {
    virtual int test() { throw "aaaa"; };
};

void print()
{

}

template<typename T, typename... Types>
void print(const T& firstAry, const Types&... args)
{
    std::cout << firstAry << std::endl;
    print(args...);
}

class a
{
public:
private:
	int m_d;
	char m_a[1024 * 1024];
	double m_c;
	int m_b;
};

int main()
{
	for (int i = 0; i < 1000; i++)
	{
		{
			std::unique_ptr<a> data(new a[10]);
			//a* data = new a[10];
		}
	}
    Test::setA(1);
    Test::setA(2);
    std::cout << "a = " << Test::getA() << std::endl;
    std::cout << "Hello World!\n";

    std::cout << __cplusplus << std::endl;
    print(1, "2323", 43);
    
    for (int i = 0; i < 100; i++)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1, 300);
        std::cout << "random:" <<dis(gen) << std::endl ;
    }

    for (int i = 0; i < 100; i++)
    {
        static std::default_random_engine default_engine(time(nullptr));
        const auto raw_result = default_engine();
        std::cout << "raw_result:" << raw_result << std::endl;

    }

    std::array<int, 5> arrTmp = {};
    for (int i = 0; i < arrTmp.size(); i++)
    {
        std::cout << arrTmp[i] << std::endl;
    }

    std::map<int, int> v;
    for (int i  = 0; i < 1000; i ++)
    {
        auto n = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(n);
        v[time % 10] = 1;
        std::cout << time << std::endl;
    }
    for (auto a : v)
    {
        std::cout << a.first << " " << a.second << std::endl;
    }
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
