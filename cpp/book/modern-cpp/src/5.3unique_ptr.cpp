#include <iostream>
#include <memory>

struct Foo {
    Foo() { std::cout << "Foo::Foo" << std::endl; }
    ~Foo() { std::cout << "Foo::~Foo" << std::endl; }
    void foo() { std::cout << "Foo::foo" << std::endl; }
};

void f(const Foo &) {
    std::cout << "f(const Foo&)" << std::endl;
}

int main() {
    


    // 非法 禁止其他智能指针与其共享同一个对象, 看源码就知道禁止拷贝构造 拷贝赋值
    // unique_ptr(const unique_ptr&) = delete;
    //  unique_ptr& operator=(const unique_ptr&) = delete;
    std::unique_ptr<Foo> pointer1(std::make_unique<Foo>());
    // std::unique_ptr<Foo> pointer2 = pointer1; // 禁止拷贝构造
    std::unique_ptr<Foo> pointer2 = std::move(pointer1);

    std::unique_ptr<Foo> p1(std::make_unique<Foo>()); // make_unique 从 C++14 引入
    // p1 不空, 输出
    if (p1) p1->foo();
    {
        std::unique_ptr<Foo> p2(std::move(p1));
        // p2 不空, 输出
        f(*p2);
        // p2 不空, 输出
        if(p2) p2->foo();
        // p1 为空, 无输出
        if(p1) p1->foo();
        p1 = std::move(p2);
        // p2 为空, 无输出
        if(p2) p2->foo();
        std::cout << "p2 被销毁" << std::endl;
    }
    // p1 不空, 输出
    if (p1) p1->foo();
    // Foo 的实例会在离开作用域时被销毁
}