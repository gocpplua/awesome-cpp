
#if 0 // 测试Timer
#include <iostream>
#include <thread>
#include "Timer.h"

int main()
{
    YQTools::Timer tm;
    std::this_thread::sleep_for(std::chrono::seconds(6));
    std::cout << tm.elapsed() << std::endl;
    std::cout << tm.elapsed_hours() << std::endl;
    std::cout << tm.elapsed_minutes() << std::endl;
    std::cout << tm.elapsed_s() << std::endl;
    std::cout << tm.elapsed_ms() << std::endl;

    tm.reset();
    std::cout << tm.elapsed_us() << std::endl;
    return 0;
}
#endif
#include <iostream>
#include "Singleton.h"
int main()
{
    if (Singleton::getInstance().print())
    {
        std::cout << "singleton" << std::endl;
    }
	return 0;
}