#define CATCH_CONFIG_MAIN
#include "../../3thParty/catch2/catch.hpp"


#include "yaml-cpp/yaml.h"
YAML::BadConversion::~BadConversion()
{
}

void  YAML::detail::node_data::convert_to_map(const shared_memory_holder& pMemory)
{
}

TEST_CASE("Yaml", "instance"){

    YAML::Node test = YAML::LoadFile("../../test_yaml/file.yaml");
    REQUIRE(test["http_server"]["thread_num"].as<int>() == 2); 
    REQUIRE(test.size()==1);
}

