#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> f1(){
  return std::make_tuple(1, 1.1, "111");
}

decltype(std::make_tuple(1, 1.1, "111")) f2(){
  return std::make_tuple(1, 1.1, "111");
}

int main(){
  {
    auto [x, y, z] = f1();
    std::cout << x << ", " << y << "," << z << std::endl;
  }
  {
    auto [x, y, z] = f2();
    std::cout << x << ", " << y << "," << z << std::endl;
  }
  return 0;
}

// g++ -o ./out/a 2.2tuple.cpp --std=c++17    //使用 C++11/C++14会有告警: warning: decomposition declaration only available with -std=c++1z or -std=gnu++1z