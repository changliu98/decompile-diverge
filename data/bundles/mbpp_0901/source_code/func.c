

#include <stdio.h>

#include <assert.h>



int func0(int n) {
  if (n <= 2) {
    return n;
  }
  int i = n * 2;
  int factors[100];
  int factor_count = 0;
  for (int number = n; number > 1; number--) {
    if (number * 2 > n) {
      factors[factor_count++] = number;
    }
  }
  while (1) {
    for (int j = 0; j < factor_count; j++) {
      if (i % factors[j] != 0) {
        i += n;
        break;
      }
      if (j == factor_count - 1 && i % factors[j] == 0) {
        return i;
      }
    }
  }
}
