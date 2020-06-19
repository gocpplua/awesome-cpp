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