#pragma once
#include <string>
class Test;
class Test1 {
public:
    Test1();
    int a = 0;
    //int aa(Test& a){}
    Test bb();
};


class Base {
private:
    int x;
public:
    virtual void mf1() = 0;
    virtual void mf1(int) {};
    virtual void mf2() {};
    void mf3() {}
    void mf3(double){}
};

class Derived :public Base {
public:
    virtual void mf1() {}
    void mf3(){}
    void mf4() {}
};

class CompanyA {
    void sendCleartext(const std::string& msg) {}
    void sendEncrypted(const std::string& msg) {}
};


class CompanyB {
    void sendCleartext(const std::string& msg) {}
    void sendEncrypted(const std::string& msg) {}
};

class MsgInfo {

};

template<typename Company>
class MsgSender {
public:
    void sendClear(const MsgInfo& info) {
        std::string msg;
        Company c;
        c.sendCleartext(msg);
    }

    void sendSecret(const MsgInfo& info) {

    }
};

template<typename Company>
class LoggingMsgSender :public MsgSender<Company> {
public:
    void sendClearMsg(const std::string& info) {
        sendClear(info);
    }
};



class LeetCode7 {
public:
    // -2147483648 ~2147483647
    int reverse(int x) {
        int source = x;
        int target = 0;
        bool positive = source > 0 ? true : false;
        while (source != 0)
        {
            int remain = source % 10;
            source /= 10;
            if (positive)
            {
                if (target > 214748364)
                {
                    return 0;
                }
                else if (target == 214748364 && remain > 7)
                {
                    return 0;
                }
            }
            else
            {
                if (target < -214748364)
                {
                    return 0;
                }
                else if (target == -214748364 && remain < -8)
                {
                    return 0;
                }
            }
            target = target * 10 + remain;
        }
        return target;
    }

    bool isPalindrome(int x) {
        int source = x;
        int target = 0;
        if (x < 0 || (x % 10 == 0 && x != 0))
        {
            return false;
        }
        else if (x > 0)
        {
            while (target < source)
            {
                target = target * 10 + source % 10;
                if (target == source)
                {
                    return true;
                }

                source /= 10;
                if (target == source)
                {
                    return true;
                }
            }
        }
        else
        {
            return true;
        }
        return false;
    }
};