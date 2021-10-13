
#include <iostream>
#include <vector>
#include <map>
#include <initializer_list>

//　-------  变长参数模板类 --------------
template<typename... Ts>
class Magic{

public:
template<typename... Args> 
  void printfcustom(const std::string &str, Args... args){
    std::cout << sizeof...(args) << std::endl;
  }

  void printfcustom1(const std::string &str, Ts... args){
    std::cout << sizeof...(args) << std::endl;
  }
};

// 模板类 Magic 的对象定义
class Magic<int,
            std::vector<int>,
            std::map<std::string,
            std::vector<int>>> darkMagic;

class Magic<int, int> darkMagic1;

//　-------  变长参数解包 --------------
// 方法一: 递归模板函数
template<typename T0>
void printf1(T0 value) {
    std::cout << "1:" << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
    std::cout << "2:" << value << std::endl;
    printf1(args...);
}

// 方法二: 变参模板展开
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << "printf2:" << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}

// todo
// 方法三：初始化列表展开 https://www.zhihu.com/question/443285720
/*
// 下面的写法会出现问题：error: parameter packs not expanded with ‘...’:
template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
    std::cout << value << std::endl;
    (void) std::initializer_list<T>{([&args] {
        std::cout << args << std::endl;
    }(), value)...};
}
//*/

// 方法四：　折叠表达式　https://www.zhihu.com/question/443285720/answer/1719851060
// 在元编程场景下初始化列表是能够保证模板可变参数包从左往右执行
template <typename T, typename... Args>
void printf4(T value, Args&&... args) {
  std::cout << value << std::endl;
  (std::cout << ... << args) << '\n';
}

// 方法五、　C++17 中有个 Pack fold expression 的语法
template <typename T, typename... Ts>
void printf5(T value, Ts... args) {
  std::cout << value << std::endl;
  ((std::cout << args << std::endl), ...);
}

int main(){
  darkMagic.printfcustom("d", 1, 2); // 参数随意，因为　printfcustom　是变长模板函数，　使用的模板参数不是模板类Magic的
  darkMagic1.printfcustom1("d", 5, 6); // 参数需要和　darkMagic1　一致，因为　printfcustom１　使用的模板参数是　模板类　Magic　的

  printf1(1,2,3,4);
  printf2(1,2,3,4);
  //printf3(1, 2, 3, 4);
  printf4(1,2,3, 4);
  printf5(1,2,3, 4);
  return 0;
}