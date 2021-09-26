#include <iostream>
#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}
constexpr int len_foo_constexpr() {
    return 5;
}

// 从 C++14 开始，constexpr 函数可以在内部使用局部变量、循环和分支等简单语句
// C++14及以上写法
//g++ -o ./out/a 2.1constexpr.cpp  --std=c++14
/*
constexpr int fibonacci(const int n) {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}*/

// C++11 写法
// g++ -o ./out/a 2.1constexpr.cpp  --std=c++11
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    char arr_1[10];                      // 合法
    char arr_2[LEN];                     // 合法

    int len = 10;
    // char arr_3[len];                  // 非法

    const int len_2 = len + 1;
    constexpr int len_2_constexpr = 1 + 2 + 3;
    // char arr_4[len_2];                // 非法:因为 C++ 标准中数组的长度必须是一个常量表达式，而对于 len_2 而言，这是一个 const 常数，而不是一个常量表达式，
    char arr_4[len_2_constexpr];         // 合法

    // char arr_5[len_foo()+5];          // 非法: gcc version 5.4.0 20160609 编译是成功的，因为，现在大部分编译器其实都带有自身编译优化，很多非法行为在编译器优化的加持下会变得合法，若需重现编译报错的现象需要使用老版本的编译器。
    char arr_6[len_foo_constexpr() + 1]; // 合法

    std::cout << fibonacci(10) << std::endl;
    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    std::cout << fibonacci(10) << std::endl;
    return 0;
}