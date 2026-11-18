#include <assert.h>



int func0(int n) {
  int a = 3, b = 0, c = 2;
  if (n == 0) return 3;
  if (n == 1) return 3;
  if (n == 2) return 5;
  int sum = 5;
  while (n > 2) {
    int d = a + b;
    sum += d;
    a = b;
    b = c;
    c = d;
    n--;
  }
  return sum;
}
