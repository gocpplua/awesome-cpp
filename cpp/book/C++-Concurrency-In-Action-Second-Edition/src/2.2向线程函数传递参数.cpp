// // clang++ book/C++-Concurrency-In-Action-Second-Edition/src/2.1.1启动线程.cpp -pthread
#include <iostream>
#include <thread>
#include <chrono>

using widget_id = int;
class widget_data{
  public:
    int a;
    int b;
  void update_data_for_widget(int b)// 1
  {
    a = b;
  }
};

void update_data_for_widget(widget_id w,widget_data& data)// 1
{
  data.a = 999;
}

void oops_again(widget_id w)
{
  widget_data data;
  // 方式1
  std::thread t(update_data_for_widget,w,std::ref(data));// 2  不加std::ref 无法编译通过
  std::cout << data.a << std::endl << std::flush;
  t.join();
  std::cout << data.a << std::endl << std::flush;

  // 方式2
  std::thread t1(&widget_data::update_data_for_widget, &data, 888);
  std::cout << data.a << std::endl << std::flush;
  t1.join();
  std::cout << data.a << std::endl << std::flush;
}

int main(){
  oops_again(1);
  return 0;
}