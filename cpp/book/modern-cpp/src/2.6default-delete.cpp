// C++11: The Rule of the Big Five: https://www.feabhas.com/sites/default/files/2016-06/Rule%20of%20the%20Big%20Five.pdf
// Rule of three (C++ programming): https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)
// The rule of three/five/zero: https://en.cppreference.com/w/cpp/language/rule_of_three
// Move constructors: https://en.cppreference.com/w/cpp/language/move_constructor
#include <iostream>
using namespace std;

class Magic {
    public:
    Magic() = default; // 显式声明使用编译器生成的构造
    Magic& operator=(const Magic&) = default; // 显式声明拒绝编译器生成构造 copy assignment
    Magic& operator=(const Magic&&); // A move constructor of class T is a non-template constructor whose first parameter is T&&, const T&&, volatile T&&, or const volatile T&&, and either there are no other parameters, or the rest of the parameters all have default values.
    Magic(const Magic&) = delete; // copy constructor
    Magic(const Magic&&);

    Magic(int magic_number);
};


int main(){
  return 0;
}