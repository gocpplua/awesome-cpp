// 话说C++中的左值、纯右值、将亡值: https://www.cnblogs.com/zpcdbky/p/5275959.html
#include <iostream>
using namespace std;
// note: 我们不去管big five 内部实现是否正确，只要就是打印日志
class Magic {
    public:
    Magic(){ 
      std::cout << "Magic()" << this << std::endl;
    }// 显式声明使用编译器生成的构造
    Magic& operator=(const Magic& magic){
      std::cout << "Magic() copy assignment" << this << std::endl;
      return *this;
    } // 显式声明拒绝编译器生成构造 copy assignment
    Magic& operator=(const Magic&& magic){
      std::cout << "Magic() move assignment" << this << std::endl;
      return *this;
    } // A move constructor of class T is a non-template constructor whose first parameter is T&&, const T&&, volatile T&&, or const volatile T&&, and either there are no other parameters, or the rest of the parameters all have default values.
    Magic(const Magic& magic){
      std::cout << "Magic() copy constructor" << this << std::endl;
    } // copy constructor
    Magic(const Magic&& magic){
      std::cout << "Magic() move constructor" << this << std::endl;
    }
    ~Magic(){
      std::cout << "~Magic()" << this << std::endl;
    }
};

int main(){
  Magic m;
  Magic m1 = m; // 拷贝构造
  Magic m2 = std::move(m); // 使用移动构造
  m2 = m1; // 拷贝赋值
  m2 = std::move(m1); // 移动赋值

  const int& a = std::move(1); // 合法, 常量左引用允许引用右值
  // int& b = std::move(1); // 不合法，非常量左引用无法引用右值
}