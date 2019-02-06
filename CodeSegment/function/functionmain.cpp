#include<iostream>
#include<functional>

void funcMain(void)
{
    std::cout << __FUNCTION__ << std::endl;
}

class FooMain
{
public:
    static int foo_func(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ") -> ";
        return a;
    }
};

class BarMain
{
public:
    int operator()(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ") -> ";
        return a;
    }
};

void call_when_even(int x, const std::function<void(int)>& f)
{
    if (!(x & 1))
    {
        f(x);
    }
}
void output(int x)
{
    std::cout << x << " ";
}

int main()
{
    std::function<void(void)> fr1 = funcMain; //绑定一个普通函数
    fr1();

    std::function<int(int)> fr2 = FooMain::foo_func;
    std::cout << fr2(123) << std::endl;

    //绑定一个仿函数
    BarMain bar;
    fr2 = bar;
    std::cout << fr2(123) << std::endl;

    auto fr = std::bind(output, std::placeholders::_1);
    for (size_t i = 0; i < 10; i++)
    {
        call_when_even(i, fr);
    }

    return 0;
}

//参考文章:https://www.cnblogs.com/AnnieKim/archive/2011/12/04/2275589.html