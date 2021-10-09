// 尾返回类型推导
#include <iostream>
using namespace std;

template <typename T, typename U>
auto add(T x, U y){
  return x + y;
}

int main(){
  auto ret = add<int, int>(1 ,2); 
  std::cout << ret << std::endl;
  return ret;
}