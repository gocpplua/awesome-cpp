cmake_minimum_required(VERSION 3.0.0) # CMake 最低版本
project(UnitTest VERSION 0.1.0) # 设置工程名称 和版本


include(CTest)
enable_testing()
set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(UnitTest main.cpp) 
add_executable(test_demo test_demo.cpp)

set(EXECUTABLE_OUTPUT_PATH ./out) # cmake可执行文件的存放路径

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
