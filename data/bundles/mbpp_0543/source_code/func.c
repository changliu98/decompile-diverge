

#include <assert.h>



int func0(long long num1, long long num2) {
  long long number = num1 + num2;
  int count = 0;
  while (number > 0) {
    number = number / 10;
    count = count + 1;
  }
  return count;
}
