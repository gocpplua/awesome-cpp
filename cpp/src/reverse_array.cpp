#include <iostream>

void inplace_swap(int *x, int *y){
  *y = *x ^ *y;
  *x = *x ^ *y;
  *y = *x ^ *y;
}

void reserve_array(int a[], int cnt){ 
  // 《深入理解计算机系统》 P38中，如果first <= last，那么当cnt为奇数时候，中间那个数为0，需要修改为 first < last
  for(int first = 0, last = cnt - 1; first < last; first++, last--){
    inplace_swap(&a[first], &a[last]);
  }
}

int main(){
  int a[5] = {1,2,3,4,5};
  reserve_array(a, 5);
  for (int i = 0; i< 5; i++)
  {
    std::cout << a[i] << " ";
  }
}