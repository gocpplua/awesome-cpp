// clang++ book/modern-cpp/src/7.5atomic.cpp -pthread -latomic
// 不适用 -latomic 编译出错:  undefined reference to `__atomic_is_lock_free'
#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include <sstream> // stringstream
// example 1
/*
struct A {
    float x;
    int y;
    long long z;
};

std::atomic<int> count = {0};

int main() {
    std::thread t1([](){
        count.fetch_add(1);
    });
    std::thread t2([](){
        count++;        // 等价于 fetch_add
        count += 1;     // 等价于 fetch_add
    });
    t1.join();
    t2.join();
    std::cout << count << " " << count.is_lock_free() <<std::endl;

    std::atomic<A> a;
    std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    return 0;
}
//*/

///* ————————————————
//版权声明：本文为CSDN博主「盐焗咸鱼」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// C++并发编程（六）：内存顺序
//原文链接：https://blog.csdn.net/qq_33215865/article/details/88089927
std::atomic<bool> x,y;
std::atomic<int> z;
 
void write_x_then_y()
{
  x.store(true,std::memory_order_relaxed);  
  y.store(true,std::memory_order_relaxed);  
}
void read_y_then_x()
{
  while(!y.load(std::memory_order_relaxed));  
  if(x.load(std::memory_order_relaxed))  
    ++z;
}
int main()
{
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(2,&cpuset);
  std::stringstream ss;
  ss << std::this_thread::get_id();
  uint64_t id = std::stoull(ss.str());

  int rc =pthread_setaffinity_np(id, sizeof(cpu_set_t), &cpuset);
  if (rc != 0) {
    std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
  }  

  for(int i = 0; i < 10000000; i++){
    x=false;
    y=false;
    z=0;
    std::vector<std::thread>threads(2);
    threads[0] = std::thread(write_x_then_y);
    threads[1] = std::thread(read_y_then_x);
    for(int i = 0; i < 2; ++i){
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(i,&cpuset);
      // C++11线程，亲合与超线程（绑定CPU方法）: https://blog.csdn.net/wuhui_gdnt/article/details/51280906
      int rc =pthread_setaffinity_np(threads[i].native_handle(),sizeof(cpu_set_t), &cpuset);
      if (rc != 0) {
        std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
      }  
    }
    for (auto& t : threads) {
      t.join();
    }
    if(z.load()==0)
      std::cout << " 0" << std::endl; 
  }
}
//*/
