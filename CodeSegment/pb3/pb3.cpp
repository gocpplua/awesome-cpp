// pb3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>  
#pragma comment(lib,"ws2_32.lib") 
#include "../pb3/student.pb.h"
int mainTest();
int main()
{
	const int versionL = 1;
	const int versionH = 1;
	// 1、 初始化套接字:添加头文件（#include <WinSock2.h>） 和 lib库（#pragma comment(lib,"ws2_32.lib")
	WSAData wsaData;
	int nErr = WSAStartup(MAKEWORD(versionL, versionH), &wsaData);
	if (0 != nErr)
	{
		std::cout << " 初始化套接字失败:" << WSAGetLastError() << std::endl;
		return 0;
	}
	// WSAStartup 即使没有我需要的库1.1，但是也会加载系统上的库，所以需要校验版本
	if (LOBYTE(wsaData.wVersion) != versionL || HIBYTE(wsaData.wVersion) != versionH)
	{
		std::cout << " 初始化套接字失败:" << "错误的网络库版本" << std::endl;
		return 0;
	}

	// 2、 创建socket
	SOCKET socServer = socket(AF_INET, SOCK_STREAM, 0); // 指明地址簇类型(IPV4:AF_INET), 指明socket的类型(数据报套接字TCP:SOCK_STREAM),指明数据传输协议/指明端到端协议
	if (INVALID_SOCKET == socServer)
	{
		std::cout << " 初始化socket失败:" << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}

	// 3、初始化自己的地址
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8182);//从"主机字节顺序" 转变为 "网络字节顺序"
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// 4、绑定socket
	int nBind = bind(socServer, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (0 != nBind)
	{
		std::cout << WSAGetLastError() << std::endl;
		return 0;
	}
	//5、listen 监听
	if (listen(socServer, 1))
	{
		std::cout << "listen failed:" << WSAGetLastError() << std::endl;
		return 0;
	}
	SOCKET socClientServer;
	SOCKADDR_IN addrClient;
	int len = sizeof(addrClient);
	char revData[1024];
	//6、等待连接
	if ((socClientServer = accept(socServer, (SOCKADDR*)&addrClient, &len)) <= 0) // 使用 socClient 进行和客户端的通信
	{
		std::cout << "accept failed:" << WSAGetLastError() << std::endl;
		return 0;

	}
	// 此处连接成功后，发送信息
	tutorial::Student st;
	st.set_id(28);
	st.set_name("chenqi");
	const std::string str = st.SerializeAsString(); // 将消息序列化并储存在指定的string中。注意里面的内容是二进制的，而不是文本；我们只是使用string作为一个很方便的容器。
	std::cout << str << std::endl;
	send(socClientServer, str.c_str(), strlen(str.c_str()) + 1, 0);
	//关闭连接套接字
	closesocket(socClientServer);

	mainTest();
}

int mainTest()
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
