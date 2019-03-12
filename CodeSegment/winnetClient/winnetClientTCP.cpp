// winnetClientTCP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// tcp 客户端

#include "pch.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>  
#pragma comment(lib,"ws2_32.lib") 
int main()
{
    // 1、 初始化套接字:添加头文件（#include <WinSock2.h>） 和 lib库（#pragma comment(lib,"ws2_32.lib")
    WSAData wsaData;
    int nErr = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (0 != nErr)
    {
        std::cout << " 初始化套接字失败:" << GetLastError() << std::endl;
        return 0;
    }

    // 2、 创建socket
    SOCKET socClient = socket(AF_INET, SOCK_STREAM, 0); // 指明地址簇类型(IPV4:AF_INET), 指明socket的类型(数据报套接字TCP:SOCK_STREAM),指明数据传输协议/指明端到端协议
    if (INVALID_SOCKET == socClient)
    {
        std::cout << " 初始化socket失败:" << GetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    SOCKADDR_IN addrSrv;//服务器的地址数据结构
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8182);//端口号为8182
    inet_pton(AF_INET, "127.0.0.1", &(addrSrv.sin_addr)); // 等价于:addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //127.0.0.1为本电脑IP地址

    if (0 != connect(socClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR))) // connect 返回0 表示连接成功
    {
        std::cout << " connet失败:" << GetLastError() << std::endl;
        WSACleanup();
        return 0;
    }

    std::string strSend;
    int nRecvfromLen = sizeof(SOCKADDR);
    std::cout << "waiting for cin:" << std::endl;
    while (true)
    {
        std::cin >> strSend;
        int nSend = send(socClient, strSend.c_str(), strlen(strSend.c_str()) + 1, 0); 
        if (nSend <= 0)
        {
            std::cout << WSAGetLastError() << std::endl;
        }
        /*
        char szRecv[100] = { 0 };
        int nRecv = recvfrom(socClient, szRecv, 100, 0, (SOCKADDR*)&addrSrv, &nRecvfromLen);
        if (-1 == nRecv)
        {
            std::cout << WSAGetLastError() << std::endl;
        }
        else
        {
            std::cout << "client recv:" << szRecv << std::endl;
        }*/
    }
    closesocket(socClient);
    WSACleanup();
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
