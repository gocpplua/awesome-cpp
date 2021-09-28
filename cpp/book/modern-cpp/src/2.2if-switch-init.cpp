/*
在C++17中，类似于 for 语句，在 if 和 switch 语句的判断条件之前也能加上初始化语句，语法形式如下：
if (初始化语句; 条件) 语句 else 语句
switch (初始化语句; 条件) 语句
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4};
    // 将临时变量放到 if 语句内
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) {
    *itr = 4;
  }

  for (auto &&i : vec) {
    std::cout << i << std::endl;
  }
  
}

// g++ -o ./out/a 2.2if-switch-init.cpp  --std=c++17
// g++/gcc 升级参考: https://segmentfault.com/a/1190000040739905