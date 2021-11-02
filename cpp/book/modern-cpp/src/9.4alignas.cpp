#include <iostream>
using ::max_align_t;
struct Storage {
    char      a;
    int       b;
    double    c;
    long long d;
};

struct alignas(max_align_t) AlignasStorage { // alignas 来重新修饰某个结构的对齐方式
    char      a;
    int       b;
    double    c;
    long long d;
};

int main() {
    std::cout << alignof(Storage) << std::endl; // alignof 关键字能够获得一个与平台相关的 std::size_t 类型的值，用于查询该平台的对齐方式
    std::cout << alignof(AlignasStorage) << std::endl;
    return 0;
}