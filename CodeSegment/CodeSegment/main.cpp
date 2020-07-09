#include "pch.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>
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

int main() {
    //Mp3 mp;
    //mp.BorrowA::checkout();// get

    // -2147483648 ~2147483647


    LeetCode7 x;
    //[-10,-9,-6,-4,1,9,9]
    //[-5, -3, 0, 7, 8, 8]
    std::vector<int> vecA({ -10,-9,-6,-4,1,9,9 });
    std::vector<int> vecB({ -5, -3, 0, 7, 8, 8 });
    {
        int aSize = vecA.size();
        int bSize = vecB.size();
        ListNode* a1 = new ListNode[aSize];
        ListNode* b1 = new ListNode[bSize];
        for (int i = 0; i < aSize - 1; i++)
        {
            a1[i].val = vecA[i];
            a1[i].next = &(a1[i + 1]);
        }
        a1[aSize - 1].val = vecA[aSize - 1];
        for (int i = 0; i < bSize - 1; i++)
        {
            b1[i].val = vecB[i];
            b1[i].next = &(b1[i + 1]);
        }
        b1[bSize - 1].val = vecB[bSize - 1];

        x.mergeTwoLists(a1, b1);
    }

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
