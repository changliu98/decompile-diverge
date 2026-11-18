

#include <assert.h>



int func0(int number) {
  int sum = 1;
  for (int i = 2; i < number; i++) {
    if (number % i == 0) {
      sum += i;
    }
  }
  return sum;
}
