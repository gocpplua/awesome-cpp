#include "pch.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>
#include <utility>
#include<tuple>
#include <algorithm>
#include "test.h"
std::string syscdsyscd() { return "Foo"; }
std::string foo() { return "Foo"; }
std::string bar() { return "Bar"; }
class TextBlock {
public:
    TextBlock(std::string str) {
        text = str;
    }
    const char& operator[] (std::size_t position) const {
        // do something
        std::cout << "const:";
        return text[position];
    }
    char& operator[] (std::size_t position) {
        // 调用 const 版本的重载函数，避免代码重复
        std::cout << "non-const:";
        return text[position];
    }
private:
    std::string text;
};

class BorrowA {
public:
    void checkout() {}
};

class BorrowB {
private:
    bool checkout() {}
};

class Mp3 :public BorrowA, public BorrowB {

};

int mainEEE() {
    //Mp3 mp;
    //mp.BorrowA::checkout();// get

    // -2147483648 ~2147483647


    LeetCode7 x;
    //[-10,-9,-6,-4,1,9,9]
    //[-5, -3, 0, 7, 8, 8]
    x.addBinary("11", "1");
    int a = 3;
    a = a >> 1;
    std::cout << a << std::endl;
    return 0;
}

int mainDDDD() {
    Test1 t;

    Derived d;
    int x;
    d.mf1();
//    d.mf1(x);
    d.mf2();
    d.mf3();
    //d.mf3(x);

    return 0;
}
int mainCCCC()
{
    class Window
    {
    public:
        Window() {
            std::cout << "construct window:" << this << " " << a_ << std::endl;
        }
        ~Window() {
            a_ = 1;
            std::cout << "des construct window:" << this << " " << a_ << std::endl;
        }
        Window(const Window& p)
        {
            std::cout << "Window Copy Constructor:" << this << std::endl;
        }

        Window& operator=(const Window& p)
        {
            std::cout << "Window Assign Constructor:" << this << std::endl;
            return *this;
        }
        virtual void onResize() {
            std::cout << "Window:" << this << " " << a_  << std::endl;
        }
        const int& getB()
        {
            return b_;
        }
    public:
        int a_ = 0;
    private:
        int b_ = 0;
    };

    class SpecialWindow :public Window {
    public:
        SpecialWindow() {
            std::cout << "construct SpecialWindow:" << this << " " << a_ << std::endl;
        }
        ~SpecialWindow() {
            std::cout << "des construct SpecialWindow:" << this << " " << a_ << std::endl;
        }
        SpecialWindow(const SpecialWindow& p)
        {
            std::cout << "SpecialWindow Copy Constructor:" << this << std::endl;
        }

        SpecialWindow& operator=(const SpecialWindow& p)
        {
            std::cout << "SpecialWindow Assign Constructor:" << this << std::endl;
            return *this;
        }
        virtual void onResize() {
            std::cout << "SpecialWindow:" << this << " " << a_ << std::endl;
            //static_cast<Window>(*this).onResize();
            Window::onResize();
        }
    };

    SpecialWindow sw;
    sw.a_ = 2;
    sw.onResize();
    int& b = *(const_cast<int*>(&sw.getB()));
    b = 1;
    return 0;
}

int mainBBB()
{
    TextBlock tb("Hello");
    std::cout << tb[0] << std::endl;

    const TextBlock ctb("World");
    std::cout << ctb[0] << std::endl;
    return 0;
}

int mainASA()
{
    std::unordered_map<std::string, std::string(*)()> m;
    // Map the functions to the names
    m["foo"] = &foo;
    m["bar"] = &bar;
    // Display all of the mapped functions
    std::unordered_map<std::string, std::string(*)()>::const_iterator it = m.begin();
    std::unordered_map<std::string, std::string(*)()>::const_iterator end = m.end();
    while (it != end) {
        std::string first = it->first;
        std::string second = (it->second)();
        std::cout << second << std::endl;
        ++it;
    }
    return 0;
}


int mainman() {

    std::string strOper;
    std::cout << ">>>";
    while (true)
    {
        //std::getline(std::cin, strOper);
    }

    return 0;
}


#include <iostream>
#include <queue>
#define N 5
using namespace std;
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
int mainASAD()
{
    for (int i = 1; i <= N; i++)
    {
        if (visited[i] == 1)
            continue;
        BFS(i);
    }


    // 
    return 0;
}



using namespace std;

int main()
{
    // 使用优先级队列实现最大堆最小堆：时间复杂度有O(logK)。
    // https://blog.csdn.net/nisxiya/article/details/45725857
    // http://www.sobugou.com/blog/2015/09/01/hashmapshi-li-:qiu-top-k/
	unordered_map<int, int> map = { {1,1},{3,3},{2,2},{4,4},{5,5},{7,7},{6,6} };
	struct node {
		int userid;
		int deposit;
		node(int a = 0, int b = 0) :userid(a), deposit(b) {}
	};

	struct cmp {
		bool operator()(node a, node b) {
			return a.deposit > b.deposit;
		}
	};
	priority_queue<node, vector<node>, cmp> q;
    q.push(node(0, 0));
    q.push(node(0, 0));
    q.push(node(0, 0));
	for (const auto& v : map)
	{
        std::cout << "q.top() is now " << q.top().userid << " " << q.top().deposit << '\n';
        if (v.second > q.top().deposit)
        {
            q.pop();
            q.push(node(v.first, v.second));
        }
	}
	return 0;
}