#include <initializer_list>
#include <vector>
#include <iostream>

class MagicFoo {
public:
    std::vector<int> vec;
    MagicFoo(std::initializer_list<int> list) {
        // 从 C++11 起, 使用 auto 关键字进行类型推导
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
};

// auto 能用于函数传参
int add(auto x, auto y) {
    return x+y;
}

int main() {
  MagicFoo magicFoo = {1, 2, 3, 4, 5};
  std::cout << "magicFoo: ";
  for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
      std::cout << *it << ", ";
  }
    
  std::cout << std::endl;

  auto i = 5; // 被推导为 int
  auto j = 6; // 被推导为 int
  std::cout << add(i, j) << std::endl;

  
  
  int arr[5] = {1};
  decltype(arr) auto_arr1[5] = {1}; // auto 不能用于推到数组类型
  // auto auto_arr2[10] = {arr}; // auto 不能用于推到数组类型。 因为{arr}纯粹是一个句法结构。 它不是一个表达式，也没有类型。 因此， auto 不能从中推断出它的类型。

  return 0;
}