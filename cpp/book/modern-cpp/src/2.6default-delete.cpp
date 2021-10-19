// C++11: The Rule of the Big Five: https://www.feabhas.com/sites/default/files/2016-06/Rule%20of%20the%20Big%20Five.pdf
// Rule of three (C++ programming): https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)
// The rule of three/five/zero: https://en.cppreference.com/w/cpp/language/rule_of_three
#include <iostream>
using namespace std;

class Magic {
    public:
    Magic() = default; // 显式声明使用编译器生成的构造
    Magic& operator=(const Magic&) = delete; // 显式声明拒绝编译器生成构造 copy assignment
    Magic(int magic_number);
};


int main(){
  return 0;
}