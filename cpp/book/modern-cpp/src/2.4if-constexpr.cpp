//  C++11 引入了 constexpr 关键字，它将表达式或函数编译为常量结果
// 把这一特性引入到条件判断中去，让代码在编译时就完成分支判断，能让程序效率更高
#include <iostream>
#include <chrono>

// 下面代码在编译期表现为:
/**
 * 
int print_type_info(const int& t) {
    return t + 1;
}
double print_type_info(const double& t) {
    return t + 0.001;
}
 */
template<typename T>
auto print_type_info(const T& t) {
    if constexpr (std::is_integral<T>::value) {
        return t + 1.0;
    } else {
        return t + 0.001;
    }
}

template<typename T>
decltype(auto) print_type_info1(const T& t) {  //不加 decltype 会编译失败
    if (std::is_integral<T>::value) {
        return t + 1.0;
    } else {
        return t + 0.001;
    }
}

int main() {
  auto beforeTime = std::chrono::steady_clock::now();
  for(int i = 0; i < 100000000; i++){
    print_type_info(5);
    print_type_info(3.14);
  }
  
  auto afterTime = std::chrono::steady_clock::now();
  double duration_microsecond = std::chrono::duration<double, std::micro>(afterTime - beforeTime).count();
	std::cout << duration_microsecond << "微秒" << std::endl;

  auto beforeTime1 = std::chrono::steady_clock::now();
  for(int i = 0; i < 100000000; i++) {
    print_type_info1(5);
    print_type_info1(3.14);
  }
  auto afterTime1 = std::chrono::steady_clock::now();
  double duration_microsecond1 = std::chrono::duration<double, std::micro>(afterTime1 - beforeTime1).count();
	std::cout << duration_microsecond1 << "微秒" << std::endl;
}