// Strongly-typed enums 强类型枚举
#include <iostream>
using namespace std;

enum valuetype{
  value1 = 1,
  value2 = 2
};

// 不能够被隐式的转换为整数，同时也不能够将其与整数数字进行比较， 更不可能对不同的枚举类型的枚举值进行比较。但相同枚举值之间如果指定的值相同，那么可以进行比较
enum class strongvaluetype {
  strongvalue1 = 1,
  strongvalue2 = 2
};

#include <iostream>
template<typename T>
std::ostream& operator<<(
    typename std::enable_if<std::is_enum<T>::value,
        std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

int main(){
  if (strongvaluetype::strongvalue1 == strongvaluetype::strongvalue2 ){
    cout << "1" << endl;
  }
  cout << strongvaluetype::strongvalue1 << endl;
  //  error: invalid operands to binary expression ('strongvaluetype' and 'int')
  /*
  if (strongvaluetype::strongvalue1 == 1 ){
    cout << "1" << endl;
  }
  */
  return 0;
}