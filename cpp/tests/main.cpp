#include <iostream>
#include "yaml-cpp/yaml.h"
int main(int, char**) {
    YAML::Node test = YAML::LoadFile("../../test_yaml/file.yaml");
    try
    {
        std::cout << test.IsNull() << std::endl;
        std::cout << test.IsMap() << std::endl;
        // 不能使用 test["http_server"];
        for(YAML::const_iterator it = test.begin(); it != test.end(); it++){
            std::cout << it->first.as<std::string>() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return 0;    
}




