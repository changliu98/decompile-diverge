

#include <stdio.h>

#include <assert.h>



int func0(int num) {
  if (num <= 1) return 1;
  int res_num = 0;
  for (int i = 0; i < num; i++) res_num += func0(i) * func0(num - i - 1);
  return res_num;
}
