// pb3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include "../pb3/student.pb.h"
int main()
{
    tutorial::Student st;
    st.set_id(28);
    st.set_name("chenqi");
    const std::string str = st.SerializeAsString(); // 将消息序列化并储存在指定的string中。注意里面的内容是二进制的，而不是文本；我们只是使用string作为一个很方便的容器。
    std::cout << str << std::endl;

    tutorial::Student deserializedStudent;
    bool bParseOK = deserializedStudent.ParseFromString(str);
    if (!bParseOK)
    {
        std::cout << "ParseFromString failed!" << std::endl;
        return 0;
    }

    std::cout << "deserializedStudent debugString:" << deserializedStudent.DebugString();
    std::cout << "Student ID: " << deserializedStudent.id() << std::endl;
    std::cout << "Name: " << deserializedStudent.name() << std::endl;
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
