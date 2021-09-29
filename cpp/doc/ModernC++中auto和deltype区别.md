# 一. auto和deltype作用
C++11标准引入了auto和decltype类型说明符，它能让编译器帮我们去分析表达式所属的类型。

auto 的推导能力较弱，而且还有限制。

例如: auto 不能推导数组类型:
```
  int arr[5] = {1};
  // auto 不能用于推到数组类型。 因为{arr}纯粹是一个句法结构。 它不是一个表达式，也没有类型。 因此， auto 不能从中推断出它的类型。
  auto auto_arr2[10] = {arr};  // !!!! error: ‘auto_arr2’ declared as array of ‘auto’

```

而 decltype 可以:
```
  int arr[5] = {1};
  decltype(arr) auto_arr1[5] = {1};
```

除此之外还有其他地方，我们接着往下看。 总之，decltype的出现是为了解决auto存在的一些问题，能用auto一定可以用decltype。但是auto相比decltype又更加简洁，所以能用auto就使用auto，不行就用decltype。

# 二. decltype 和 auto 区别
简单的理解可以说，auto作用变量， decltype作用表达式。

1. auto类型说明符用编译器计算变量的初始值来推断其类型(用auto声明的变量必须初始化)，而decltype虽然也让编译器分析表达式并得到它的类型，但是不实际计算表达式的值。

2. 编译器推断出来的auto类型有时候和初始值的类型并不完全一样，编译器会适当地改变结果类型使其更符合初始化规则。例如，auto一般会忽略顶层const，而把底层const保留下来。与之相反，decltype会保留变量的顶层const。

3. decltype在处理顶层const和引用的方式与auto有些许不同，如果decltype使用的表达式是一个变量，则decltype返回该变量的类型(包括顶层const和引用在内)。

如果表达式的内容是解引用操作，则decltype将得到引用类型。正如我们所熟悉的那样，解引用指针可以得到指针所指对象，而且还可以给这个对象赋值。因此decltype(*p)的结果类型就是int&.



# 参考
1. [C++11新特性— auto 和 decltype 区别和联系](https://blog.csdn.net/y1196645376/article/details/51441503)
2. [C++ auto和decltype的区别](http://c.biancheng.net/view/7158.html)
3. [C++中关键字auto和decltype的区别](https://blog.csdn.net/yishizuofei/article/details/78942425)