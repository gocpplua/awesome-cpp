// clang++ book/C++-Concurrency-In-Action-Second-Edition/src/2.1.1启动线程.cpp -pthread
#include <iostream>
#include <thread>
#include <chrono>
class background_task
{
public:
  void operator()() const
  {
    std::cout << __FUNCTION__ << " " << __TIME__ << std::endl; //  在源代码中插入当前编译时间〔注意和当前系统时间区别开来〕
  }
};

struct func
{
  int& i;
  func(int& i_) : i(i_) {}
  void operator() ()
  {
    for (unsigned j=0 ; j<1000000 ; ++j)
    {
      if (0 == j % 100)
      {
        std::cout << "i = "<< i << " " << std::endl << std::flush;           // 1 潜在访问隐患：悬空引用, 我们可以看到 i 输出的值变了
      }
    }
  }
};

//  函数已经返回，线程依旧访问局部变量
void oops()
{
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  std::this_thread::sleep_for(std::chrono::microseconds(2));
  my_thread.detach();          // 2 不等待线程结束
}      

int main(){
  background_task f;
  std::thread my_thread(f);
  my_thread.join(); // 启动了线程，你需要明确是要等待线程结束(加入式——参见2.1.2节)，还是让其自主运行(分离式——参见2.1.3节)。如果std::thread对象销毁之前还没有做出决定，程序就会终止(std::thread的析构函数会调用std::terminate())。因此，即便是有异常存在，也需要确保线程能够正确的加入(joined)或分离(detached)。
  std::this_thread::sleep_for(std::chrono::seconds(1));
  // 避免“最令人头痛的语法解析”：https://www.cnblogs.com/Patt/p/10476911.html
  // std::thread my_thread1(background_task()); // 这里将my_thread1解析成为一个函数，返回值std::thread, 参数是一个函数类型(返回值background_task， 参数为空)
  // my_thread1.join(); // error: member reference base type 'std::thread (background_task (*)())' is not a structure or union
  std::thread my_thread2((background_task()));  // 1
  my_thread2.join();
  std::thread my_thread3{background_task()};    // 2
  my_thread3.join();

  std::cout << "before" << std::endl << std::flush;
  oops();
  std::cout << "after" << std::endl << std::flush;
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  return 0;
}
