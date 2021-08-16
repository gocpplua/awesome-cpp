# 单元测试
如果你平常使用 Java 语言做开发，当你听到单元测试工具的时候，你很可能马上会想起 JUnit。作为一名C++软件工程师，当我第一次打算给我的程序做单元测试的时候，我的第一 想法是：有这样的工具吗？经过一段时间的搜索之后，我的反应变成了：我该用哪一个？

我在学校的时候，很少听说C++的单元测试工具，以至于我一直认为这样的工具是不存在。 后来慢慢的发现我们可以选择的远比你想象中的要多得多：Catch, Boost.Test, UnitTest++, lest, bandit, igloo, xUnit++, CppTest, CppUnit, CxxTest, cpputest, googletest, cute。

那我们应该使用哪一个呢？如果你在 Google 里面搜索：best c++ unit testing framework。头两条，一条是 [stackoverflow](http://stackoverflow.com/questions/20606793/state-of-the-art-c-unit-testing) 的问答，另一条是 [reddit](https://www.reddit.com/r/cpp/comments/36pru0/best_way_to_do_unit_testing_in_c/) 的问答 。这两个问题都指向同一个单元测试框架：Catch。

### 为什么使用 Catch
在 Catch 的官方文档中有一篇：[Why do we need yet another C++ test framework](https://github.com/philsquared/Catch/blob/master/docs/why-catch.md)? 有兴趣的可以去看看。对我来说，它最吸引我的地方主要是：
- 几乎不用配置，它是一个单头文件的测试框架，压根不要什么额外的配置就可以使用
- 语法非常简单明了，用它写的测试代码和自然语言一样易懂。

### 如何使用 Catch


### 常见问题:
1.  [ERROR: catch2/catch.hpp: No such file or directory](https://stackoverflow.com/questions/65098604/catch2-installation-on-ubuntu-20-04-include-catch2-catch-hpp)

> The problem is quite simple: clonning catchorg/Catch2 now gets you a v3 branch by default, which works differently. The most important change is that it is no longer single header, and that the catch2/catch.hpp header no longer exists.
>
> You can either switch to the v2 branch before configuring and installing the build, or adapt your code to the changes in v3, [starting with this documentation on v2 -> v3 migration](https://github.com/catchorg/Catch2/blob/devel/docs/migrate-v2-to-v3.md#top).
>
> To get the default main, link against Catch2::Catch2WithMain target.

----

参考文章:
- [C++ 的单元测试工具 —— Catch](http://blog.guorongfei.com/2016/08/22/cpp-unit-test-catch/)