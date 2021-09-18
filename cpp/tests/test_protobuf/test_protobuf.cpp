// 依赖镜像； docker push gocpplua/ubuntu_gocpplua:v0.0.3
// g++ -std=c++11  ./test_protobuf.cpp  ./proto/SearchRequest.pb.cc -o test_protobuf -lprotobuf
#include<iostream>
#include "./proto/SearchRequest.pb.h"
using namespace std;

int main() {
    SearchRequest one;
    one.set_page_number(1);
    std::cout << one.page_number() << std::endl;
    return 0;
}