// function.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

// 是一个函数指针
void func(void)
{
    std::cout << "void func（void）" << std::endl;
}

// 是一个具有operator()成员函数的类对象(仿函数)
struct Foo
{
    void operator() (void)
    {
        std::cout << "Foo void operator() (void)" << std::endl;
    }
};

// 是一个可被转换为函数指针的类对象
struct Bar
{
    using fr_t = void(*)(void); //Bar的成员函数:void(*)(void)

    static void func(void)
    {
        std::cout << "Bar static void func(void)" << std::endl;
    }

    operator fr_t(void)
    {
        return func;
    }
};
// 是一个类成员(函数)指针
struct A
{
    int a_;
    void mem_func(void)
    {
        std::cout << "A  void mem_func(void)" << std::endl;
    }
};

int main1()
{
    //函数指针
    void(*func_ptr)(void) = &func;
    void(*func_ptr1)(void) = func;
    func_ptr();
    func_ptr1();

    Foo foo;
    foo();

    Bar bar;
    bar();

    //这里的这个&符号是比较重要的：不加&，编译器会认为是在这里调用成员函数，所以需要给出参数列表，否则会报错；
    //加了&，才认为是要获取函数指针。这是C++专门做了区别对待。
    void (A::*mem_func_ptr)(void) = &A::mem_func;
    int A::*mem_obj_ptr = &A::a_;

    /* 调用方法也很简单，针对调用的对象是对象还是指针，分别用.*和->*进行调用，格式为：
    (类对象.*指针名)(参数列表);
    (类指针->*指针名)(参数列表);
    注意：这里的前面一对括号是很重要的，因为()的优先级高于成员操作符指针的优先级。 */
    A aa;
    (aa.*mem_func_ptr)();
    A *bb = new A();
    (bb->*mem_func_ptr)();
    delete bb;

    (aa.*mem_obj_ptr) = 123;
    std::cout << aa.*mem_obj_ptr << std::endl;
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
