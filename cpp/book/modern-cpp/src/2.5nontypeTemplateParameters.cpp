// 非类型模板参数 Nontype Template Parameters
#include <iostream>
template <typename T, auto BufSize> // c++ 11 只能是: template <typename T, int BufSize>, C++17 可以使用auto
class buffer_t {
public:
    T& alloc();
    void free(T& item);
    void print(){
      std::cout << sizeof(data) << " " << sizeof(data) / sizeof(T) << std::endl;
    }
private:
    T data[BufSize];
};

buffer_t<int, 100> buf; // 100 作为模板参数

int main(){
  buf.print();
  return 0;
}