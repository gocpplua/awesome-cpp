#include<iostream>
#include <memory>  // std::make_unique
#include <utility> // std::move
using namespace std;

void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << " value:" << value <<std::endl;
    // 这时, stored_value == 1, 而 value == 100.
    // 因为 copy_value 在创建时就保存了一份 value 的拷贝
}

void lambda_reference_capture1() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << " value:" << value <<std::endl;
    // 这时, stored_value == 100, value == 100.
    // 因为 copy_value 保存的是引用
}


void lambda_expression_capture() {
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };
    std::cout << add(3,4) << std::endl;
}

// auto 关键字不能够用在参数表里，这是因为这样的写法会与模板的功能产生冲突。 
// 但是 Lambda 表达式并不是普通函数，所以 Lambda 表达式并不能够模板化。 这就为我们造成了一定程度上的麻烦：参数表不能够泛化，必须明确参数表类型。
// 这种麻烦只存在于 C++11 中，从 C++14 开始， Lambda 函数的形式参数可以使用 auto 关键字来产生意义上的泛型：
auto add = [](auto x, auto y) {
    return x+y;
};

int main(){
  lambda_value_capture();
  lambda_reference_capture1();
  lambda_expression_capture();
  std::cout << add(1, 2) << endl;
  return 0;
}