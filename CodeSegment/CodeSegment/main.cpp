#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>

std::string syscdsyscd() { return "Foo"; }
std::string foo() { return "Foo"; }
std::string bar() { return "Bar"; }

int main()
{
    std::unordered_map<std::string, std::string(*)()> m;
    // Map the functions to the names
    m["foo"] = &foo;
    m["bar"] = &bar;
    // Display all of the mapped functions
    std::unordered_map<std::string, std::string(*)()>::const_iterator it = m.begin();
    std::unordered_map<std::string, std::string(*)()>::const_iterator end = m.end();
    while (it != end) {
        std::string first = it->first;
        std::string second = (it->second)();
        std::cout << second << std::endl;
        ++it;
    }
}


int mainman() {

    std::string strOper;
    std::cout << ">>>";
    while (true)
    {
        //std::getline(std::cin, strOper);
    }

    return 0;
}








