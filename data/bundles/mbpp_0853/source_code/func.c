

#include <stdio.h>

#include <math.h>

#include <assert.h>



int func0(int n) {
  int res = 1;
  while (n % 2 == 0) {
    n /= 2;
  }
  for (int i = 3; i <= sqrt(n) + 1; i += 2) {
    int count = 0;
    int curr_sum = 1;
    int curr_term = 1;
    while (n % i == 0) {
      count++;
      n /= i;
      curr_term *= i;
      curr_sum += curr_term;
    }
    res *= curr_sum;
  }
  if (n >= 2) {
    res *= (1 + n);
  }
  return res;
}
