cmake_minimum_required(VERSION 3.0.0) # CMake 最低版本
project(UnitTest VERSION 0.1.0) # 设置工程名称 和版本


include(CTest)
enable_testing()
set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -std=c++11 -rdynamic -Wall -Wextra -Wpedantic")

set(CMAKE_BUILD_TYPE "Release")

find_package(yaml-cpp REQUIRED)
MESSAGE(STATUS "yaml_INCLUDE_DIR: ${YAML_CPP_INCLUDE_DIR}")
MESSAGE(STATUS "yaml_libraries: ${YAML_CPP_LIBRARIES}")

include_directories(${PROJECT_SOURCE_DIR}/)

add_executable(main main.cpp) 
target_link_libraries(main yaml-cpp)

add_executable(test_demo test_demo.cpp)

add_executable(test_yaml ./test_yaml/test_yaml.cpp)
target_link_libraries(test_yaml yaml-cpp)

set(EXECUTABLE_OUTPUT_PATH ./out) # cmake可执行文件的存放路径

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
