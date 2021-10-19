// clang++ --std=c++20 book/modern-cpp/src/2.6override-final.cpp 
#include <iostream>
#include <typeinfo>
using namespace std;

struct A final {

};
/* error: base 'A' is marked 'final'
struct BA : A{

};
*/


struct Base {
    virtual void foo(){
      cout << __PRETTY_FUNCTION__ << endl;
      cout << typeid(*this).name() << endl;
    }
    virtual void f() final{

    }
};
struct SubClass: Base {
    virtual void foo() override{
      cout << __PRETTY_FUNCTION__ << endl;
      cout << typeid(*this).name() << endl;
    }

    /*  error: 'foo1' marked 'override' but does not override any member functions
    virtual void foo1() override{
      cout << __PRETTY_FUNCTION__ << endl;
    }
    //*/

    /* error: declaration of 'f' overrides a 'final' function
    void f(){

    }
    */
};

int main(){
  SubClass sub;
  sub.foo();

  Base b;
  b.foo();

  Base *bb = new SubClass();
  bb->foo();
  return 0;
}