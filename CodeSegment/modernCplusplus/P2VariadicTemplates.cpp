#include "pch.h"
#include<iostream>
using namespace std;
// ��������������ģ��

void print()
{
    //Ϊ�˴���߽�������Ҳ���ǲ���Ϊ0��ʱ��
    cout << "print" << endl;
}

//Ϊ�˴������>=1��ʱ��
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