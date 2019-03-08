// CodeSegment.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

class A {
    virtual int test() { return 1; };
};
class B : public A {
    virtual int test() { throw "aaaa"; };
};

int main()
{
    Test::setA(1);
    Test::setA(2);
    std::cout << "a = " << Test::getA() << std::endl;
    std::cout << "Hello World!\n";

    int tmp_windeposit = 1020;
    int fee = tmp_windeposit * 10 / 100 ;

    if (tmp_windeposit <= 100) {			// 100两以下不收
        fee *= 0;
    }
    else if (tmp_windeposit <= 10000) {	// 1万两以下
    }
    else if (tmp_windeposit <= 100000) {	// 10万两以下
        fee *= (int)ceil((double)tmp_windeposit / 20000);
    }
    else {							// 10万两以上
        fee *= 5;
    }
    std::cout << "fee = " << fee << std::endl;

    B b1;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
