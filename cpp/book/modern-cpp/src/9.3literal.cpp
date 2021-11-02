// 字面量
#include <iostream>
#include <string>

// 字符串字面量自定义必须设置如下的参数列表
// C++11 引进了自定义字面量的能力，通过重载双引号后缀运算符实现
/*
自定义字面量支持四种字面量：
整型字面量：重载时必须使用 unsigned long long、const char *、模板字面量算符参数，在上面的代码中使用的是前者；
浮点型字面量：重载时必须使用 long double、const char *、模板字面量算符；
字符串字面量：必须使用 (const char *, size_t) 形式的参数表；
字符字面量：参数只能是 char, wchar_t, char16_t, char32_t 这几种类型。
*/
std::string operator"" _wow1(const char *wow1, size_t len) {
    return std::string(wow1)+"woooooooooow, amazing";
}

std::string operator"" _wow2 (unsigned long long i) {
    return std::to_string(i)+"woooooooooow, amazing";
}

int main() {
    std::string str = R"(C:\File\To\Path)";
    std::cout << str << std::endl;

    auto str1 = "abc"_wow1;
    auto num = 1_wow2;
    std::cout << str1 << std::endl;
    std::cout << num << std::endl;
    return 0;
    return 0;
}