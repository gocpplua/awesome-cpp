// creatocpu100.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <thread>
#include <atomic>
#define MAX_CPU (8)

std::atomic<char> flag = '1' - '0';

void ThreadCallBack()
{
	while (flag != 'q')
	{
		int interval = flag;
		if (0 == interval)
		{
			continue;
		}
		int count = 0;
		int loop = 10000000;
#if _DEBUG
		loop = 100000;
#endif
			for (size_t i = 0; i < loop * interval; i++)
		{
			count = count + 1;
			count += 3;
		}
		std::this_thread::sleep_for(std::chrono::nanoseconds(interval));
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	SYSTEM_INFO sysInfo = { 0 };
	GetSystemInfo(&sysInfo);
	DWORD dwProcessorCoreNum = sysInfo.dwNumberOfProcessors;
	std::thread thread[MAX_CPU];
	for (int i = 0; i < dwProcessorCoreNum && i < MAX_CPU; i++)
	{
		thread[i] = std::thread(ThreadCallBack);
		int core = 1 << i;
		SetProcessAffinityMask(static_cast<HANDLE>(thread[i].native_handle()), core);
	}
	printf("ÇëÊäÈë×Ö·û£º");
	while (true)
	{
		int alphabet = getchar();
		if (alphabet == 10)
		{
			continue; // »»ÐÐ
		}
		printf("ÇëÊäÈë×Ö·û£º");
		if (alphabet == 'q'){
			flag = alphabet;
			break;
		}
		else
		{
			flag = (alphabet - '0') > 0 ? (alphabet - '0'):0;
		}
	}

	for (int i = 0; i < dwProcessorCoreNum && i < MAX_CPU; i++)
	{
		thread[i].join();
	}
	return 0;
}

