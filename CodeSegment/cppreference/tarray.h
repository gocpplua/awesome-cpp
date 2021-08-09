#include <iostream>
#include <array>
using namespace std;

void tarray()
{
	array<double, 5> ad = { 0.1,0.3,0.5,0.7,0.9 };
	double* p = ad.data();
	cout << "ad.data()=" << *p << endl;
	cout << "*£¨p+1£©" << *(p + 1) << endl;
	cout << "*(p-1)" << *(p - 1) << endl;
	cout << "*£¨p+10£©" << *(p + 10) << endl;
	cout << "*(p-10)" << *(p - 10) << endl;



}