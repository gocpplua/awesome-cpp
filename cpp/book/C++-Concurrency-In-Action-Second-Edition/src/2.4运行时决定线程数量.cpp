#include <iostream>
#include <thread>


int main(){
  unsigned long const hardware_threads=
      std::thread::hardware_concurrency();
      std::cout << hardware_threads << std::endl;
  return 0;
}