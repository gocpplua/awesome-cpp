/**************************************************************************
	*  @Copyright (c) 2020, ChenQi, All rights reserved.
	*  @file	 : and_eq.h
	*  @version  : ver 1.0
    *  @author   : ChenQi
    *  @date     : 2020/05/22 12:06
    *  @brief    : 代用运算符：用作 &= 的替代写法(https://zh.cppreference.com/w/cpp/keyword/and_eq)
**************************************************************************/#pragma once
#include <iostream>
#include <bitset>
inline void test_and_ed() {
    std::bitset<4> mask("1100");
    std::bitset<4> val("0111");
    val and_eq mask; 
    // val &= mask; // 功能同上
    std::cout << val << std::endl;
}

