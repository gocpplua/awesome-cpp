#pragma once
#include <string>
using namespace std;
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


    int getValue(char pre, char cur) {
        switch (pre) {
        case 'I': return (cur == 'V' || cur == 'X') ? -1 : 1;
        case 'V': return 5;
        case 'X': return (cur == 'L' || cur == 'C') ? -10 : 10;
        case 'L': return 50;
        case 'C': return (cur == 'D' || cur == 'M') ? -100 : 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
        }
    }
    int romanToInt(std::string s) {
        int target = 0;
        int len = s.length();
        if (len <= 0) return 0;
        char pre = s[0];
        for (int i = 1; i < len; i++)
        {
            char current = s[i];
            target += getValue(pre, current);
            pre = current;
        }
        target += getValue(pre, ' '); // 特别注意最后一位的问题
        return target;
    }

    int romanToInt1(std::string s) {
        int target = 0;
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
            char c = s[i];
            if (c == 'I')
            {
                if (i < len - 1)
                {
                    if (s[i+1] == 'V')
                    {
                        target += 4;
                        i++;
                        continue;
                    }
                    else if (s[i+1]== 'X')
                    {
                        target += 9;
                        i++;
                        continue;
                    }
                }
                target += 1;
            }
            else if (c == 'X')
            {
                if (i < len - 1)
                {
                    if (s[i+1] == 'L')
                    {
                        target += 40;
                        i++;
                        continue;
                    }
                    else if (s[i+1] == 'C')
                    {
                        target += 90;
                        i++;
                        continue;
                    }
                }
                target += 10;
            }
            else if (c == 'C')
            {
                if (i < len - 1)
                {
                    if (s[i+1] == 'D')
                    {
                        target += 400;
                        i++;
                        continue;
                    }
                    else if (s[i+1] == 'M')
                    {
                        target += 900;
                        i++;
                        continue;
                    }
                }
                target += 100;
            }
            else if (c == 'V')
            {
                target += 5;
            }
            else if (c == 'L')
            {
                target += 50;
            }
            else if (c == 'D')
            {
                target += 500;
            }
            else if (c == 'M')
            {
                target += 1000;
            }
        }
        return target;
    }

    string longestCommonPrefix(vector<string>& strs) {
        if (!strs.size())return "";
        string commonPre = strs[0];
        for (int i = 1; i < strs.size(); i++) {
            int j = 0;
            for (; j < commonPre.length() && j < strs[i].length(); j++) {
                if (commonPre[j] != strs[i][j]) {
                   break;
                }
            }
            if (j == 0) return "";
            commonPre[j] = '\0';
        }
        return commonPre;
    }
};