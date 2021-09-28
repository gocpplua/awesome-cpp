#include <initializer_list>
#include <vector>
#include <iostream>
class MagicFoo{
  public:
    MagicFoo(std::initializer_list<int> list){
      for (auto &&data : list)
      {
        std::cout << data << std::endl;
      }
    }
};

int main(){
  MagicFoo m = {1, 2};
  MagicFoo m1 {1, 2};
  return 0;
}