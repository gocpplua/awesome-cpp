#pragma once
#include <iostream>
class Library_materials {
public:
    virtual void check_in() {
        using namespace std;
        std::cout << "Library_materials" << std::endl;
    }
};

class Book : public Library_materials {
public:
    virtual void check_in() {
        std::cout << "Book" << std::endl;
    }
};