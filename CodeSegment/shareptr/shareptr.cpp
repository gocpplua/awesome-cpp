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
    MyClass(int nUserID) { a = nUserID; };
    ~MyClass();
    int a = 0;
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

void AddUser(int userid, const std::shared_ptr<MyClass> &user)
{
    std::lock_guard<std::mutex> users_lock(rooms_mutex_);
    rooms_[userid] = user;
}

int main()
{
    std::shared_ptr<MyClass> class1 = GetUser(1);
    std::shared_ptr<MyClass> class2 = GetUser(2);
    std::unordered_map<int, std::shared_ptr<MyClass>> rooms1 = rooms_; // map是进行深拷贝的

    for (int i = 0; i < 1; i++)
    {
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            std::unique_ptr<char[]> data(new char[4096*1024]); // 这里不会内存泄漏，unique_ptr 除了独占性这个特点，还可以指向一个数组
            int j = 0;
        }
        int k = 0;
    }

    // 测试erase以后，对智能指针的影响，结论是：erase之后，只是对智能指针的引用计数减去1
    {
        std::weak_ptr<MyClass> weakClass11;
        {
            int nUserID = 11;
            AddUser(nUserID, std::make_shared<MyClass>(nUserID));
            std::shared_ptr<MyClass> class11 = GetUser(nUserID);
            weakClass11 = class11;
            std::cout << "智能指针引用数1:" << weakClass11.use_count() << std::endl;
            rooms_.erase(nUserID);
            std::cout << "智能指针引用数2:" << weakClass11.use_count() << std::endl;
            std::lock_guard<std::mutex> users_lock(rooms_mutex_);
            class11->a = 1;
        }
        std::cout << "智能指针引用数3:" << weakClass11.use_count() << std::endl;
        if (weakClass11.expired())
        {
            std::cout << "智能指针已经被释放" << std::endl;
        }
        else
        {
            std::cout << "智能指针引用数4:" << weakClass11.use_count() <<std::endl;
        }
    }


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
