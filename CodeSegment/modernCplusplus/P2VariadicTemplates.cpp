#include "pch.h"
#include<iostream>
using namespace std;
// 参数数量不定的模板

void print()
{
    //为了处理边界条件，也就是参数为0的时候
    cout << "print" << endl;
}

//为了处理参数>=1的时候
template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
    cout << firstArg << endl;
    print(args...);
}

int main()
{
    print(1, "22", 333);
    return 0;
}