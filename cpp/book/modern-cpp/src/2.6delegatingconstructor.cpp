//委托构造
#include <iostream>
#include <string>
using namespace std;
class class_a {
public:
    class_a() {}
    // member initialization here, no delegate
    class_a(string str) : m_string{ str } {}

    //can’t do member initialization here
    // error C3511: a call to a delegating constructor shall be the only member-initializer
    // class_a(string str, double dbl) : class_a(str) , m_double{ dbl } {}

    // only member assignment
    class_a(string str, double dbl) : class_a(str) { m_double = dbl; }

    class_a(string str, double dbl, int a):m_string(str), m_double(dbl){}
    double m_double{ 1.0 };
    string m_string;
};

int main(){
  class_a a("str", 1);
  class_a a1("str", 1, 2);
}