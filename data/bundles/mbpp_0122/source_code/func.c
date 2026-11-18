

#include <stdio.h>

#include <assert.h>



#define MAX 3000



int func0(int n) {
  int primes[MAX] = {0};
  int result[MAX], resultIndex = 0;
  for (int i = 2; i < MAX; i++) {
    if (primes[i] == 0) {
      primes[i] = 1;
      int j = i * 2;
      while (j < MAX) {
        primes[j] -= 1;
        if ((primes[j] + 3) == 0) {
          result[resultIndex++] = j;
        }
        j += i;
      }
    }
  }
  for (int i = 0; i < resultIndex - 1; i++) {
    for (int j = 0; j < resultIndex - i - 1; j++) {
      if (result[j] > result[j + 1]) {
        int temp = result[j];
        result[j] = result[j + 1];
        result[j + 1] = temp;
      }
    }
  }
  return result[n - 1];
}
