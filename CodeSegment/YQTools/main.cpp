
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

#if 0
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
#endif
#pragma optimize( "", off )
#include <iostream>
#include "constructor.h"
using namespace std;

A GetA()
{
    return A(1);
}

A&& MoveA()
{
    return A(1);
}

int main()
{
    cout << "-------------------------1-------------------------" << endl;
    A a(1);
    cout << "-------------------------2-------------------------" << endl;
    A b = a;
    cout << "-------------------------3-------------------------" << endl;
    A c(a);
    cout << "-------------------------4-------------------------" << endl;
    b = a;
    cout << "-------------------------5-------------------------" << endl;
    A d = A(1);
    cout << "-------------------------6-------------------------" << endl;
    A e = std::move(a);
    cout << "-------------------------7-------------------------" << endl;
    A f = GetA();
    cout << "-------------------------8-------------------------" << endl;
    A&& g = MoveA();
    cout << "-------------------------9-------------------------" << endl;
    d = A(1);
}
