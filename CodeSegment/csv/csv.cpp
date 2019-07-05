// csv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  

using namespace std;
int main()
{
    // 写文件  
    ofstream outFile;
    outFile.open("data.csv", ios::out); // 打开模式可省略
    outFile << "name" << ',' << "age" << ',' << "hobby" << endl;
    outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;
    outFile << "Tom" << ',' << 25 << ',' << "football" << endl;
    outFile << "Jack" << ',' << 21 << ',' << "music" << endl;
    outFile.close();

    // 读文件  
    ifstream inFile("data.csv", ios::in);
    string lineStr;
    vector<vector<string>> strArray;
    while (getline(inFile, lineStr))
    {
        // 打印整行字符串  
        cout << lineStr << endl;
        // 存成二维表结构  
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        // 按照逗号分隔  
        while (getline(ss, str, ','))
            lineArray.push_back(str);
        strArray.push_back(lineArray);
    }

    getchar();
    return 0;
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
