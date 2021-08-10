#include <iostream>
#include <map>
#include <unordered_map>

int main(){
  std::map<int, int> tMap;
  std::cout << tMap.size() << " " << std::endl;
  
  std::cout << __cplusplus << std::endl;

  std::unordered_map<int, int> m;
  m.insert({1,1});
  std::cout << m.size() << " " << std::endl;
}