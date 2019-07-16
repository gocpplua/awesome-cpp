// winnetClientTCP.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
// tcp �ͻ���

#include "pch.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>  
#pragma comment(lib,"ws2_32.lib") 
int main()
{
    // 1�� ��ʼ���׽���:���ͷ�ļ���#include <WinSock2.h>�� �� lib�⣨#pragma comment(lib,"ws2_32.lib")
    const int versionL = 1;
    const int versionH = 1;
    WSAData wsaData;
    int nErr = WSAStartup(MAKEWORD(versionL, versionH), &wsaData);
    if (0 != nErr)
    {
        std::cout << " ��ʼ���׽���ʧ��:" << WSAGetLastError() << std::endl;
        return 0;
    }
    // WSAStartup ��ʹû������Ҫ�Ŀ�1.1������Ҳ�����ϵͳ�ϵĿ⣬������ҪУ��汾
    if (LOBYTE(wsaData.wVersion) != versionL || HIBYTE(wsaData.wVersion) != versionH)
    {
        std::cout << " ��ʼ���׽���ʧ��:" << "����������汾" << std::endl;
        return 0;
    }
    // 2�� ����socket
    SOCKET socClient = socket(AF_INET, SOCK_STREAM, 0); // ָ����ַ������(IPV4:AF_INET), ָ��socket������(���ݱ��׽���TCP:SOCK_STREAM),ָ�����ݴ���Э��/ָ���˵���Э��
    if (INVALID_SOCKET == socClient)
    {
        std::cout << " ��ʼ��socketʧ��:" << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    SOCKADDR_IN addrSrv;//�������ĵ�ַ���ݽṹ
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8182);//�˿ں�Ϊ8182
    inet_pton(AF_INET, "127.0.0.1", &(addrSrv.sin_addr)); // �ȼ���:addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //127.0.0.1Ϊ������IP��ַ

    if (0 != connect(socClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR))) // connect ����0 ��ʾ���ӳɹ�
    {
        std::cout << " connetʧ��:" << WSAGetLastError() << std::endl;
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
    }
    closesocket(socClient);
    WSACleanup();
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
