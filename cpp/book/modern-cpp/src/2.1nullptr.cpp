#include <iostream>
#include <type_traits>

void foo(char*){
  std::cout << "foo(char*) is called" << std::endl;
}
void foo(int){
  std::cout << "foo(int) is called" << std::endl;
}
void foo(long){
  std::cout << "foo(long) is called" << std::endl;
}

int main(){
  if(std::is_same<decltype(NULL), decltype(0)>::value){
    std::cout << "NULL == 0" << std::endl;
  }

  if(std::is_same<decltype(NULL), decltype((long)0)>::value){
    std::cout << "NULL == ((long)0" << std::endl;
  }

  if(std::is_same<decltype(NULL), decltype((void*)0)>::value){
    std::cout << "NULL == (void*)0" << std::endl;
  }

  if(std::is_same<decltype(NULL), decltype(nullptr)>::value){
    std::cout << "NULL == nullptr" << std::endl;
  }

  foo(0);
  foo(NULL); // 触发告警:warning: passing NULL to non-pointer argument 1 of ‘void foo(long int)’ [-Wconversion-null]
  foo(nullptr);
}

// output:
/*
NULL == ((long)0
foo(int) is called
foo(long) is called
foo(char*) is called
*/