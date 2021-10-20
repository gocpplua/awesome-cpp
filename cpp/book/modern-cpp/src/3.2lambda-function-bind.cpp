// [C++11中的lambda，std::function以及std:bind](https://paul.pub/cpp-lambda-function-bind/)
#include <iostream>
#include <vector>
#include <algorithm> // for_each
#include <functional> // function
using namespace std;

vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };

void printNumber1(vector<int>& numbers) {
	for (const int& i : numbers) {
	    if (i % 5 == 0) {
	        cout<<i<<endl;
	    }
	}
}

void printNumber2(vector<int>& numbers) {
	for (const int& i : numbers) {
	    if (i % 5 == 0) {
	        cout<<i<<endl;
	    }
	}
}


void printNumber(vector<int>& number, std::function<bool (int)> filter) {
	for (const int& i : number) {
	    if (filter(i)) {
	        cout<<i<<endl;
	    }
	}
}

bool isBetween( int i, int min, int max) {
	return i >= min && i <= max;
}

class Printer {
private:
	int min, max;
public:
  Printer(int x, int y){
    min = x;
    max = y;
  }

  void print(){
    cout << "min:" << min << endl;
    cout << "max:" << max << endl;
  }
};
void usingCallBack(std::function<void()> print){
  print();
}
int main(){
  // 方法１
  printNumber1(numbers);
  printNumber2(numbers);

  // 方法２
  cout << "for_each" << endl;
  std::for_each(numbers.begin(), numbers.end(), [] (int i) {
    if(i % 5 == 0) {
        cout<<i<<endl;
    }
  });

  std::for_each(numbers.begin(), numbers.end(), [] (int i) {
    if(i > 20) {
        cout<<i<<endl;
    }
  });

  //　方法３
  /*
  两（多）个函数，有大部分的代码都是一样的，其中只有一两行代码有不一样的地方。
  其实，我们可以对这个不一样的地方，再做一个抽象，把它们共通起来。
  C++11中，提供了一个通用的描述方法，就是std::function。 std::function可以hold住任何可以通过“()”来调用的对象，包括：
    普通函数
    成员函数
    lambda
    std::bind（见下文）后的结果
  */
  printNumber(numbers, [] (int i){ return i % 5 == 0;});
  printNumber(numbers, [] (int i){ return i > 20;});

  // 方式４: std::bind可以将调用函数时的部分参数先指定好，留下一部分在真正调用的时候确定
  std::function<bool(int)> filter = std::bind(isBetween, placeholders::_1, 20, 40);
  printNumber(numbers, filter);


  // 回调函数设置
  Printer printer = Printer(10, 20);
  std::function<void()> print = std::bind(&Printer::print, printer);
  [&](){
    print();
  }();
  usingCallBack(print);

  // lambda表达式实现：其实是编译器为我们了创建了一个类，这个类重载了()，让我们可以像调用函数一样使用。
  return 0;
}