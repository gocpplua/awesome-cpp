#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4};
    // C++17 -- if statement with initializer, we can now create the variable inside the if statement
    // if (init; condition)
    if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) *itr = 4; 
    
    for (auto element : vec)
        std::cout << element << std::endl; // read only
    for (auto &element : vec) {
        element += 1;                      // writeable
    }
    for (auto element : vec)
        std::cout << element << std::endl; // read only
}