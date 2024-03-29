#include<iostream>
#include<thread>
#include<mutex>
#include<list>
#include<algorithm>
using namespace std;

std::mutex mtx_;
std::list<int> l_;

void add(int i){
  std::lock_guard<std::mutex>  lock(mtx_); // C++11  等价于下面
  //std::scoped_lock lock(mtx_); // C++17  等价于下面
  // std::lock_guard  lock(mtx_); // C++17中添加了一个新特性，称为模板类参数推导
  l_.emplace_back(i);
}

void findi(int i){
  std::lock_guard lock(mtx_);
  std::find(l_.begin(), l_.end(), i);
}

int main(){
  std::thread t1(add, 1);
  std::thread t2(findi, 1);
  t1.join();
  t2.join();
  std::cout << l_.front() << std::endl;
  return 0;
}