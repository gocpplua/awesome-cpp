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

/* ————————————————
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

/*
// 宽松模型：在此模型下，单个线程内的原子操作都是顺序执行的，不允许指令重排，但不同线程间原子操作的顺序是任意的。类型通过 std::memory_order_relaxed 指定。
int main(){
  std::atomic<int> counter = {0};
  std::vector<std::thread> vt;
  for (int i = 0; i < 100; ++i) {
      vt.emplace_back([&](){
          counter.fetch_add(1, std::memory_order_relaxed);
      });
  }

  for (auto& t : vt) {
      t.join();
  }
  std::cout << "current counter:" << counter << std::endl;
  return 0;
}
//*/

/* 2. 释放/消费模型：在此模型中，我们开始限制进程间的操作顺序，如果某个线程需要修改某个值，但另一个线程会对该值的某次操作产生依赖，即后者依赖前者。
// 具体而言，线程 A 完成了三次对 x 的写操作，线程 B 仅依赖其中第三次 x 的写操作，与 x 的前两次写行为无关，则当 A 主动 x.release() 时候（即使用 std::memory_order_release），
// 选项 std::memory_order_consume 能够确保 B 在调用 x.load() 时候观察到 A 中第三次对 x 的写操作。
int main(){
  // 初始化为 nullptr 防止 consumer 线程从野指针进行读取
  std::atomic<int*> ptr(nullptr);
  int v;
  std::thread producer([&]() {
      int* p = new int(42);
      v = 1024;
      ptr.store(p, std::memory_order_release);
  });
  std::thread consumer([&]() {
      int* p;
      while(!(p = ptr.load(std::memory_order_consume)));

      std::cout << "p: " << *p << std::endl;
      std::cout << "v: " << v << std::endl;
  });
  producer.join();
  consumer.join();
  return 0;
}
//*/