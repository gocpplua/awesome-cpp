#pragma once
#include <iostream>

class Singleton
{
public:
    bool print() {
        return true;
    }
private:
    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
};