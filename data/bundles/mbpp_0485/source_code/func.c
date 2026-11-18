

#include <stdio.h>

#include <assert.h>

#include <stdbool.h>



bool is_palindrome(int n) {

    int divisor = 1;

    while (n / divisor >= 10) {

        divisor *= 10;

    }

    while (n != 0) {

        int leading = n / divisor;

        int trailing = n % 10;

        if (leading != trailing) {

            return false;

        }

        n = (n % divisor) / 10;

        divisor = divisor / 100;

    }

    return true;

}



int func0(int A[], int n) {
  int i, j, temp;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (A[i] > A[j]) {
        temp = A[j];
        A[j] = A[i];
        A[i] = temp;
      }
    }
  }
  for (i = n - 1; i >= 0; i--) {
    if (is_palindrome(A[i])) {
      return A[i];
    }
  }
  return -1;
}
