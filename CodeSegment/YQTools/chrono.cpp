// C++ 工具库: 
// 1、获取主机时间: 年月日时分秒
// 2、格式化输出：年月日时分秒

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <sstream>

/* 实验结果
本地时间(localtime_s):14 39 58
本地时间格式化:11/28/19 14:39:58
UTC时间(gmtime_s):6 39 58
locale name:Chinese (Simplified)_China.936
bad locale name
*/

int mainChrono() {
    // 表示系统范围的实时壁钟
    // !!用在需要得到绝对时点的场景
    auto timePoint = std::chrono::system_clock::now();
    auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm now_time;
    localtime_s(&now_time, &tt);
    std::cout << "本地时间(localtime_s):" << now_time.tm_hour << " " << now_time.tm_min << " " << now_time.tm_sec << std::endl;
    std::cout << "本地时间格式化:" << std::put_time(&now_time, "%c") << '\n';
   
    // 表示单调时钟。此时钟的时间点无法减少，因为物理时间向前移动。此时钟与壁钟时间无关（例如，它能是上次重启开始的时间），且最适于度量间隔
    // !!用在需要得到时间间隔，并且这个时间间隔不会因为修改系统时间而受影响的场景
    auto start = std::chrono::steady_clock::to_time_t(std::chrono::steady_clock::now());
    gmtime_s(&now_time, &start);
    std::cout << "UTC时间(gmtime_s):" << now_time.tm_hour << " " << now_time.tm_min << " " << now_time.tm_sec << std::endl;

    // 格式化 time
    // 1、put_time
    // 2、get_time(这个函数需要设置环境std::locale，但是会崩溃，所以用了try/catch)，崩溃暂时无法解决
    // crash 参考资料:https://developercommunity.visualstudio.com/content/problem/330322/stdlocale-l2-en-usutf-8-broken-crashes-now.html
    try
    {
        std::cout << "locale name:" << std::locale("").name() << std::endl;
        std::tm t = {};
        std::istringstream ss("2011-Februar-18 23:12:34");
        ss.imbue(std::locale("de_DE.utf-8"));
        ss >> std::get_time(&t, "%Y-%b-%d %H:%M:%S");
        if (ss.fail()) {
            std::cout << "Parse failed\n";
        }
        else {
            std::cout << std::put_time(&t, "%c") << '\n';
        }
    }
    catch (const std::exception& e) // CException 无法捕获这个崩溃
    {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}