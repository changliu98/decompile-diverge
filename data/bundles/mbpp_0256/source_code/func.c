

#include <assert.h>



int func0(int n) {
  int ctr = 0;
  for (int num = 0; num < n; num++) {
    if (num <= 1) {
      continue;
    }
    int isPrime = 1;
    for (int i = 2; i < num; i++) {
      if (num % i == 0) {
        isPrime = 0;
        break;
      }
    }
    if (isPrime) {
      ctr++;
    }
  }
  return ctr;
}
