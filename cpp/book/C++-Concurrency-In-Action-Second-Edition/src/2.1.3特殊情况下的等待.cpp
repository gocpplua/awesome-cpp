#include <iostream>
#include <thread>
#include <chrono>


struct func
{
  int& i;
  func(int& i_) : i(i_) {}
  void operator() ()
  {
    for (unsigned j=0 ; j<1000000 ; ++j)
    {
      if (0 == j % 10000)
      {
        std::cout << "i = "<< i << " " << std::endl << std::flush;           //  潜在访问隐患：悬空引用, 我们可以看到 i 输出的值变了
      }
    }
    std::cout << 7 << std::endl << std::flush; 
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
};

// 方法一、 无论有无异常，都会等到线程t结束
void f()
{
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread t(my_func);

  // try/catch块能轻易的捕获轻量级错误，所以这种情况，并非放之四海而皆准。
  try
  {
   std::cout << 3 << std::endl << std::flush; 
   throw 1;
  }
  catch(...)
  {
    t.join();  // 1
    std::cout << 4 << std::endl << std::flush; 
    throw;
  }
  std::cout << 5 << std::endl << std::flush; 
  t.join();  // 2
  std::cout << 6 << std::endl << std::flush; 
}

// 方法二： 使用RAII等待线程完成
class thread_guard
{
  std::thread& t;
public:
  explicit thread_guard(std::thread& t_):
    t(t_)
  {
    std::cout << 8 << std::endl << std::flush; 
  }
  ~thread_guard()
  {
    if(t.joinable()) // 1
    {
      std::cout << 9 << std::endl << std::flush; 
      t.join();      // 2
    }
    std::cout << 10 << std::endl << std::flush; 
  }
  // 拷贝构造函数和拷贝赋值操作被标记为=delete③，是为了不让编译器自动生成它们。
  // 直接对一个对象进行拷贝或赋值是危险的，因为这可能会弄丢已经加入的线程。通过删除声明，任何尝试给thread_guard对象赋值的操作都会引发一个编译错误。
  thread_guard(thread_guard const&)=delete;   // 3
  thread_guard& operator=(thread_guard const&)=delete;
};

void f2()
{
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);
  std::cout << __FUNCTION__ << std::endl << std::flush; 
} 

// 使用detach()会让线程在后台运行，这就意味着主线程不能与之产生直接交互。
// 也就是说，不会等待这个线程结束；如果线程分离，那么就不可能有std::thread对象能引用它，分离线程的确在后台运行，所以分离线程不能被加入。
// 不过C++运行库保证，当线程退出时，相关资源的能够正确回收，后台线程的归属和控制C++运行库都会处理。

int main(){
  struct func; // 定义在清单2.1中
  std::cout << 1 << std::endl << std::flush; 
  //f();
  std::cout << 2 << std::endl << std::flush; 
  f2();
  std::cout <<"end" << std::endl << std::flush; 
}