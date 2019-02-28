// shareptr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <mutex>
#include <unordered_map>
class MyClass
{
public:
    MyClass();
    ~MyClass();
};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}
std::mutex rooms_mutex_;
std::unordered_map<int, std::shared_ptr<MyClass>> rooms_;

std::shared_ptr<MyClass> GetUser(int userid)
{
    static int a = userid; // 执行 GetUser(1); GetUser(2);后面，a 还是为1，因为static初始化一次
    static std::shared_ptr<MyClass> null_user = std::make_shared<MyClass>(); //使用static的话，下面main中class1，class2就是同一个对象，因为static初始化一次
    //std::shared_ptr<MyClass> null_user = std::make_shared<MyClass>();

    std::lock_guard<std::mutex> users_lock(rooms_mutex_);
    auto itr = rooms_.find(userid);
    if (itr == rooms_.end()) {
        std::cout << a << std::endl;
        return null_user;
    }
    return itr->second;
}

int main()
{
    std::shared_ptr<MyClass> class1 = GetUser(1);
    std::shared_ptr<MyClass> class2 = GetUser(2);
    std::unordered_map<int, std::shared_ptr<MyClass>> rooms1 = rooms_; // map是进行深拷贝的
    std::cout << "Hello World!\n";
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
