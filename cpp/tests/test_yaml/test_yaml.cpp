#define CATCH_CONFIG_MAIN
#include "../../3thParty/catch2/catch.hpp"


#include "yaml-cpp/yaml.h"

TEST_CASE("Yaml", "instance"){
  try
  {
    YAML::Node test = YAML::LoadFile("../../tests/test_yaml/file.yaml");
    REQUIRE(test.size()==1);
    
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}

