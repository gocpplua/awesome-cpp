#include <iostream>
#include <thread>

void do_something()
{
  std::cout << __FUNCTION__ << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(10));
}


void do_something_in_current_thread()
{
  std::cout << __FUNCTION__ << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(10));
}


int main()
{
  std::thread t1(do_something);            // 1
  std::thread t2=std::move(t1);            // 2
  t1=std::thread(do_something_in_current_thread);    // 3
  std::thread t3;                            // 4
  t3=std::move(t2);                        // 5

  // 6 赋值操作将使程序崩溃 t1已经有了一个关联的线程(执行some_other_function的线程)，所以这里系统直接调用std::terminate()终止程序继续运行。
  // 这样做（不抛出异常，std::terminate()是noexcept函数)是为了保证与std::thread的析构函数的行为一致。
  // 2.1.1节中，需要在线程对象被析构前，显式的等待线程完成，或者分离它；进行赋值时也需要满足这些条件(说明：不能通过赋一个新值给std::thread对象的方式来”丢弃”一个线程)。
  //t1=std::move(t3); // 6 赋值操作将使程序崩溃 

  std::this_thread::sleep_for(std::chrono::seconds(15));

  // joining_thread类的实现  
  return 0;
}
