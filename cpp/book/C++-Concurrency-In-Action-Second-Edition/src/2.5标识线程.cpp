//  clang++ book/C++-Concurrency-In-Action-Second-Edition/src/2.5标识线程.cpp  -pthread
#include <iostream>
#include <thread>

std::thread::id master_thread;
void some_core_part_of_algorithm()
{
  if(std::this_thread::get_id()==master_thread)
  {
    std::cout << "main" << std::endl;
  }
  std::cout << __FUNCTION__ << std::endl;
}

int main(){
  master_thread = std::this_thread::get_id();
  some_core_part_of_algorithm();
  std::thread t(some_core_part_of_algorithm);
  t.join();
  return 0;
}