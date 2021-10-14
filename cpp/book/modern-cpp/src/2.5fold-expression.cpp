// 折叠表达式
// 参考文章:
// 《C++17：folder expression（折叠表达式）》　https://www.jianshu.com/p/8df794addfed
// 《C++17尝鲜：fold expression（折叠表达式）》　https://blog.csdn.net/zwvista/article/details/53981696

#include <iostream>
template<typename ... T>
auto sum(T ... t) {
    return (t + ...);
}
int main() {
    std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}