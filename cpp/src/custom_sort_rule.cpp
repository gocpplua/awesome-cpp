/*
如何自定义C++ STL关联式容器的排序规则 
参考文章:http://www.cdsy.xyz/computer/programme/stl/20210307/cd161510782812005.html
*/
#include <iostream>
#include <set>      // set
#include <string>       // string
using namespace std;
//定义函数对象类
class cmp {
public:
    //重载 () 运算符
    bool operator ()(const string &a,const string &b) {
        //按照字符串的长度，做升序排序(即存储的字符串从短到长)
        return  (a.length() < b.length());
    }
};

// std::less<T> 为例，其底层实现为：
/*
template <typename T>
struct less {
    //定义新的排序规则
    bool operator()(const T &_lhs, const T &_rhs) const {
        return _lhs < _rhs;
    }
}
*/

//自定义类
class myString {
public:
    //方式三、类中友元函数的定义 - 类外部友元函数的具体实现
    //friend bool operator <(const myString &a, const myString &b);

    //定义构造函数，向 myset 容器中添加元素时会用到
    myString(string tempStr) :str(tempStr) {};
    //获取 str 私有对象，由于会被私有对象调用，因此该成员方法也必须为 const 类型
    string getStr() const{
        return this->str;
    };

///*
    // 方式一、-> 成员函数形式
    bool operator <(const myString & tempStr) const {
        //以字符串的长度为标准比较大小
        return this->str.length() < tempStr.str.length();
    }
//*/
private:
    string str;
};
/*
// 方式二、全局函数形式
//重载 < 运算符，参数必须都为 const 类型
bool operator <(const myString &stra, const myString & strb) {
    //以字符串的长度为标准比较大小
    return stra.getStr().length() < strb.getStr().length();
}
*/
/*
//方式三、类外部友元函数的具体实现
bool operator <(const myString &stra, const myString &strb) {
    //以字符串的长度为标准比较大小
    return stra.str.length() < strb.str.length();
}
*/

int main() {
    //创建 set 容器，并使用自定义的 cmp 排序规则
    std::set<string, cmp>myset{"http://www.cdsy.xyz/computer/programme/stl/",
                               "http://www.cdsy.xyz/computer/programme/Python/",
                               "http://www.cdsy.xyz/computer/programme/java/"};
    //输出容器中存储的元素
    for (auto iter = myset.begin(); iter != myset.end(); ++iter) {
            cout << *iter << endl;
    }

    ////////////////////////////////////////////////////////////
    std::set<myString> mysetString;
    //向 set 容器添加元素，这里会调用 myString 类的构造函数
    mysetString.emplace("http://www.cdsy.xyz/computer/programme/stl/");
    mysetString.emplace("http://www.cdsy.xyz/computer/programme/C_language/");
    mysetString.emplace("http://www.cdsy.xyz/computer/programme/Python/");
    //
    for (auto iter = mysetString.begin(); iter != mysetString.end(); ++iter) {
        myString mystr = *iter;
        cout << mystr.getStr() << endl;
    }

    return 0;
}