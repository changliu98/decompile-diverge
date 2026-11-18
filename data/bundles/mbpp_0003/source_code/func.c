

#include <stdio.h>

#include <math.h>

#include <assert.h>



int func0(int n) {
  int result = 0;
  for (int i = 2; i <= (int)sqrt(n); i++) {
    if (n % i == 0) {
      result = 1;
    }
  }
  return result;
}
