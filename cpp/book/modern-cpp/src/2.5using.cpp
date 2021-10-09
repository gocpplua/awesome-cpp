// using 模板别名
#include <vector>
#include <string>

template<typename T, typename U>
class MagicType {
public:
    T dark;
    U magic;
};


template<typename T>
// typedef MagicType<std::vector<T>, std::string> FakeDarkMagic; // typedef old new // error：模板是用来产生类型的。 typedef 可以为类型定义一个新的名称，但是却没有办法为模板定义一个新的名称
using FakeDarkMagic = MagicType<std::vector<T>, std::string>;
int main() {
    FakeDarkMagic<bool> you;
}