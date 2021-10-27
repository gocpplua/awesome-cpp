#include <iostream>
#include<vector>
#include<array>
#include<algorithm> // std::sort
#include <functional> // function
#include <forward_list>
using namespace std;

int main(){
  // vector
  std::vector<int> v;
  std::cout << "size:" << v.size() << std::endl;         // 输出 0
  std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0

  // 如下可看出 std::vector 的存储是自动管理的，按需自动扩张
  // 但是如果空间不足，需要重新分配更多内存，而重分配内存通常是性能上有开销的操作
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  std::cout << "size:" << v.size() << std::endl;         // 输出 3
  std::cout << "capacity:" << v.capacity() << std::endl; // 输出 4

  // 这里的自动扩张逻辑与 Golang 的 slice 很像
  v.push_back(4);
  v.push_back(5);
  std::cout << "size:" << v.size() << std::endl;         // 输出 5
  std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8

  // 如下可看出容器虽然清空了元素，但是被清空元素的内存并没有归还
  v.clear();                                             
  std::cout << "size:" << v.size() << std::endl;         // 输出 0
  std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8

  // 额外内存可通过 shrink_to_fit() 调用返回给系统
  v.shrink_to_fit();
  std::cout << "size:" << v.size() << std::endl;         // 输出 0
  std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0


  // array
  std::array<int, 4> arr = {1, 2, 3, 4};

  arr.empty(); // 检查容器是否为空
  arr.size();  // 返回容纳的元素数

  // 迭代器支持
  for (auto &i : arr)
  {
      cout << i << " ";
  }
  cout << endl;
  // 用 lambda 表达式排序
  std::sort(arr.begin(), arr.end(), [](int a, int b) {
      return b < a;
  });
  // 迭代器支持
  for (auto &i : arr)
  {
      cout << i << " ";
  }
  cout << endl;
  // 数组大小参数必须是常量表达式
  constexpr int len = 4;
  std::array<int, len> arr1 = {1, 2, 3, 4};

  // 非法,不同于 C 风格数组，std::array 不会自动退化成 T*
  // int *arr_p = arr1;


  std::function<void(int* p, int len)> foo = [](int* p, int len){
    for(int i = 0; i< len; i++){
      cout << p[i] << " ";
    }
    cout << endl;
    return;
  };
  // C 风格接口传参
  // foo(arr, arr.size()); // 非法, 无法隐式转换
  foo(&arr[0], arr.size());
  foo(arr.data(), arr.size());

  // std::forward_list
  forward_list<int> fl = {1, 2, 3, 4, 5};

  for (const auto &elem : fl)
  {
      cout << elem;
  }

  return 0;
}