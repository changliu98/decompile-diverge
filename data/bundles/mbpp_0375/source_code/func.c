

#include <assert.h>



int func0(int n, int m) {
  int a = (n / m) * m;
  int b = a + m;
  return (n - a > b - n) ? b : a;
}
