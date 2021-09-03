// g++ -std=c++11 demo.cpp -o ../out/demo
#include <iostream>
#include <map>
#include <unordered_map>
#include "./util/instance.h"
#include "../3thParty/icecream-cpp/icecream.hpp"
class test{
  public:
    void print(){
    std::cout << "print" << std::endl;
  }
};

class test1{
  public:
    void print(){
    std::cout << "print" << std::endl;
  }
};
int main(){
  std::map<int, int> tMap;
  std::cout << tMap.size() << " " << std::endl;
  
  std::cout << __cplusplus << std::endl;

  std::unordered_map<int, int> m;
  m.insert({1,1});
  std::cout << m.size() << " " << std::endl;

  std::cout << Singleton<test>::getInstance() << std::endl;
  std::cout << Singleton<test>::getInstance() << std::endl;
  std::cout << Singleton<test1>::getInstance() << std::endl;
  IC();
}
