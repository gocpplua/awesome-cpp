#include<iostream>

int checkCPU()
{
	union w
	{
		int a;
		char b;
	}c;
	c.a = 1;
	return (c.b == 1); // 小端返回TRUE,大端返回FALSE
}

int main(){

  int num = 0x123456;
  if(*(char*)(&num) == 12){
    std::cout << "big" << std::endl;
  }
  else{
    std::cout << "small" << std::endl;
  }

  std::cout << checkCPU << std::endl;
}