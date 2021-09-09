cmake_minimum_required (VERSION 2.8)

project (cqevpptest C CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
         -g\
         -fPIC\
         -Wall\
         -Wno-unused-parameter\
         -Wno-unused-function\
         -Wunused-variable\
         -Wunused-value\
         -Wshadow\
         -Wcast-qual\
         -Wcast-align\
         -Wwrite-strings\
         -Wsign-compare\
         -Winvalid-pch\
         -fms-extensions\
         -Wfloat-equal\
         -Wextra\
         -std=c++11"
    )
   

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

    
# include_directories (${PROJECT_SOURCE_DIR})

# SET(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g -ggdb -D_DEBUG -DGOOGLE_STRIP_LOG=0")
# SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -ggdb -DNDEBUG -DGOOGLE_STRIP_LOG=1")

add_executable(pingpong pingpong.cc)
target_link_libraries(pingpong evpp)


