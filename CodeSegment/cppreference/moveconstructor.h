#include <iostream> 
using namespace std;
class testDemo
{
public:
    testDemo(int num) :num(num) {
        std::cout << "���ù��캯��" << endl;
    }
    testDemo(const testDemo& other) :num(other.num) {
        std::cout << "���ÿ������캯��" << endl;
    }
    testDemo(testDemo&& other) :num(other.num) {
        std::cout << "�����ƶ����캯��" << endl;
    }
private:
    int num;
};