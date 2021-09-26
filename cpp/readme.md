## 环境配置

- 使用C++11
- vscode中配置C++11需要注意
> c_cpp_properties.json  中 "cppStandard": "c++11"
> 添加 tasks.json，并且"args"中加上"-std=c++11"

## 目录说明
```
.
├── 3thParty  // 第三方库
├── doc       // 文档 -- 用于对C++语法、第三方库使用等的总结
├── out       // 编译输出的可执行文件
├── readme.md 
├── src       // C++源码
└── tests     // 单元测试目录
```

## doc文件夹下文件说明
```
.
├── icecream.hpp.md // 打印调试库使用说明
└── unit-test.md // 单元测试 Catch2 的使用
```

## 单元测试
```
cd tests && mkdir -p build && cd build && cmake .. && make && ./out/test_demo --success
```

## 参考资料:
1. [现代 C++ 教程高速上手 C++ 11/14/17/20](https://changkun.de/modern-cpp/)

2. [0voice/cpp_new_features](https://github.com/0voice/cpp_new_features)
> 2021年最新整理， C++ 学习资料，含C++ 11 / 14 / 17 / 20 / 23 新特性、入门教程、推荐书籍、优质文章、学习笔记、教学视频等

