// tupe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<string>
#include<tuple>
#include<memory>

// 打印任何大小 tuple 的帮助函数:https://zh.cppreference.com/w/cpp/utility/tuple/tuple_cat
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N - 1>::print(t);
        std::cout << ", " << std::get<N - 1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

template<class... Args>
void print(const std::tuple<Args...>& t)
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}
// 结束帮助函数

struct A;
struct B;
struct A
{
    std::shared_ptr<B> bptr;
    ~A()
    {
        std::cout << "A is delete!" << std::endl;
    }
};

struct B
{
    std::weak_ptr<A> aptr; // 这里使用shared_ptr会导致循环引用，从而出现内存泄漏
    ~B()
    {
        std::cout << "B is delete!" << std::endl;
    }
};

int main()
{
    int x = 1;
    int y = 2;
    std::string s = "a";
    auto tp = std::tie(x, y, s); // 头文件#include<tuple>

    //tupe解析方法一:
    int tpParamX = std::get<0>(tp); // 此时为C++17的用法:https://en.cppreference.com/w/cpp/utility/tuple/get
    std::cout << tpParamX << std::endl;

    //tupe解析方法二:
    int tpX, tpY;
    std::tie(tpX, tpY, std::ignore) = tp;
    std::cout << tpX << "" << tpY << std::endl;

    //tupe创建
    std::tuple<int, int> tp1(11, 22);
    auto tp2 = std::tuple_cat(tp1, std::make_tuple("tuple"));
    print(tp2);

    {
        std::shared_ptr<A> ap(new A); // 构造一个A 和 智能指针ap，ap的引用计数1
        std::shared_ptr<B> bp(new B); // 构造一个B 和 智能指针bp，bp的引用计数1
        ap->bptr = bp; // 由于bptr是share_ptr,所以bp 的引用计数+1，那么bp的引用计数就是2
        bp->aptr = ap; // 由于aptr是weak_ptr,所以ap 的引用计数不加1，那么ap的引用计数还是1
    }
    // 此时ap 和 bp 的引用计数分别减去1，ap引用计数就是0，bp引用计数就是1,
    // 接着A对象析构，那么ap->bptr 就不存在了，那么 bp的引用就是再减去1，变为0,
    // 接着B对象析构

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
