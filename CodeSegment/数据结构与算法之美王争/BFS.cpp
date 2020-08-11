// https://www.jianshu.com/p/70952b51f0c8

#include <iostream>
#include <queue>
#define N 5
using namespace std;
namespace aa {
    int maze[N][N] = {
        { 0, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0 }
    };
    int visited[N + 1] = { 0, };
    void BFS(int start)
    {
        queue<int> Q;
        Q.push(start);
        visited[start] = 1;
        while (!Q.empty())
        {
            int front = Q.front();
            cout << front << " ";
            Q.pop();
            for (int i = 1; i <= N; i++)
            {
                if (!visited[i] && maze[front - 1][i - 1] == 1)
                {
                    visited[i] = 1;
                    Q.push(i);
                }
            }
        }
    }
    int main1()
    {
        for (int i = 1; i <= N; i++)
        {
            if (visited[i] == 1)
                continue;
            BFS(i);
        }
        return 0;
    }
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
