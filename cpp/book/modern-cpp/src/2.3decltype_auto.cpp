// decltype(auto) 主要用于对转发函数或封装的返回类型进行推导，它使我们无需显式的指定 decltype 的参数表达式
#include <iostream>
#include <string>

std::string  lookup1(){
  return "lookup1";
}
std::string& lookup2(){

  //std::string tmp = "lookup2"; // warning: reference to local variable ‘tmp’ returned [-Wreturn-local-addr]
  //return tmp;

  std::string* tmp = new std::string("lookup2"); // 内存泄露
  return *tmp;
}

std::string look_up_a_string_1() {
    return lookup1();
}
std::string& look_up_a_string_2() {
    return lookup2();
}

decltype(auto) modern_look_up_a_string_1() {
    return lookup1();
}
decltype(auto) modern_look_up_a_string_2() {
    return lookup2();
}

int main(){
  std::cout << modern_look_up_a_string_1() << std::endl;
  std::cout << modern_look_up_a_string_2() << std::endl;
}
