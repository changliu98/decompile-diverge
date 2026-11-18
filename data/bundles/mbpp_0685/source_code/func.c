

#include <stdbool.h>

#include <assert.h>

#include <stdio.h>



int func0(int n) {
  bool prime[n + 1];
  for (int j = 0; j <= n; j++) {
    prime[j] = true;
  }
  int p = 2;
  while (p * p <= n) {
    if (prime[p] == true) {
      int i = p * 2;
      while (i <= n) {
        prime[i] = false;
        i += p;
      }
    }
    p += 1;
  }
  int sum = 0;
  for (int i = 2; i <= n; i++) {
    if (prime[i]) {
      sum += i;
    }
  }
  return sum;
}
