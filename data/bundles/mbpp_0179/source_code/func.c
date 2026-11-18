#include <assert.h>

#include <stdbool.h>

#include <stdio.h>



bool func0(int x) {
  int terms[100], temp = x, n = 0;
  while (temp > 0) {
    terms[n++] = temp % 10;
    temp /= 10;
  }
  for (int left = 0, right = n - 1; left < right; left++, right--) {
    int temp = terms[left];
    terms[left] = terms[right];
    terms[right] = temp;
  }
  int next_term = 0, i = n;
  while (next_term < x) {
    next_term = 0;
    for (int j = 1; j <= n; j++) {
      next_term += terms[i - j];
    }
    terms[i++] = next_term;
  }
  return (next_term == x);
}
