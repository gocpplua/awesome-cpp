// cppreference.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "and_eq.h"
#include "system.h"
#include <map>
#include<string>
#include "tarray.h"
#include<vector>
#include"moveconstructor.h"
bool CompHourKeyDesc(const std::pair<std::string, std::string>& x, const std::pair<std::string, std::string>& y)
{
    return  atoi(x.first.c_str()) > atoi(y.first.c_str());
}
int main()
{
    std::map<std::string, std::string> ret;
    ret["1"] = "1";
    ret["2"] = "2";
    // std::qsort(ret.begin(), ret.end(), CompHourKeyDesc);
    std::cout << "start main" << std::endl;
    //test_and_ed();
    t_system();

    tarray();

    cout << "emplace_back:" << endl;
    std::vector<testDemo> demo1;
    demo1.emplace_back(2);

    cout << "push_back:" << endl;
    std::vector<testDemo> demo2;
    demo2.push_back(2);

    // remove() 的实现原理是，在遍历容器中的元素时，一旦遇到目标元素，就做上标记，然后继续遍历，直到找到一个非目标元素，
    // 即用此元素将最先做标记的位置覆盖掉，同时将此非目标元素所在的位置也做上标记，等待找到新的非目标元素将其覆盖。
    // 因此，如果将程序中 demo 容器的元素全部输出，得到的结果为 1 4 5 4 3 5。
    vector<int>demo{ 1,3,3,4,3,5 };
    //交换要删除元素和最后一个元素的位置
    auto iter = std::remove(demo.begin(), demo.end(), 3);

    cout << "size is :" << demo.size() << endl;
    cout << "capacity is :" << demo.capacity() << endl;
    //输出剩余的元素
    for (auto first = demo.begin(); first < iter; ++first) {
        cout << *first << " "; // output: 1 4 5
    }
    cout << endl;
    for (int i = 0; i < 6; i++)
        cout << demo[i] << " "; // output: 1 4 5 4 3 5
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
