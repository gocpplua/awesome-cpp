// 继承构造函数: 解决父类有多个构造函数时，子类需要多次调用
// 参考文章: https://www.runoob.com/w3cnote/cpp11-inheritance-constructor.html
#include <iostream>
struct A
{
  A(int i) {}
  A(double d,int i){}
  int m_i = 2;
  double m_d = 3.3;
};
struct B:A
{
  B(int i):A(i){}
  B(double d,int i):A(d,i){}
};

struct C:A{
  using A::A;
};

int main(){
  B b1(1);
  B b2(1.0, 1);
  std::cout << b1.m_d << " " << b1.m_i << std::endl;
  C c1(1);
  C c2(1.0, 1);
  std::cout << c1.m_d << " " << c1.m_i << std::endl;
  return 0;
}